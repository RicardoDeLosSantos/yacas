//
// declare the core functions that have special syntax
//

OPERATOR(bodied,KMaxPrecedence,While);
OPERATOR(bodied,KMaxPrecedence,Rule);
OPERATOR(bodied,KMaxPrecedence,MacroRule);
OPERATOR(bodied,KMaxPrecedence,RulePattern);
OPERATOR(bodied,KMaxPrecedence,MacroRulePattern);
OPERATOR(bodied,KMaxPrecedence,FromFile);
OPERATOR(bodied,KMaxPrecedence,FromString);
OPERATOR(bodied,KMaxPrecedence,ToFile);
OPERATOR(bodied,KMaxPrecedence,ToString);
OPERATOR(bodied,KMaxPrecedence,ToStdout);
OPERATOR(bodied,KMaxPrecedence,TraceRule);
OPERATOR(bodied,KMaxPrecedence,Subst);
OPERATOR(bodied,KMaxPrecedence,LocalSymbols);
OPERATOR(bodied,KMaxPrecedence,BackQuote);
OPERATOR(prefix,0,`);
OPERATOR(prefix,0,@);
OPERATOR(prefix,0,_);
OPERATOR(infix,0,_);


//
// Evaluation direction.
//
CORE_KERNEL_FUNCTION("Hold",LispQuote,1,YacasEvaluator::Macro | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("Eval",LispEval,1,YacasEvaluator::Function | YacasEvaluator::Fixed);

//
// Input/output functions
//
CORE_KERNEL_FUNCTION("Write",LispWrite,1,YacasEvaluator::Function | YacasEvaluator::Variable);
CORE_KERNEL_FUNCTION("WriteString",LispWriteString,1,YacasEvaluator::Function | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("FullForm",LispFullForm,1,YacasEvaluator::Function | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("DefaultDirectory",LispDefaultDirectory,1,YacasEvaluator::Function | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("DllDirectory",LispDllDirectory,1,YacasEvaluator::Function | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("FromFile",LispFromFile,2,YacasEvaluator::Macro | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("FromString",LispFromString,2,YacasEvaluator::Macro | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("Read",LispRead,0,YacasEvaluator::Function | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("ReadToken",LispReadToken,0,YacasEvaluator::Function | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("ToFile",LispToFile,2,YacasEvaluator::Macro | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("ToString",LispToString,1,YacasEvaluator::Macro | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("ToStdout",LispToStdout,1,YacasEvaluator::Macro | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("Load",LispLoad,1,YacasEvaluator::Function | YacasEvaluator::Fixed);

//
// Variable setting/clearing
//
CORE_KERNEL_FUNCTION("Set",LispSetVar,2,YacasEvaluator::Macro | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("MacroSet",LispMacroSetVar,2,YacasEvaluator::Macro | YacasEvaluator::Fixed);
// MacroClear is the same as Clear, but with its arguments evaluated first
CORE_KERNEL_FUNCTION("Clear",LispClearVar,1,YacasEvaluator::Macro | YacasEvaluator::Variable);
CORE_KERNEL_FUNCTION("MacroClear",LispClearVar,1,YacasEvaluator::Function | YacasEvaluator::Variable);

CORE_KERNEL_FUNCTION("Local",LispNewLocal,1,YacasEvaluator::Macro | YacasEvaluator::Variable);
CORE_KERNEL_FUNCTION("MacroLocal",LispNewLocal,1,YacasEvaluator::Function | YacasEvaluator::Variable);

//
// List and compound object manipulation
//
CORE_KERNEL_FUNCTION("Head",LispHead,1,YacasEvaluator::Function | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("MathNth",LispNth,2,YacasEvaluator::Function | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("Tail",LispTail,1,YacasEvaluator::Function | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("DestructiveReverse",LispDestructiveReverse,1,YacasEvaluator::Function | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("Length",LispLength,1,YacasEvaluator::Function | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("List",LispList,1,YacasEvaluator::Macro | YacasEvaluator::Variable);
CORE_KERNEL_FUNCTION("UnList",LispUnList,1,YacasEvaluator::Function | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("Listify",LispListify,1,YacasEvaluator::Function | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("Concat",LispConcatenate,1,YacasEvaluator::Function | YacasEvaluator::Variable);
CORE_KERNEL_FUNCTION("ConcatStrings",LispConcatenateStrings,1,YacasEvaluator::Function | YacasEvaluator::Variable);

CORE_KERNEL_FUNCTION("Delete",LispDelete,2,YacasEvaluator::Function | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("DestructiveDelete",LispDestructiveDelete,2,YacasEvaluator::Function | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("Insert",LispInsert,3,YacasEvaluator::Function | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("DestructiveInsert",LispDestructiveInsert,3,YacasEvaluator::Function | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("Replace",LispReplace,3,YacasEvaluator::Function | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("DestructiveReplace",LispDestructiveReplace,3,YacasEvaluator::Function | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("Atom",LispAtomize,1,YacasEvaluator::Function | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("String",LispStringify,1,YacasEvaluator::Function | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("FlatCopy",LispFlatCopy,1,YacasEvaluator::Function | YacasEvaluator::Fixed);

//???CORE_KERNEL_FUNCTION("",LispNoCacheConcatenateStrings);

//
// Program control flow
//
CORE_KERNEL_FUNCTION("Prog",LispProgBody,1,YacasEvaluator::Macro | YacasEvaluator::Variable);
CORE_KERNEL_FUNCTION("While",LispWhile,2,YacasEvaluator::Macro | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("If",LispIf,2,YacasEvaluator::Macro | YacasEvaluator::Variable);
//
// Error handling
//
CORE_KERNEL_FUNCTION("Check",LispCheck,2,YacasEvaluator::Macro | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("TrapError",LispTrapError,2,YacasEvaluator::Macro | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("GetCoreError",LispGetCoreError,0,YacasEvaluator::Function | YacasEvaluator::Fixed);

//
// User function definition
//
CORE_KERNEL_FUNCTION("Prefix",LispPreFix,2,YacasEvaluator::Function | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("Infix",LispInFix,2,YacasEvaluator::Function | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("Postfix",LispPostFix,2,YacasEvaluator::Function | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("Bodied",LispBodied,2,YacasEvaluator::Function | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("RuleBase",LispRuleBase,2,YacasEvaluator::Macro | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("MacroRuleBase",LispMacroRuleBase,2,YacasEvaluator::Function | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("RuleBaseListed",LispRuleBaseListed,2,YacasEvaluator::Macro | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("MacroRuleBaseListed",LispMacroRuleBaseListed,2,YacasEvaluator::Function | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("DefMacroRuleBase",LispDefMacroRuleBase,2,YacasEvaluator::Macro | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("DefMacroRuleBaseListed",LispDefMacroRuleBaseListed,2,YacasEvaluator::Macro | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("HoldArg",LispHoldArg,2,YacasEvaluator::Function | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("Rule",LispNewRule,5,YacasEvaluator::Macro | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("MacroRule",LispMacroNewRule,5,YacasEvaluator::Function | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("UnFence",LispUnFence,2,YacasEvaluator::Function | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("Retract",LispRetract,2,YacasEvaluator::Function | YacasEvaluator::Fixed);
//
// Predicates
//
CORE_KERNEL_FUNCTION("MathNot",LispNot,1,YacasEvaluator::Function | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION_ALIAS("Not",LispNot,1,YacasEvaluator::Function | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("MathAnd",LispLazyAnd,1,YacasEvaluator::Macro | YacasEvaluator::Variable);
CORE_KERNEL_FUNCTION_ALIAS("And",LispLazyAnd,1,YacasEvaluator::Macro | YacasEvaluator::Variable);
CORE_KERNEL_FUNCTION("MathOr",LispLazyOr,1,YacasEvaluator::Macro | YacasEvaluator::Variable);
CORE_KERNEL_FUNCTION_ALIAS("Or",LispLazyOr,1,YacasEvaluator::Macro | YacasEvaluator::Variable);
CORE_KERNEL_FUNCTION("Equals",LispEquals,2,YacasEvaluator::Function | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION_ALIAS("=",LispEquals,2,YacasEvaluator::Function | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("LessThan",LispLessThan,2,YacasEvaluator::Function | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("GreaterThan",LispGreaterThan,2,YacasEvaluator::Function | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("IsFunction",LispIsFunction,1,YacasEvaluator::Function | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("IsAtom",LispIsAtom,1,YacasEvaluator::Function | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("IsNumber",LispIsNumber,1,YacasEvaluator::Function | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("IsInteger",LispIsInteger,1,YacasEvaluator::Function | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("IsList",LispIsList,1,YacasEvaluator::Function | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("IsString",LispIsString,1,YacasEvaluator::Function | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("IsBound",LispIsBound,1,YacasEvaluator::Macro | YacasEvaluator::Fixed);
//
// Math functions (REQUIRING number inputs);.
//
CORE_KERNEL_FUNCTION("MathMultiply",LispMultiply,2,YacasEvaluator::Function | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("MathAdd",LispAdd,2,YacasEvaluator::Function | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("MathSubtract",LispSubtract,2,YacasEvaluator::Function | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("MathDivide",LispDivide,2,YacasEvaluator::Function | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("MathDebugInfo",LispDumpBigNumberDebugInfo,1,YacasEvaluator::Function | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("MathSin",LispSin,1,YacasEvaluator::Function | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("MathCos",LispCos,1,YacasEvaluator::Function | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("MathTan",LispTan,1,YacasEvaluator::Function | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("MathArcSin",LispArcSin,1,YacasEvaluator::Function | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("MathArcCos",LispArcCos,1,YacasEvaluator::Function | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("MathArcTan",LispArcTan,1,YacasEvaluator::Function | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("Precision",LispPrecision,1,YacasEvaluator::Function | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("MathGetExactBits",LispGetExactBits,1,YacasEvaluator::Function | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("MathSetExactBits",LispSetExactBits,2,YacasEvaluator::Function | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("MathSqrt",LispSqrt,1,YacasEvaluator::Function | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("MathFloor",LispFloor,1,YacasEvaluator::Function | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("MathCeil",LispCeil,1,YacasEvaluator::Function | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("MathAbs",LispAbs,1,YacasEvaluator::Function | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("MathMod",LispMod,2,YacasEvaluator::Function | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("MathDiv",LispDiv,2,YacasEvaluator::Function | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("MathLog",LispLog,1,YacasEvaluator::Function | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("MathExp",LispExp,1,YacasEvaluator::Function | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("MathPower",LispPower,2,YacasEvaluator::Function | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("MathPi",LispPi,0,YacasEvaluator::Function | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("MathGcd",LispGcd,2,YacasEvaluator::Function | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("SystemCall",LispSystemCall,1,YacasEvaluator::Function | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("FastSin",LispFastSin,1,YacasEvaluator::Function | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("FastCos",LispFastCos,1,YacasEvaluator::Function | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("FastTan",LispFastTan,1,YacasEvaluator::Function | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("FastArcSin",LispFastArcSin,1,YacasEvaluator::Function | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("FastArcCos",LispFastArcCos,1,YacasEvaluator::Function | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("FastArcTan",LispFastArcTan,1,YacasEvaluator::Function | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("FastExp",LispFastExp,1,YacasEvaluator::Function | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("FastLog",LispFastLog,1,YacasEvaluator::Function | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("FastPower",LispFastPower,2,YacasEvaluator::Function | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("FastSqrt",LispFastSqrt,1,YacasEvaluator::Function | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("FastPi",LispFastPi,0,YacasEvaluator::Function | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("FastFloor",LispFastFloor,1,YacasEvaluator::Function | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("FastCeil",LispFastCeil,1,YacasEvaluator::Function | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("FastMod",LispFastMod,2,YacasEvaluator::Function | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("FastAbs",LispFastAbs,1,YacasEvaluator::Function | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("ShiftLeft",LispShiftLeft,2,YacasEvaluator::Function | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("ShiftRight",LispShiftRight,2,YacasEvaluator::Function | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("FromBase",LispFromBase,2,YacasEvaluator::Function | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("ToBase",LispToBase,2,YacasEvaluator::Function | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("MaxEvalDepth",LispMaxEvalDepth,1,YacasEvaluator::Function | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("DefLoad",LispDefLoad,1,YacasEvaluator::Function | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("Use",LispUse,1,YacasEvaluator::Function | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("RightAssociative",LispRightAssociative,1,YacasEvaluator::Function | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("LeftPrecedence",LispLeftPrecedence,2,YacasEvaluator::Function | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("RightPrecedence",LispRightPrecedence,2,YacasEvaluator::Function | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("IsBodied",LispIsBodied,1,YacasEvaluator::Function | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("IsInfix",LispIsInFix,1,YacasEvaluator::Function | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("IsPrefix",LispIsPreFix,1,YacasEvaluator::Function | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("IsPostfix",LispIsPostFix,1,YacasEvaluator::Function | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("OpPrecedence",LispGetPrecedence,1,YacasEvaluator::Function | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("OpLeftPrecedence",LispGetLeftPrecedence,1,YacasEvaluator::Function | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("OpRightPrecedence",LispGetRightPrecedence,1,YacasEvaluator::Function | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("GetPrecision",LispGetPrecision,0,YacasEvaluator::Function | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("BitAnd",LispBitAnd,2,YacasEvaluator::Function | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("BitOr",LispBitOr,2,YacasEvaluator::Function | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("BitXor",LispBitXor,2,YacasEvaluator::Function | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("Secure",LispSecure,1,YacasEvaluator::Macro | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("FindFile",LispFindFile,1,YacasEvaluator::Function | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("FindFunction",LispFindFunction,1,YacasEvaluator::Function | YacasEvaluator::Fixed);
// Generic objecs support 
CORE_KERNEL_FUNCTION("IsGeneric",LispIsGeneric,1,YacasEvaluator::Function | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("GenericTypeName",LispGenericTypeName,1,YacasEvaluator::Function | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("ArrayCreate",GenArrayCreate,2,YacasEvaluator::Function | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("ArraySize",GenArraySize,1,YacasEvaluator::Function | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("ArrayGet",GenArrayGet,2,YacasEvaluator::Function | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("ArraySet",GenArraySet,3,YacasEvaluator::Function | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("CustomEval",LispCustomEval,4,YacasEvaluator::Macro | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("CustomEval'Expression",LispCustomEvalExpression,0,YacasEvaluator::Function | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("CustomEval'Result",LispCustomEvalResult,0,YacasEvaluator::Function | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("CustomEval'Locals",LispCustomEvalLocals,0,YacasEvaluator::Function | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("CustomEval'Stop",LispCustomEvalStop,0,YacasEvaluator::Function | YacasEvaluator::Fixed);

CORE_KERNEL_FUNCTION("TraceRule",LispTraceRule,2,YacasEvaluator::Macro | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("TraceStack",LispTraceStack,1,YacasEvaluator::Macro | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("LispRead",LispReadLisp,0,YacasEvaluator::Function | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("LispReadListed",LispReadLispListed,0,YacasEvaluator::Function | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("Type",LispType,1,YacasEvaluator::Function | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("StringMid",LispStringMid,3,YacasEvaluator::Function | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("SetStringMid",LispSetStringMid,3,YacasEvaluator::Function | YacasEvaluator::Fixed);
// Pattern matching 
CORE_KERNEL_FUNCTION("PatternCreate",GenPatternCreate,2,YacasEvaluator::Function | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("PatternMatches",GenPatternMatches,2,YacasEvaluator::Function | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("RuleBaseDefined",LispRuleBaseDefined,2,YacasEvaluator::Function | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("DefLoadFunction",LispDefLoadFunction,1,YacasEvaluator::Function | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("RuleBaseArgList",LispRuleBaseArgList,2,YacasEvaluator::Function | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("RulePattern",LispNewRulePattern,5,YacasEvaluator::Macro | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("MacroRulePattern",LispMacroNewRulePattern,5,YacasEvaluator::Function | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("Subst",LispSubst,3,YacasEvaluator::Function | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("LocalSymbols",LispLocalSymbols,1,YacasEvaluator::Macro | YacasEvaluator::Variable);
CORE_KERNEL_FUNCTION("FastIsPrime",LispFastIsPrime,1,YacasEvaluator::Function | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("MathFac",LispFac,1,YacasEvaluator::Function | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("ApplyPure",LispApplyPure,2,YacasEvaluator::Function | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("PrettyPrinter",LispPrettyPrinter,1,YacasEvaluator::Function | YacasEvaluator::Variable);
CORE_KERNEL_FUNCTION("GetPrettyPrinter",LispGetPrettyPrinter,0,YacasEvaluator::Function | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("GarbageCollect",LispGarbageCollect,0,YacasEvaluator::Function | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("LazyGlobal",LispLazyGlobal,1,YacasEvaluator::Macro | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("PatchLoad",LispPatchLoad,1,YacasEvaluator::Function | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("PatchString",LispPatchString,1,YacasEvaluator::Function | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("DllLoad",LispDllLoad,1,YacasEvaluator::Function | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("DllUnload",LispDllUnload,1,YacasEvaluator::Function | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("DllEnumerate",LispDllEnumerate,0,YacasEvaluator::Function | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("SetExtraInfo",LispSetExtraInfo,2,YacasEvaluator::Function | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("GetExtraInfo",LispGetExtraInfo,1,YacasEvaluator::Function | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("Berlekamp",LispBerlekamp,2,YacasEvaluator::Function | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("DefaultTokenizer",LispDefaultTokenizer,0,YacasEvaluator::Function | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("CommonLispTokenizer",LispCommonLispTokenizer,0,YacasEvaluator::Function | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("CTokenizer",LispCTokenizer,0,YacasEvaluator::Function | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("XmlTokenizer",LispXmlTokenizer,0,YacasEvaluator::Function | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("XmlExplodeTag",LispExplodeTag,1,YacasEvaluator::Function | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("FastAssoc",LispFastAssoc,2,YacasEvaluator::Function | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("CurrentFile",LispCurrentFile,0,YacasEvaluator::Function | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("CurrentLine",LispCurrentLine,0,YacasEvaluator::Function | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("`",LispBackQuote,1,YacasEvaluator::Macro | YacasEvaluator::Fixed);

//
// Information functions
//
CORE_KERNEL_FUNCTION("MathLibrary",LispMathLibName,0,YacasEvaluator::Function | YacasEvaluator::Fixed);
CORE_KERNEL_FUNCTION("Version",LispVersion,0,YacasEvaluator::Function | YacasEvaluator::Fixed);
