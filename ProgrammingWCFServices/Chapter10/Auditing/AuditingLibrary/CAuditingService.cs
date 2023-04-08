using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;
using System.Transactions;
using System.Runtime.Serialization;
using System.Runtime.CompilerServices;
using System.ServiceModel;
using System.Security.Principal;
using System.Security.Permissions;
using System.ServiceModel.Security;
//-------------------------------------------------------------------------------------------------------
// 1. Auditovanie sluzi na zapis informacii o uspesnom, alebo neuspesnom prihlaseni.
// 2. Audit sa zapisuje do systemovych eventov.
// 3. Audit sa definuje nastavenim a pridanim ServiceSecurityAuditBehavior medzi behaviors.
// !!! 4. Audit sa tyka IBA AUTENTIFIKACIE a nie autorizacie. Teda success je ak sa uspesne autentifikuje pricom moze zlyhat autorizacia.
//-------------------------------------------------------------------------------------------------------
namespace AuditingLibrary
{
//-------------------------------------------------------------------------------------------------------
	[ServiceBehavior(InstanceContextMode=InstanceContextMode.PerCall)]
	public class CAuditingService : IAuditingContract, IDisposable
	{
//-------------------------------------------------------------------------------------------------------
		public CAuditingService()
		{
			Console.WriteLine(CDebugHelper.GetConstructorCallString());
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void IsAlive()
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());
		}
//-------------------------------------------------------------------------------------------------------
		public void DoAudit1()
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());

			Console.WriteLine("AUTORIZHED");
		}
//-------------------------------------------------------------------------------------------------------
		[PrincipalPermission(SecurityAction.Demand,Role="Administrators")]
		public void DoAudit2()
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());

			Console.WriteLine("AUTORIZHED");
		}
//-------------------------------------------------------------------------------------------------------
		[PrincipalPermission(SecurityAction.Demand,Role="Users")]
		public void DoAudit3()
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());

			Console.WriteLine("AUTORIZHED");
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void Dispose()
		{
			Console.WriteLine(CDebugHelper.GetDestructorCallString());
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------