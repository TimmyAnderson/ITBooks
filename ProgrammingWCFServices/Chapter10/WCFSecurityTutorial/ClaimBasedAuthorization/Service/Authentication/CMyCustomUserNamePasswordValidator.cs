using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IdentityModel.Selectors;
using System.ServiceModel.Security;
using System.IdentityModel.Tokens;
//-------------------------------------------------------------------------------------------------------
namespace Service
{
//-------------------------------------------------------------------------------------------------------
	// Trieda realizuje CUSTOM AUTHENTIFICATION.
	public class CMyCustomUserNamePasswordValidator : UserNamePasswordValidator
	{
//-------------------------------------------------------------------------------------------------------
		public override void Validate(string UserName, string Password)
		{
			try
			{
				Console.WriteLine("CMyCustomUserNamePasswordValidator.Validate() STARTED !");

				if (UserName!="Timmy" && UserName!="Atreyu" && UserName!="Jenny")
					throw(new SecurityTokenValidationException("INVALID USER NAME !"));

				if (Password!="XXX")
					throw(new SecurityTokenValidationException("INVALID PASSWORD !"));
			}
			finally
			{
				Console.WriteLine("CMyCustomUserNamePasswordValidator.Validate() FINISHED !");
			}
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------