


#include "yacas/yacasprivate.h"
#include "yacas/yacasbase.h"
#include "yacas/patterns.h"
#include "yacas/standard.h"
#include "yacas/mathuserfunc.h"
#include "yacas/lispobject.h"
#include "yacas/lispeval.h"
#include "yacas/standard.h"

#ifdef YACAS_DEBUG
#include <stdio.h>
#endif // YACAS_DEBUG


MatchAtom::MatchAtom(LispString * aString) : iString(aString)
{
}

bool MatchAtom::ArgumentMatches(LispEnvironment& aEnvironment,
                                       LispPtr& aExpression,
                                       LispPtr* arguments)
{
    // If it is a floating point, don't even bother comparing
    if (!!aExpression)
      if (aExpression->Number(0))
        if (!aExpression->Number(0)->IsInt())
          return false;

    return (iString == aExpression->String());
}







MatchNumber::MatchNumber(BigNumber* aNumber) : iNumber(aNumber)
{
}

bool MatchNumber::ArgumentMatches(LispEnvironment& aEnvironment,
                                       LispPtr& aExpression,
                                       LispPtr* arguments)
{
  if (aExpression->Number(aEnvironment.Precision()))
    return iNumber->Equals(*aExpression->Number(aEnvironment.Precision()));
  return false;
}




MatchVariable::MatchVariable(LispInt aVarIndex) : iVarIndex(aVarIndex)
{
}
bool MatchVariable::ArgumentMatches(LispEnvironment& aEnvironment,
                                       LispPtr& aExpression,
                                       LispPtr* arguments)
{
    if (!arguments[iVarIndex])
    {
        arguments[iVarIndex] = (aExpression);
        return true;
    }
    else
    {
        if (InternalEquals(aEnvironment, aExpression, arguments[iVarIndex]))
        {
            return true;
        }
        return false;
    }
    return false;
}

MatchSubList::MatchSubList(YacasParamMatcherBase** aMatchers,
                           LispInt aNrMatchers)
: iMatchers(aMatchers),iNrMatchers(aNrMatchers)

{
}

MatchSubList::~MatchSubList()
{
    if (iMatchers)
    {
        LispInt i;
        for (i=0;i<iNrMatchers;i++)
            delete iMatchers[i];
        PlatFree(iMatchers);
    }
}

bool MatchSubList::ArgumentMatches(LispEnvironment& aEnvironment,
                                          LispPtr& aExpression,
                                          LispPtr* arguments)
{
  if (!aExpression->SubList())
    return false;

  LispIterator iter(aExpression);
  LispObject * pObj = iter.getObj();

  if (!pObj)
      throw LispErrInvalidArg();

  LispPtr * pPtr = pObj->SubList();

  if (!pPtr)
      throw LispErrNotList();

  iter = *pPtr;

  for (LispInt i=0;i<iNrMatchers;i++,++iter)
  {
    if (!iter.getObj())
      return false;
    if (!iMatchers[i]->ArgumentMatches(aEnvironment,*iter,arguments))
      return false;
  }
  if (iter.getObj())
    return false;
  return true;
}

LispInt YacasPatternPredicateBase::LookUp(LispString * aVariable)
{
    LispInt i;
    for (i=0;i<iVariables.Size();i++)
    {
        if (iVariables[i] == aVariable)
        {
            return i;
        }
    }
    aVariable->iReferenceCount += 1;
    iVariables.Append(aVariable);
    return iVariables.Size()-1;
}


YacasParamMatcherBase* YacasPatternPredicateBase::MakeParamMatcher(LispEnvironment& aEnvironment, LispObject* aPattern)
{
    if (!aPattern)
        return nullptr;

    if (aPattern->Number(aEnvironment.Precision()))
    {
        return NEW MatchNumber(aPattern->Number(aEnvironment.Precision()));
    }

    // Deal with atoms
    if (aPattern->String())
    {
        return NEW MatchAtom(aPattern->String());
    }

    // Else it must be a sublist
    if (aPattern->SubList())
    {
        // See if it is a variable template:
        LispPtr* sublist = aPattern->SubList();
        assert(sublist);

        LispInt num = InternalListLength(*sublist);

        // variable matcher here...
        if (num>1)
        {
            LispObject* head = (*sublist);
            if (head->String() == aEnvironment.HashTable().LookUp("_"))
            {
                LispObject* second = head->Nixed();
                if (second->String())
                {
                    LispInt index = LookUp(second->String());

                    // Make a predicate for the type, if needed
                    if (num>2)
                    {
                        LispPtr third;

                        LispObject* predicate = second->Nixed();
                        if (predicate->SubList())
                        {
                            InternalFlatCopy(third, *predicate->SubList());
                        }
                        else
                        {
                            third = (second->Nixed()->Copy());
                        }

                        LispObject* last = third;
                        while (!!last->Nixed())
                            last = last->Nixed();

                        last->Nixed() = (LispAtom::New(aEnvironment,second->String()->c_str()));

                        LispPtr pred(LispSubList::New(third));
                        DBG_( third->Nixed()->SetFileAndLine(second->iFileName,second->iLine); )
                        DBG_( pred->SetFileAndLine(head->iFileName,head->iLine); )
                        iPredicates.Append(pred);
                    }
                    return NEW MatchVariable(index);
                }
            }
        }

        YacasParamMatcherBase** matchers = PlatAllocN<YacasParamMatcherBase*>(num);
        LispIterator iter(*sublist);
        for (LispInt i=0;i<num;i++,++iter)
        {
            matchers[i] = MakeParamMatcher(aEnvironment,iter.getObj());
            assert(matchers[i]);
        }
    return NEW MatchSubList(matchers, num);
    }

    return nullptr;
}

YacasPatternPredicateBase::YacasPatternPredicateBase(LispEnvironment& aEnvironment, LispPtr& aPattern,
                                                     LispPtr& aPostPredicate)
  : iParamMatchers(),iVariables(),iPredicates()
{
    LispIterator iter(aPattern);
    for ( ; iter.getObj(); ++iter)
  {
        YacasParamMatcherBase* matcher = MakeParamMatcher(aEnvironment,iter.getObj());
        assert(matcher!=nullptr);
        iParamMatchers.Append(matcher);
  }
  LispPtr post(aPostPredicate);
  iPredicates.Append(post);
}

bool YacasPatternPredicateBase::Matches(LispEnvironment& aEnvironment,
                                              LispPtr& aArguments)
{
    LispPtr* arguments = nullptr;
    if (iVariables.Size() > 0)
    arguments = NEW LispPtr[iVariables.Size()];
    LocalArgs args(arguments); //Deal with destruction
    LispIterator iter(aArguments);
    for (LispInt i=0;i<iParamMatchers.Size();i++,++iter)
  {
        if (!iter.getObj())
            return false;
        if (!iParamMatchers[i]->ArgumentMatches(aEnvironment,*iter,arguments))
        {
            return false;
        }
  }
    if (iter.getObj())
        return false;

    {
        // set the local variables.
        LispLocalFrame frame(aEnvironment,false);

        SetPatternVariables(aEnvironment,arguments);

        // do the predicates
        if (!CheckPredicates(aEnvironment))
            return false;
    }

    // set the local variables for sure now
    SetPatternVariables(aEnvironment,arguments);

    return true;
}




bool YacasPatternPredicateBase::Matches(LispEnvironment& aEnvironment,
                                              LispPtr* aArguments)
{
    LispInt i;

    LispPtr* arguments = nullptr;
    if (iVariables.Size() > 0)
        arguments = NEW LispPtr[iVariables.Size()];
    LocalArgs args(arguments); //Deal with destruction

    for (i=0;i<iParamMatchers.Size();i++)
    {
        if (!iParamMatchers[i]->ArgumentMatches(aEnvironment,aArguments[i],arguments))
        {
            return false;
        }
    }

    {
        // set the local variables.
        LispLocalFrame frame(aEnvironment,false);
        SetPatternVariables(aEnvironment,arguments);

        // do the predicates
        if (!CheckPredicates(aEnvironment))
            return false;
    }

    // set the local variables for sure now
    SetPatternVariables(aEnvironment,arguments);
    return true;
}



bool YacasPatternPredicateBase::CheckPredicates(LispEnvironment& aEnvironment)
{
  for (LispInt i=0;i<iPredicates.Size();i++)
  {
    LispPtr pred;
    aEnvironment.iEvaluator->Eval(aEnvironment, pred, iPredicates[i]);
    if (IsFalse(aEnvironment, pred))
    {
      return false;
    }
    // If the result is not False, it should be True, else probably something is wrong (the expression returned unevaluated)
    bool isTrue = IsTrue(aEnvironment, pred);
    if (!isTrue)
    {
#define LIM_AL 60
      LispString strout;

#ifdef YACAS_DEBUG
        if (iPredicates[i]->iFileName)
        {
          printf("File %s, line %d\n",iPredicates[i]->iFileName, iPredicates[i]->iLine);
        }
#endif


      aEnvironment.iErrorOutput.Write("The predicate\n\t");
      PrintExpression(strout, iPredicates[i], aEnvironment, LIM_AL);
      aEnvironment.iErrorOutput.Write(strout.c_str());
      aEnvironment.iErrorOutput.Write("\nevaluated to\n\t");
      PrintExpression(strout, pred, aEnvironment, LIM_AL);
      aEnvironment.iErrorOutput.Write(strout.c_str());
      aEnvironment.iErrorOutput.Write("\n");

      ShowStack(aEnvironment);
      throw LispErrMaxRecurseDepthReached();
    }
  }
  return true;
}


void YacasPatternPredicateBase::SetPatternVariables(LispEnvironment& aEnvironment,
                                                    LispPtr* arguments)
{
    LispInt i;
    for (i=0;i<iVariables.Size();i++)
    {
        // set the variable to the new value
        aEnvironment.NewLocal(iVariables[i],arguments[i]);
    }
}


YacasPatternPredicateBase::~YacasPatternPredicateBase()
{
    for (int i = 0; i < iVariables.Size(); ++i) {
        if (--iVariables[i]->iReferenceCount == 0)
            delete iVariables[i];
    }
}

