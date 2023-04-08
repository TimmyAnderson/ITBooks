using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Security.Principal;
using System.IdentityModel.Policy;
using System.IdentityModel.Claims;
//-------------------------------------------------------------------------------------------------------
namespace Service
{
//-------------------------------------------------------------------------------------------------------
	// Trieda predstavuje implementaciu IAuthorizationPolicy, ktora sluzi na VYTVORENIE IPrincipal na ZAKLADE CLAIM SET.
	public class CMyCustomAuthorizationPolicy : IAuthorizationPolicy
	{
//-------------------------------------------------------------------------------------------------------
		private string											MID=Guid.NewGuid().ToString();
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public ClaimSet											Issuer
		{
			get
			{
				return(ClaimSet.System);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public string											Id
		{
			get
			{
				return(MID);
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		// KLUCOVA METODA, ktora musi na ZAKLADE ClaimSet VYTVORIT IPrincipal.
		public bool Evaluate(EvaluationContext EC, ref object State)
		{
			try
			{
				Console.WriteLine("CMyCustomAuthorizationPolicy.Evaluate() STARTED !");

				object				Obj;

				// Musi obsahovat 'Identities'
				if (EC.Properties.TryGetValue("Identities", out Obj)==false)
					return(false);

				IList<IIdentity>	Identities=Obj as IList<IIdentity>;

				if (Identities==null || Identities.Count<=0)
					return(false);

				// !!! VYTVORIM CUSTOM IPrincipal.
				EC.Properties["Principal"]=new CMyCustomPrincipal(Identities[0]);
	                
				return(true);
			}
			finally
			{
				Console.WriteLine("CMyCustomAuthorizationPolicy.Evaluate() FINISHED !");
			}
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------