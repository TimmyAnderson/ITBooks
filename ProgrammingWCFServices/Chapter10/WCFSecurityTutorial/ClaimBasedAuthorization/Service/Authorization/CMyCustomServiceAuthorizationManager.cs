using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ServiceModel;
using System.IdentityModel.Claims;
using System.ServiceModel.Channels;
//-------------------------------------------------------------------------------------------------------
namespace Service
{
//-------------------------------------------------------------------------------------------------------
	// Trieda VYKONAVA SAMOTNU AUTHORZIATION. Teda zistuje CI NA DANU OPERACIU ma USER ACCESS.
	public class CMyCustomServiceAuthorizationManager : ServiceAuthorizationManager
	{
//-------------------------------------------------------------------------------------------------------
		private Dictionary<string,string[]>						MAuthorizationRules;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CMyCustomServiceAuthorizationManager()
		{
			MAuthorizationRules=new Dictionary<string,string[]>();

			MAuthorizationRules.Add("http://tempuri.org/IMyCustomAuthorizationService/Method1",new string[]{"Boys"});
			MAuthorizationRules.Add("http://tempuri.org/IMyCustomAuthorizationService/Method2",new string[]{"Girls"});
			MAuthorizationRules.Add("http://tempuri.org/IMyCustomAuthorizationService/Method3",new string[]{});
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		// Klucova metoda, ktora zisti, ci k danej OPERATION moze dany USER PRISTUPOVAT.
		protected override bool CheckAccessCore(OperationContext OC)
		{
			try
			{
				Console.WriteLine("CMyCustomServiceAuthorizationManager.CheckAccessCore() STARTED !");

				string							Action=OC.RequestContext.RequestMessage.Headers.Action;
				string							UserName=null;

				// Prechadzam vsetky Claim Set.
				foreach(ClaimSet ClaimSet in OC.ServiceSecurityContext.AuthorizationContext.ClaimSets)
				{
					// Prechadzam kazdy Claim.
					foreach (Claim Claim in ClaimSet)
					{
						// Hladam Claim typu NAME.
						if (string.Compare(Claim.ClaimType, "http://schemas.xmlsoap.org/ws/2005/05/identity/claims/name",true)==0)
						{
							UserName=(string) Claim.Resource;

							// Zistim, ci ma dany User opravnenie na danu operaciu.
							if (MAuthorizationRules.ContainsKey(Action)==false)
								return(false);

							string[]			RolesForOperation=MAuthorizationRules[Action];

							foreach(string Role in RolesForOperation)
								if (CRolesStore.AuthorizationStore.IsInRole(UserName,Role)==true)
									return(true);
						}
					}
				}

				return(false);
			}
			finally
			{
				Console.WriteLine("CMyCustomServiceAuthorizationManager.CheckAccessCore() FINISHED !");
			}
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------