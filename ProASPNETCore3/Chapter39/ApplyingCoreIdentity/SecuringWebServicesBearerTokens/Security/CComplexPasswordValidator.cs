using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Identity;
//----------------------------------------------------------------------------------------------------------------------
namespace SecuringWebServicesBearerTokens.Security
{
//----------------------------------------------------------------------------------------------------------------------
	// !!! CLASS implementuje CUSTOM PASSWORD VALIDATOR zdedenim z CLASS [PasswordValidator<CCustomUser>].
	public sealed class CComplexPasswordValidator : PasswordValidator<CCustomUser>
	{
//----------------------------------------------------------------------------------------------------------------------
		private static readonly HashSet<string>					MDictionaryPasswords;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		static CComplexPasswordValidator()
		{
			MDictionaryPasswords=new HashSet<string>();

			MDictionaryPasswords.Add("aaa");
			MDictionaryPasswords.Add("bbb");
			MDictionaryPasswords.Add("ccc");
			MDictionaryPasswords.Add("AAAaaa111...");
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		// !!! METHOD vykonava CUSTOM CHECKS.
		public override async Task<IdentityResult> ValidateAsync(UserManager<CCustomUser> Manager, CCustomUser User, string Password)
		{
			List<IdentityError>									Errors=new List<IdentityError>();

			// !!! Zavola sa BASE CLASS, ktora robi DEFAULT PASSWORD VALIDATION.
			IdentityResult										BaseResult=await base.ValidateAsync(Manager,User,Password);

			// !!! Ak DEFAULT PASSWORD VALIDATION najde ERRORS, tie sa pridaju do ERROR COLLECTION.
			if (BaseResult.Succeeded==false)
			{
				Errors.AddRange(BaseResult.Errors);
			}

			string												UserNameToUpper=User.UserName.ToUpper();
			string												PasswordNameToUpper=Password.ToUpper();

			if (UserNameToUpper==PasswordNameToUpper)
			{
				IdentityError									Error=new IdentityError();

				Error.Code="PasswordContainsUserName";
				Error.Description="PASSWORD contains USER NAME !";

				Errors.Add(Error);
			}

			if (MDictionaryPasswords.Contains(Password)==true)
			{
				IdentityError									Error=new IdentityError();

				Error.Code="PasswordIsDictionaryPassword";
				Error.Description="PASSWORD is DICTIONARY PASSWORD !";

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