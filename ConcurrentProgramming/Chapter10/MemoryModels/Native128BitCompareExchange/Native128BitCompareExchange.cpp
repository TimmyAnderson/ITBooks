//------------------------------------------------------------------------------
#include "stdafx.h"
#include <stdio.h>
#include <conio.h>
#include <intrin.h>
//------------------------------------------------------------------------------
// Obsahuje strukturu DVOCH __int64.
typedef struct _LARGE_INTEGER_128
{
	__int64				Int[2];
} LARGE_INTEGER_128, *PLARGE_INTEGER_128;
//------------------------------------------------------------------------------
volatile LARGE_INTEGER_128				BigInt;
//------------------------------------------------------------------------------
// This AtomicOp() function atomically performs:
//   BigInt.Int[1] += BigInt.Int[0],
//   BigInt.Int[0] += 1.
void AtomicOp ()
{
    LARGE_INTEGER_128					Comparand;

    Comparand.Int[0]=BigInt.Int[0];
    Comparand.Int[1]=BigInt.Int[1];

    do
	{
		;
    }
	while(_InterlockedCompareExchange128(BigInt.Int, Comparand.Int[0]+Comparand.Int[1], Comparand.Int[0]+1,Comparand.Int)==0);
}
//------------------------------------------------------------------------------
void Test(void)
{
   BigInt.Int[1]=23;
   BigInt.Int[0]=11;

   AtomicOp();

   printf("BigInt.Int[1] = %d, BigInt.Int[0] = %d !\n", BigInt.Int[1],BigInt.Int[0]);
}
//------------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
	Test();

	printf("Press any key to EXIT !");
	_getch();

	return(0);
}
//------------------------------------------------------------------------------