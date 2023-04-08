//-------------------------------------------------------------------------------------------------------
#include <wdm.h>
#include <initguid.h>
 //-------------------------------------------------------------------------------------------------------
#include "Driver.h"
#include "GUIDS.h"
#include "Macros.h"
//-------------------------------------------------------------------------------------------------------
#pragma warning(disable:4127)
//-------------------------------------------------------------------------------------------------------
// !!!!! DRIVER sa sice FORMALNE NENAINSTALUJE - pocas DRIVER DEPLOY (vyvolany REBUILD [MySkeletonDriver Package]) vyhlasi DEPLOYMENT proces CHYBU, ale v skutocnosti DRIVER je NAINSTALOVANY. Kedze vsak AddDevice() vrati STATUS_UNSUCCESSFUL, tak INSTALLER to vyhodnoti ako NEUSPESNE NAINSTALOVANIE DRIVER. Avsak LOGY sa ZAPISU a je ich mozne citat cez TOOL [DebugView.exe].
//-------------------------------------------------------------------------------------------------------
VOID DriverUnload(IN PDRIVER_OBJECT DriverObject);
NTSTATUS AddDevice(IN PDRIVER_OBJECT DriverObject, IN PDEVICE_OBJECT PDO);
NTSTATUS DispatchPNP(PDEVICE_OBJECT FDO, PIRP IRP);
NTSTATUS DispatchPower(PDEVICE_OBJECT FDO, PIRP IRP);
NTSTATUS DispatchSystemControl(PDEVICE_OBJECT FDO, PIRP IRP);
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
#pragma PAGEDCODE
// !!! Kedze DriverEntry() je EXPORTED tam NESMIE MAT MANGLED NAME a teda MUSI byt oznacena direktivou 'extern c'.
// !!! PARAMETER DriverObject je DRIVER OBJECT, ktory musi DriverEntry() INICIALIZOVAT.
// DRUHY PAREMTER typu STRING sa zvycajne nepouziva. Je NON-PERSISTENT a teda v pripade pouzitia je nutne vytvorit jeho KOPIU.
extern "C" NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING)
{
	KdPrint((DRIVERNAME " - FUNCTION DriverEntry(): DriverObject [%p] !\n",DriverObject));
	
	// Initializuju sa FUNCTION POINTERS.
	// !!! Nastavi sa DRIVER UNLOAD FUNCTION.
	DriverObject->DriverUnload=DriverUnload;
	// !!! Nastavi sa ADD DEVICE FUNCTION.
	DriverObject->DriverExtension->AddDevice=AddDevice;

	DriverObject->MajorFunction[IRP_MJ_PNP]=DispatchPNP;
	DriverObject->MajorFunction[IRP_MJ_POWER]=DispatchPower;
	DriverObject->MajorFunction[IRP_MJ_SYSTEM_CONTROL]=DispatchSystemControl;

	RTL_OSVERSIONINFOW											Version={0};

	Version.dwOSVersionInfoSize=sizeof(OSVERSIONINFOW);

	// Ziska sa WINDOWS VERSION.
	RtlGetVersion(&Version);

	KdPrint((DRIVERNAME " - FUNCTION DriverEntry(): MAJOR VERSION [%d], MINOR VERSION [%d], BUILD NUMBER [%d], PLATFORM ID [%d], CSDVersion [%s] !\n",Version.dwMajorVersion,Version.dwMinorVersion,Version.dwBuildNumber,Version.dwPlatformId,Version.szCSDVersion));

	return(STATUS_SUCCESS);

	// !!!!! Ak sa vrati ERROR CODE, tak sa DriverUnload() NEZAVOLA.
	//return(STATUS_UNSUCCESSFUL);
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
#pragma PAGEDCODE
VOID DriverUnload(IN PDRIVER_OBJECT DriverObject)
{
	PAGED_CODE();
	KdPrint((DRIVERNAME " - FUNCTION DriverUnload(): DriverObject [%p] !\n",DriverObject));
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
#pragma PAGEDCODE
NTSTATUS AddDevice(IN PDRIVER_OBJECT DriverObject, IN PDEVICE_OBJECT PhysicalDeviceObject)
{
	PAGED_CODE();
	KdPrint((DRIVERNAME " - FUNCTION AddDevice(): DriverObject [%p], PhysicalDeviceObject [%p] !\n",DriverObject,PhysicalDeviceObject));

	NTSTATUS													Status;
	PDEVICE_OBJECT												NewDeviceObject=NULL;

	/*
	// !!!!! OPTIONALY je mozne definovat DEVICE_OBJECT NAME. No v sucasnosti sa to az tak nepouziva. APPLICATIONS najcastejsie pristupuju k DEVICES NIE cez NAMES, ale cez DEVICE INTERFACES.

	static LONG													UniqueDeviceID=0;

	InterlockedIncrement(&UniqueDeviceID);

	WCHAR														DeviceNameBuffer[100];

	// !!! DEVICE_OBJECT NAME by malo byt v [Device] NAMESPACE.
	swprintf_s(DeviceNameBuffer,L"\\Device\\MySkeletonDriver%d",UniqueDeviceID);

	UNICODE_STRING												DeviceName;

	// Vytvori sa DEVICE_OBJECT NAME.
	RtlInitUnicodeString(&DeviceName,DeviceNameBuffer);
	*/

	// !!!!! Vytvori sa FUNCTION DEVICE OBJECT, ktory reprezentuje HW DEVICE, ktory je MANAGED tymto DRIVER.
	// !!! DEVICE_OBJECT NAME sa zasle ako 3. PARAMETER. Toto je IBA OPTIONAL. DEVICE_OBJECT by NEMALI mat NAMES.
	// !!!!! DEVICE_OBJECT NAME sa zobrazi IBA ak AddDevice() vrati STATUS_SUCCESS. Vtedy sa pridaju ENTRIES [Device\MySkeletonDriver1] a [Driver\MySkeletonDriver]. Ak AddDevice() vrati STATUS_UNSUCCESSFUL, tak sa ZIADNE ENTRIES NEPRIDAJU.
	// !!! DEVICE_EXTENSION je CUSTOM STRUCTURE, ktora moze obsahovat LUBOVOLNE DATA asociovane s DEVICE_OBJECT.
	Status=IoCreateDevice(DriverObject,sizeof(DEVICE_EXTENSION),NULL,FILE_DEVICE_UNKNOWN,FILE_DEVICE_SECURE_OPEN,FALSE,&NewDeviceObject);
	//Status=IoCreateDevice(DriverObject,sizeof(DEVICE_EXTENSION),&DeviceName,FILE_DEVICE_UNKNOWN,FILE_DEVICE_SECURE_OPEN,FALSE,&NewDeviceObject);

	// Vytvorenie DEVICE OBJECT ZLYHALO.
	if (NT_SUCCESS(Status)==false)
	{
		KdPrint((DRIVERNAME " - FUNCTION AddDevice(): IoCreateDevice() FAILED [%X] !\n",Status));
		return(Status);
	}
	
	PDEVICE_EXTENSION											DeviceExtensionData=(PDEVICE_EXTENSION) NewDeviceObject->DeviceExtension;

	do
	{
		DeviceExtensionData->DeviceObject=NewDeviceObject;
		DeviceExtensionData->PDO=PhysicalDeviceObject;

		// DEVICE OBJECT sa nalinkuje do STACK veduci k PDO.
		// !!! FUNCTION IoAttachDeviceToDeviceStack() vracia POINTER na povodny VRCHOL STACKU - na DEVICE_OBJECT, ktory je NIZSIE v STACKU.
		DeviceExtensionData->LowerDeviceObject=IoAttachDeviceToDeviceStack(NewDeviceObject,PhysicalDeviceObject);

		// DEVICE sa nepodarilo pripojit.
		if (DeviceExtensionData->LowerDeviceObject==NULL)
		{
			KdPrint((DRIVERNAME " - FUNCTION AddDevice(): IoAttachDeviceToDeviceStack() FAILED !\n"));
			// !!! Ak sa DEVICE_OBJECT NEPODARILO pridat na VRCHOL DRIVER STACK (RETURN VALUE IoAttachDeviceToDeviceStack() je NULL), potom AddDevice() MUSI vratit hodnotu STATUS_DEVICE_REMOVED.
			Status=STATUS_DEVICE_REMOVED;
			break;
		}

		// !!! Niektore FLAGS sa daju nastavit IBA v AddDevice(), lebo ostatne DRIVERS v DRIVER STACK si ich ulozia a pripadnu neskorsiu zmenu nie je mozne standardne zaslat do tychto DRIVERS.
		// Nastavia sa POWER MANAGEMENT FLAGS v DEVICE OBJECT.
		NewDeviceObject->Flags|=DO_POWER_PAGABLE;

		// !!! FUNCTION IoRegisterDeviceInterface() vykonava 2 cinnosti.
		// A. Zaregistruje DEVICE INTERFACE CLASS ak predtym nebol zaregistrovany.
		// B. Vytvori INSTANCIU DEVICE INTERFACE CLASS, ktoru DRIVER moze pouzit, aby umoznil APPLICATIONS pristupovat cez tento DEVICE INTERFACE k DEVICE.
		Status=IoRegisterDeviceInterface(PhysicalDeviceObject,&GUID_DEVINTERFACE_MY_SKELETON_DRIVER,NULL,&DeviceExtensionData->InterfaceName);

		// Nepodarilo sa zaregistrovat INTERFACE.
		if (NT_SUCCESS(Status)==false)
		{
			KdPrint((DRIVERNAME " - FUNCTION AddDevice(): IoRegisterDeviceInterface() FAILED [%X] !\n",Status));
			break;
		}

		// !!! Vytvori sa REMOVE LOCK, ktory sa pouziva pri detekcii kedy je mozne DEVICE_OBJECT odstranit z MEMORY.
		IoInitializeRemoveLock(&DeviceExtensionData->RemoveLock,0,0,0);

		// !!! Vymaze sa FLAG DO_DEVICE_INITIALIZING, takze DRIVER bude moct dostavat IRP REQUESTS.
		NewDeviceObject->Flags&=~DO_DEVICE_INITIALIZING;

		KdPrint((DRIVERNAME " - FUNCTION AddDevice(): DEVICE_OBJECT INITIALIZED, Flags [%X], Characteristics [%X], AlignmentRequirement [%X] !\n",NewDeviceObject->Flags,NewDeviceObject->Characteristics,NewDeviceObject->AlignmentRequirement));

		// !!!!! Simulacia NEUSPESNEJ incializacie DRIVER.
		// !!!!! Kedze tento DRIVER nie je kompletne implementovany, tak sa vrati UMYSELNE ERROR.
		Status=STATUS_UNSUCCESSFUL;
	}
	while(FALSE);

	if (NT_SUCCESS(Status)==false)
	{
		if (DeviceExtensionData->InterfaceName.Buffer!=NULL)
		{
			RtlFreeUnicodeString(&DeviceExtensionData->InterfaceName);
		}

		if (DeviceExtensionData->LowerDeviceObject!=NULL)
		{
			IoDetachDevice(DeviceExtensionData->LowerDeviceObject);
		}

		if (NewDeviceObject!=NULL)
		{
			// !!! Pri ERROR je NUTNE uvolnit vytvoreny DEVICE OBJECT.
			IoDeleteDevice(NewDeviceObject);
			NewDeviceObject=NULL;
		}
	}

	return(Status);
}
//-------------------------------------------------------------------------------------------------------
#pragma PAGEDCODE
NTSTATUS DispatchPNP(PDEVICE_OBJECT FDO, PIRP IRP)
{
	PAGED_CODE();
	
	KdPrint((DRIVERNAME " - FUNCTION DispatchPNP(): DeviceObject [%p], IRP [%p] !\n",FDO,IRP));

	return(STATUS_UNSUCCESSFUL);
}
//-------------------------------------------------------------------------------------------------------
#pragma PAGEDCODE
NTSTATUS DispatchPower(PDEVICE_OBJECT FDO, PIRP IRP)
{
	PAGED_CODE();

	KdPrint((DRIVERNAME " - FUNCTION DispatchPower(): DeviceObject [%p], IRP [%p] !\n",FDO,IRP));

	return(STATUS_UNSUCCESSFUL);
}
//-------------------------------------------------------------------------------------------------------
#pragma PAGEDCODE
NTSTATUS DispatchSystemControl(PDEVICE_OBJECT FDO, PIRP IRP)
{
	PAGED_CODE();

	KdPrint((DRIVERNAME " - FUNCTION DispatchSystemControl(): DeviceObject [%p], IRP [%p] !\n",FDO,IRP));

	return(STATUS_UNSUCCESSFUL);
}
//-------------------------------------------------------------------------------------------------------