using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Identity;
//----------------------------------------------------------------------------------------------------------------------
namespace UsingCoreIdentity.Security
{
//----------------------------------------------------------------------------------------------------------------------
	// !!! CLASS implementuje CUSTOM USER VALIDATOR implementaciou INTERFACE [UserValidator<CCustomUser>].
	public sealed class CComplexUserValidator : UserValidator<CCustomUser>
	{
//----------------------------------------------------------------------------------------------------------------------
		private static readonly string[]						MValidEmailDomains;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		static CComplexUserValidator()
		{
			List<string>										ValidEmailDomains=new List<string>();

			ValidEmailDomains.Add("@EXAMPLE.COM");

			MValidEmailDomains=ValidEmailDomains.ToArray();
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		// !!! METHOD vykonava CUSTOM CHECKS.
		public override async Task<IdentityResult> ValidateAsync(UserManager<CCustomUser> Manager, CCustomUser User)
		{
			List<IdentityError>									Errors=new List<IdentityError>();

			// !!! Zavola sa BASE CLASS, ktora robi DEFAULT PASSWORD VALIDATION.
			IdentityResult										BaseResult=await base.ValidateAsync(Manager,User);

			// !!! Ak DEFAULT USER VALIDATION najde ERRORS, tie sa pridaju do ERROR COLLECTION.
			if (BaseResult.Succeeded==false)
			{
				Errors.AddRange(BaseResult.Errors);
			}

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
				IdentityResult									Result=IdentityResult.Success;

				return(Result);
			}
			else
			{
				// !!! Vytvori sa ERROR RESPONSE.
				IdentityResult									Result=IdentityResult.Failed(Errors.ToArray());

				return(Result);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------