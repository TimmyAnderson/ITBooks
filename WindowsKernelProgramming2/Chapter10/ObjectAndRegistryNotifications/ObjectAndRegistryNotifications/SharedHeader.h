//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#define MY_DRIVER_NAME L"ObjectAndRegistryNotifications"
//----------------------------------------------------------------------------------------------------------------------
#define CODE_TEST_READ_OBJECT_NOTIFICATION_COUNTERS 0x801
#define CODE_TEST_READ_REGISTRY_NOTIFICATION_COUNTERS 0x802
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
struct SObjectNotificationStatistics final
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		LONG64													MNumberOfPreProcessHandleCreatedCalled;
		LONG64													MNumberOfPreProcessHandleDuplicatedCalled;
		LONG64													MNumberOfPostProcessHandleCreatedCalled;
		LONG64													MNumberOfPostProcessHandleDuplicatedCalled;
		LONG64													MNumberOfPreThreadHandleCreatedCalled;
		LONG64													MNumberOfPreThreadHandleDuplicatedCalled;
		LONG64													MNumberOfPostThreadHandleCreatedCalled;
		LONG64													MNumberOfPostThreadHandleDuplicatedCalled;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
struct SRegistryNotificationStatistics final
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		LONG64													MNumberOfPreCreateKeyCalled;
		LONG64													MNumberOfPostCreateKeyCalled;
		LONG64													MNumberOfPreCreateKeyExCalled;
		LONG64													MNumberOfPostCreateKeyExCalled;
		LONG64													MNumberOfPreDeleteValueKeyCalled;
		LONG64													MNumberOfPostDeleteValueKeyCalled;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------