//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <ntddk.h>
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! Tato ENUM je vytiahnuty z USER MODE HEADER [Winternl.h]. HEADER sa neda vlozit priamo, pretoze by doslo ku kolizii NAMES.
enum class ESYSTEM_INFORMATION_CLASS
{
//----------------------------------------------------------------------------------------------------------------------
    SystemBasicInformation=0,
    SystemPerformanceInformation=2,
    SystemTimeOfDayInformation=3,
    SystemProcessInformation=5,
    SystemProcessorPerformanceInformation=8,
    SystemInterruptInformation=23,
    SystemExceptionInformation=33,
    SystemRegistryQuotaInformation=37,
    SystemLookasideInformation=45,
    SystemCodeIntegrityInformation=103,
    SystemPolicyInformation=134,
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! Tato ENUM je vytiahnuty z USER MODE HEADER [Winternl.h]. HEADER sa neda vlozit priamo, pretoze by doslo  ku kolizii NAMES.
enum class EPROCESSINFOCLASS
{
//----------------------------------------------------------------------------------------------------------------------
    ProcessBasicInformation=0,
    ProcessDebugPort=7,
    ProcessWow64Information=26,
    ProcessImageFileName=27,
    ProcessBreakOnTermination=29
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! Tato STRUCTURE je vytiahnuta z USER MODE HEADER [Winternl.h]. HEADER sa neda vlozit priamo, pretoze by doslo  ku kolizii NAMES.
struct SSYSTEM_PROCESS_INFORMATION final
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		ULONG														NextEntryOffset;
		ULONG														NumberOfThreads;
		UCHAR														Reserved1[48];
		UNICODE_STRING												ImageName;
		KPRIORITY													BasePriority;
		HANDLE														UniqueProcessId;
		PVOID														Reserved2;
		ULONG														HandleCount;
		ULONG														SessionId;
		PVOID														Reserved3;
		SIZE_T														PeakVirtualSize;
		SIZE_T														VirtualSize;
		ULONG														Reserved4;
		SIZE_T														PeakWorkingSetSize;
		SIZE_T														WorkingSetSize;
		PVOID														Reserved5;
		SIZE_T														QuotaPagedPoolUsage;
		PVOID														Reserved6;
		SIZE_T														QuotaNonPagedPoolUsage;
		SIZE_T														PagefileUsage;
		SIZE_T														PeakPagefileUsage;
		SIZE_T														PrivatePageCount;
		LARGE_INTEGER												Reserved7[6];
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! Tato STRUCTURE je vytiahnuta z USER MODE HEADER [Winternl.h]. HEADER sa neda vlozit priamo, pretoze by doslo  ku kolizii NAMES.
struct SPROCESS_BASIC_INFORMATION final
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		NTSTATUS													ExitStatus;
		PPEB														PebBaseAddress;
		ULONG_PTR													AffinityMask;
		KPRIORITY													BasePriority;
		ULONG_PTR													UniqueProcessId;
		ULONG_PTR													InheritedFromUniqueProcessId;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! Tato FUNCTION je vytiahnuta z USER MODE HEADER [Winternl.h]. HEADER sa neda vlozit priamo, pretoze by doslo  ku kolizii NAMES.
extern "C" NTSTATUS NTAPI ZwQuerySystemInformation(ESYSTEM_INFORMATION_CLASS SystemInformationClass, PVOID SystemInformation, ULONG SystemInformationLength, PULONG ReturnLength);
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! Tato FUNCTION je vytiahnuta z USER MODE HEADER [Winternl.h]. HEADER sa neda vlozit priamo, pretoze by doslo  ku kolizii NAMES.
extern "C" NTSTATUS NTAPI ZwQueryInformationProcess(HANDLE ProcessHandle, EPROCESSINFOCLASS ProcessInformationClass, PVOID ProcessInformation, ULONG ProcessInformationLength, PULONG ReturnLength);
//----------------------------------------------------------------------------------------------------------------------