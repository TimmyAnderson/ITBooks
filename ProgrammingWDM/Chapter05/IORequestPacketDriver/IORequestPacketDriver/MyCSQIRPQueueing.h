//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include "Driver.h"
//-------------------------------------------------------------------------------------------------------
NTSTATUS MyCSQInsertIRPEx(PIO_CSQ Queue, PIRP InterruptRequestPacket, PVOID InsertContext);
VOID MyCSQRemoveIRP(PIO_CSQ Queue, PIRP InterruptRequestPacket);
PIRP MyCSQPeekNextIRP(PIO_CSQ Queue, PIRP InterruptRequestPacket, PVOID PeekContext);
VOID MyCSQCompleteCanceledIRP(PIO_CSQ Queue, PIRP InterruptRequestPacket);
_IRQL_raises_(DISPATCH_LEVEL)
VOID MyCSQAcquireLock(PIO_CSQ Queue, PKIRQL IRQL);
_IRQL_raises_(DISPATCH_LEVEL)
VOID MyCSQReleaseLock(PIO_CSQ Queue, KIRQL IRQL);
//-------------------------------------------------------------------------------------------------------