using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Identity;
//----------------------------------------------------------------------------------------------------------------------
namespace SecuringWebServicesBearerTokens.Security
{
//----------------------------------------------------------------------------------------------------------------------
	// !!! CLASS implementuje CUSTOM PASSWORD VALIDATOR implementaciou INTERFACE [IPasswordValidator<CCustomUser>].
	public sealed class CSimplePasswordValidator : IPasswordValidator<CCustomUser>
	{
//----------------------------------------------------------------------------------------------------------------------
		private static readonly HashSet<string>					MDictionaryPasswords;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		static CSimplePasswordValidator()
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
		public Task<IdentityResult> ValidateAsync(UserManager<CCustomUser> Manager, CCustomUser User, string Password)
		{
			List<IdentityError>									Errors=new List<IdentityError>();
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