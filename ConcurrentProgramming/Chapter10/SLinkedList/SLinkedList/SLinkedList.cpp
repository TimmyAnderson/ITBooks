#include "stdafx.h"
#include <windows.h>
#include <process.h>
#include "MyDebug.h"
#include "SDataItem.h"
//-----------------------------------------------------------------------------
void Test(void)
{
	SLIST_HEADER				ListHead;

	InitializeSListHead(&ListHead);

	// Vlozim 10 Items do Stack.
	for (int i=0;i<10;i++)
	{
		SDataItem				*D=new SDataItem();

		D->MValue=i;
		InterlockedPushEntrySList(&ListHead, &D->MListEntry);

		printf("ADDED - value: [%d] !\n",D->MValue);
	}

	// Vyberiem 5 Items zo Stack.
	for (int i=0;i<5;i++)
	{
		SDataItem				*D=(SDataItem *) InterlockedPopEntrySList(&ListHead);

		printf("REMOVED - value: [%d] !\n",D->MValue);

		delete(D);
	}

	// Now flush the remaining contents of the list.
	SDataItem					*D=(SDataItem *) InterlockedFlushSList(&ListHead);

	while (D!=NULL)
	{
		SDataItem				*Next=(SDataItem *) D->MListEntry.Next;

		printf("CLEARED - value: [%d] !\n",D->MValue);

		delete(D);
		D=Next;
	}
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
	SafeMain();

	Test();

	ShowExitLine();

	return(0);
}
//-----------------------------------------------------------------------------