using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Identity;
//----------------------------------------------------------------------------------------------------------------------
namespace UsingCoreIdentity.Security
{
//----------------------------------------------------------------------------------------------------------------------
	// !!! CLASS implementuje CUSTOM USER VALIDATOR implementaciou INTERFACE [IUserValidator<CCustomUser>].
	public sealed class CSimpleUserValidator : IUserValidator<CCustomUser>
	{
//----------------------------------------------------------------------------------------------------------------------
		private static readonly string[]						MValidEmailDomains;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		static CSimpleUserValidator()
		{
			List<string>										ValidEmailDomains=new List<string>();

			ValidEmailDomains.Add("@EXAMPLE.COM");

			MValidEmailDomains=ValidEmailDomains.ToArray();
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		// !!! METHOD vykonava CUSTOM CHECKS.
		public Task<IdentityResult> ValidateAsync(UserManager<CCustomUser> Manager, CCustomUser User)
		{
			List<IdentityError>									Errors=new List<IdentityError>();
			bool												IsValidDomain=false;
			string												EmailToUpper=User.Email.ToUpper();

			foreach(string ValidEmailDomain in MValidEmailDomains)
			{
				if (EmailToUpper.EndsWith(ValidEmailDomain)==true)
				{
					IsValidDomain=true;
					break;
				}
			}

			if (IsValidDomain==false)
			{
				IdentityError									Error=new IdentityError();

				Error.Code="InvalidEmailDomainName";
				Error.Description="INVALID EMAIL DOMAIN NAME !";

				Errors.Add(Error);
			}

			if (Errors.Count==0)
			{
				// !!! Vytvori sa OK RESPONSE.
				Task<IdentityResult>							Result=Task.FromResult(IdentityResult.Success);

				return(Result);
			}
			else
			{
				// !!! Vytvori sa ERROR RESPONSE.
				IdentityResult									ResultData=IdentityResult.Failed(Errors.ToArray());
				Task<IdentityResult>							Result=Task.FromResult(ResultData);

				return(Result);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------