using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Net.Security;
using System.ServiceModel;
using System.ServiceModel.Channels;
using System.Security.Permissions;
//-------------------------------------------------------------------------------------------------------
namespace SharedLibrary
{
//-------------------------------------------------------------------------------------------------------
	// Nastavenim ProtectionLevel na EncryptAndSign VYZADUJEM, aby BINDING BOL SECURE. Ak nie je, tak sa hodi pr vytvarani HOST EXCEPTION.
	[ServiceContract(ProtectionLevel=ProtectionLevel.EncryptAndSign)]
	public interface IMSWindowsService
	{
//-------------------------------------------------------------------------------------------------------
		[OperationContract(ProtectionLevel=ProtectionLevel.EncryptAndSign)]
		void JustForAdministrator();
		[OperationContract(ProtectionLevel=ProtectionLevel.EncryptAndSign)]
		void JustForAdministrators();
		[OperationContract(ProtectionLevel=ProtectionLevel.EncryptAndSign)]
		void ForAll();
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------