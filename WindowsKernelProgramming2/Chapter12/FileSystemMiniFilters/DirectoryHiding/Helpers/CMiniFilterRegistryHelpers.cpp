//----------------------------------------------------------------------------------------------------------------------
#include "CMiniFilterRegistryHelpers.h"
#include "CRegistryKeyCreate.h"
#include "CRegistryKeyOpen.h"
#include "MyKernelHelpers.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
NTSTATUS CMiniFilterRegistryHelpers::CreateRegistryKeys(PUNICODE_STRING RegistryPath, const WCHAR* InstanceNameBuffer, ULONG InstanceNameSize, const WCHAR* AltitudeBuffer, ULONG AltitudeSize, ULONG Flags)
{
	NTSTATUS													Status;
	PWSTR														Buffer=(PWSTR) ExAllocatePool2(POOL_FLAG_NON_PAGED,RegistryPath->MaximumLength,MY_TAG);

	if (Buffer!=nullptr)
	{
		MRegistryPath.Length=0;
		MRegistryPath.MaximumLength=RegistryPath->MaximumLength;
		MRegistryPath.Buffer=Buffer;

		RtlCopyUnicodeString(&MRegistryPath,RegistryPath);

		UNICODE_STRING											SubKeyName=RTL_CONSTANT_STRING(L"Instances");
		UNICODE_STRING											DefaultInstanceName=RTL_CONSTANT_STRING(L"DefaultInstance");
		UNICODE_STRING											AltitudeName=RTL_CONSTANT_STRING(L"Altitude");
		UNICODE_STRING											FlagsName=RTL_CONSTANT_STRING(L"Flags");

		UNICODE_STRING											InstanceName;

		RtlInitUnicodeString(&InstanceName,InstanceNameBuffer);

		{
			OBJECT_ATTRIBUTES									KeyAttributes=RTL_CONSTANT_OBJECT_ATTRIBUTES(RegistryPath,OBJ_KERNEL_HANDLE);
			CRegistryKeyOpen									Key(Status,KEY_WRITE,KeyAttributes);

			if (NT_SUCCESS(Status)==true)
			{
				OBJECT_ATTRIBUTES								SubKeyAttributes;
		
				InitializeObjectAttributes(&SubKeyAttributes,&SubKeyName,OBJ_KERNEL_HANDLE,Key.GetKey(),nullptr);

				CRegistryKeyCreate								SubKey(Status,KEY_WRITE,SubKeyAttributes,0,nullptr,0,nullptr);

				if (NT_SUCCESS(Status)==true)
				{
					do
					{
						Status=SubKey.SetValueKey(DefaultInstanceName,0,REG_SZ,(PVOID)InstanceNameBuffer,InstanceNameSize);

						if (NT_SUCCESS(Status)==false)
						{
							KdPrint(("!!!!! FILE SYSTEM MINI FILTER REGISTRATION FAILED to CREATE KEY [%wZ] with ERROR CODE [%lX] !!!\n",InstanceName,Status));
							break;
						}

						OBJECT_ATTRIBUTES						InstanceSubKeyAttributes;

						InitializeObjectAttributes(&InstanceSubKeyAttributes,&InstanceName,OBJ_KERNEL_HANDLE,SubKey.GetKey(),nullptr);

						CRegistryKeyCreate						InstanceSubKey(Status,KEY_WRITE,InstanceSubKeyAttributes,0,nullptr,0,nullptr);

						if (NT_SUCCESS(Status)==true)
						{
							do
							{
								Status=InstanceSubKey.SetValueKey(AltitudeName,0,REG_SZ,(PVOID)AltitudeBuffer,AltitudeSize);

								if (NT_SUCCESS(Status)==false)
								{
									KdPrint(("!!!!! FILE SYSTEM MINI FILTER REGISTRATION FAILED to CREATE KEY VALUE [%wZ] with ERROR CODE [%lX] !!!\n",AltitudeName,Status));
									break;
								}

								Status=InstanceSubKey.SetValueKey(FlagsName,0,REG_DWORD,&Flags,sizeof(Flags));

								if (NT_SUCCESS(Status)==false)
								{
									KdPrint(("!!!!! FILE SYSTEM MINI FILTER REGISTRATION FAILED to CREATE KEY VALUE [%wZ] with ERROR CODE [%lX] !!!\n",FlagsName,Status));
									break;
								}
							}
							while(false);

							if (NT_SUCCESS(Status)==false)
							{
								InstanceSubKey.DeleteValueKey(AltitudeName);
								InstanceSubKey.DeleteValueKey(FlagsName);

								InstanceSubKey.DeleteKey();
							}
						}
						else
						{
							KdPrint(("!!!!! FILE SYSTEM MINI FILTER REGISTRATION FAILED to CREATE KEY [%wZ] with ERROR CODE [%lX] !!!\n",InstanceName,Status));
							break;
						}
					}
					while(false);

					if (NT_SUCCESS(Status)==false)
					{
						SubKey.DeleteValueKey(InstanceName);

						SubKey.DeleteKey();
					}
				}
				else
				{
					KdPrint(("!!!!! FILE SYSTEM MINI FILTER REGISTRATION FAILED to CREATE KEY [%wZ] with ERROR CODE [%lX] !!!\n",SubKeyName,Status));
				}
			}
			else
			{
				KdPrint(("!!!!! FILE SYSTEM MINI FILTER REGISTRATION FAILED to OPEN KEY [%wZ] with ERROR CODE [%lX] !!!\n",*RegistryPath,Status));
			}
		}

		if (NT_SUCCESS(Status)==false)
		{
			ExFreePoolWithTag(Buffer,MY_TAG);
			Buffer=nullptr;
		}
	}
	else
	{
		KdPrint(("!!!!! FILE SYSTEM MINI FILTER REGISTRATION FAILED to ALLOCATE MEMORY !!!\n"));

		Status=STATUS_INSUFFICIENT_RESOURCES;
	}

	return(Status);
}
//----------------------------------------------------------------------------------------------------------------------
NTSTATUS CMiniFilterRegistryHelpers::DeleteRegistryKeys(const WCHAR* InstanceNameBuffer)
{
	NTSTATUS													Status;
	UNICODE_STRING												SubKeyName=RTL_CONSTANT_STRING(L"Instances");
	UNICODE_STRING												DefaultInstanceName=RTL_CONSTANT_STRING(L"DefaultInstance");
	UNICODE_STRING												AltitudeName=RTL_CONSTANT_STRING(L"Altitude");
	UNICODE_STRING												FlagsName=RTL_CONSTANT_STRING(L"Flags");

	UNICODE_STRING												InstanceName;

	RtlInitUnicodeString(&InstanceName,InstanceNameBuffer);

	{
		OBJECT_ATTRIBUTES										KeyAttributes=RTL_CONSTANT_OBJECT_ATTRIBUTES(&MRegistryPath,OBJ_KERNEL_HANDLE);
		CRegistryKeyOpen										Key(Status,KEY_WRITE,KeyAttributes);

		if (NT_SUCCESS(Status)==true)
		{
			OBJECT_ATTRIBUTES									SubKeyAttributes;

			InitializeObjectAttributes(&SubKeyAttributes,&SubKeyName,OBJ_KERNEL_HANDLE,Key.GetKey(),nullptr);

			CRegistryKeyOpen									SubKey(Status,KEY_WRITE,SubKeyAttributes);

			if (NT_SUCCESS(Status)==true)
			{
				OBJECT_ATTRIBUTES								InstanceSubKeyAttributes;

				InitializeObjectAttributes(&InstanceSubKeyAttributes,&InstanceName,OBJ_KERNEL_HANDLE,SubKey.GetKey(),nullptr);

				CRegistryKeyOpen								InstanceSubKey(Status,KEY_WRITE,InstanceSubKeyAttributes);

				if (NT_SUCCESS(Status)==true)
				{
					InstanceSubKey.DeleteValueKey(AltitudeName);
					InstanceSubKey.DeleteValueKey(FlagsName);

					InstanceSubKey.DeleteKey();
				}
				else
				{
					KdPrint(("!!!!! FILE SYSTEM MINI FILTER UNREGISTRATION FAILED to OPEN KEY [%wZ] with ERROR CODE [%lX] !!!\n",InstanceName,Status));
				}

				SubKey.DeleteValueKey(DefaultInstanceName);

				SubKey.DeleteKey();
			}
			else
			{
				KdPrint(("!!!!! FILE SYSTEM MINI FILTER UNREGISTRATION FAILED to OPEN KEY [%wZ] with ERROR CODE [%lX] !!!\n",SubKeyName,Status));
			}
		}
		else
		{
			KdPrint(("!!!!! FILE SYSTEM MINI FILTER UNREGISTRATION FAILED to OPEN KEY [%wZ] with ERROR CODE [%lX] !!!\n",MRegistryPath,Status));
		}
	}

	ExFreePoolWithTag(MRegistryPath.Buffer,MY_TAG);

	MRegistryPath.Length=0;
	MRegistryPath.MaximumLength=0;
	MRegistryPath.Buffer=nullptr;

	return(Status);
}
//----------------------------------------------------------------------------------------------------------------------