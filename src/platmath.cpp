/* Math using the standard library, if the precision is less than 13 */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "yacasprivate.h"
#include "yacasbase.h"
#include "lispobject.h"
#include "lispatom.h"
#include "lispenvironment.h"
#include "numbers.h"
#include "platmath.h"
#include "errors.h"


double GetDouble(LispObject* aInteger)
{
  BigNumber* number = aInteger->Number(0);
  if (number == NULL)
  {
    RaiseError("Argument is not a number: %s",aInteger->String());
  }
  return number->Double();

//TODO remove return strtod(aString,NULL); 
}

LispObject* Double(LispEnvironment& aEnvironment,double aValue)
{
  char buf[150];
#ifdef HAVE_VSNPRINTF
    snprintf(buf,150,"%g",aValue);
#else
    sprintf(buf,"%g",aValue);
#endif
  return LispAtom::New(aEnvironment,buf);
}

LispObject* PlatSin(LispEnvironment& aEnvironment,LispObject* int1, LispInt aPrecision)
{
    return Double(aEnvironment, sin(GetDouble(int1)));
}

LispObject* PlatCos(LispEnvironment& aEnvironment,LispObject* int1, LispInt aPrecision)
{
    return Double(aEnvironment, cos(GetDouble(int1)));
}

LispObject* PlatTan(LispEnvironment& aEnvironment,LispObject* int1, LispInt aPrecision)
{
    return Double(aEnvironment, tan(GetDouble(int1)));
}

LispObject* PlatArcSin(LispEnvironment& aEnvironment,LispObject* int1, LispInt aPrecision)
{
    return Double(aEnvironment, asin(GetDouble(int1)));
}

LispObject* PlatArcCos(LispEnvironment& aEnvironment,LispObject* int1, LispInt aPrecision)
{
    return Double(aEnvironment, acos(GetDouble(int1)));
}

LispObject* PlatArcTan(LispEnvironment& aEnvironment,LispObject* int1, LispInt aPrecision)
{
    return Double(aEnvironment, atan(GetDouble(int1)));
}

LispObject* PlatExp(LispEnvironment& aEnvironment,LispObject* int1, LispInt aPrecision)
{
    return Double(aEnvironment, exp(GetDouble(int1)));
}

LispObject* PlatLn(LispEnvironment& aEnvironment,LispObject* int1, LispInt aPrecision)
{
    return Double(aEnvironment, log(GetDouble(int1)));
}

LispObject* PlatPower(LispEnvironment& aEnvironment,LispObject* int1, LispObject* int2,
                        LispInt aPrecision)
{
    return Double(aEnvironment, pow(GetDouble(int1),GetDouble(int2)));
}



LispObject* PlatSqrt(LispEnvironment& aEnvironment,LispObject* int1, LispInt aPrecision)
{
    return Double(aEnvironment, sqrt(GetDouble(int1)));
}
LispObject* PlatPi(LispEnvironment& aEnvironment,LispInt aPrecision)
{
    return Double(aEnvironment, acos(-1.0));
}
LispObject* PlatFloor(LispEnvironment& aEnvironment,LispObject* int1, LispInt aPrecision)
{
    return Double(aEnvironment, floor(GetDouble(int1)));
}
LispObject* PlatCeil(LispEnvironment& aEnvironment,LispObject* int1, LispInt aPrecision)
{
    return Double(aEnvironment, ceil(GetDouble(int1)));
}
LispObject* PlatMod(LispEnvironment& aEnvironment,LispObject* int1, LispObject* int2,LispInt aPrecision)
{
    return Double(aEnvironment, fmod(GetDouble(int1),GetDouble(int2)));
}
LispObject* PlatDiv(LispEnvironment& aEnvironment,LispObject* int1, LispObject* int2,LispInt aPrecision)
{
    return Double(aEnvironment,((long)GetDouble(int1))/((long)GetDouble(int2)));
}
LispObject* PlatAbs(LispEnvironment& aEnvironment,LispObject* int1, LispInt aPrecision)
{
    return Double(aEnvironment, fabs(GetDouble(int1)));
}


/// fast checking for prime numbers

#include "fastprimes.c"

/* subroutine returns 1 if p is in the table of prime numbers up to primes_table_limit */
unsigned primes_table_check(unsigned long p)
{
	unsigned long index;
	unsigned field;
	if (p==0) return primes_table_limit;
	if (p==2) return 1;
	if (p<2 || p>primes_table_limit || (p & 1) == 0) return 0;
	p >>= 1;
	// get index in 8-bit chunks
	index = p >> 3;
	field = p & 7;
	return ((primes_table[index] & (1 << field))==0) ? 0 : 1;
}

LispObject* PlatIsPrime(LispEnvironment& aEnvironment,LispObject* int1, LispInt aPrecision)
{
    return Double(aEnvironment, primes_table_check((unsigned long)(GetDouble(int1))));
}


