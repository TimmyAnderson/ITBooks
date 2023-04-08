using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.ServiceModel;
using System.IdentityModel.Claims;
using System.ServiceModel.Channels;
//-------------------------------------------------------------------------------------------------------
namespace SharedLibrary
{
//-------------------------------------------------------------------------------------------------------
	public class CMyLogServiceAuthorizationManager : ServiceAuthorizationManager
	{
//-------------------------------------------------------------------------------------------------------
		protected override bool CheckAccessCore(OperationContext OC)
		{
			string							Action=OC.RequestContext.RequestMessage.Headers.Action;
			ReadOnlyCollection<ClaimSet>	Claims=OC.ServiceSecurityContext.AuthorizationContext.ClaimSets;

			bool							Ret=base.CheckAccessCore(OC);

			if (Claims.Count==0)
			{
				Console.WriteLine("CheckAccessCore() - EMPTY CLAIM SET !");
				return(Ret);
			}
			else
			{
				ClaimSet					CS=Claims[0];

				Console.WriteLine(string.Format("CheckAccessCore() - Action: {0}, Number of CLAIMS: {1}, Access: {2} !",Action,CS.Count,Ret));

				return(Ret);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public override bool CheckAccess(OperationContext OC)
		{
			string							Action=OC.RequestContext.RequestMessage.Headers.Action;
			bool							Ret=base.CheckAccess(OC);

			Console.WriteLine(string.Format("CheckAccess_1() - Action: {0}, Access: {1} !",Action,Ret));

			return(Ret);
		}
//-------------------------------------------------------------------------------------------------------
		public override bool CheckAccess(OperationContext OC, ref Message Message)
		{
			string							Action=OC.RequestContext.RequestMessage.Headers.Action;
			bool							Ret=base.CheckAccess(OC);

			Console.WriteLine(string.Format("CheckAccess_2() - Action: {0}, Access: {1} !",Action,Ret));

			return(Ret);
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------