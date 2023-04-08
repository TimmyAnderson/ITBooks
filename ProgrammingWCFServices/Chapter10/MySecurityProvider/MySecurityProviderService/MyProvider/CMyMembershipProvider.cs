using System;
using System.Collections.Generic;
using System.Text;
using System.Web.Security;
//-------------------------------------------------------------------------------------------------------
namespace MySecurityProviderService
{
//-------------------------------------------------------------------------------------------------------
	public class CMyMembershipProvider : MembershipProvider
	{
//-------------------------------------------------------------------------------------------------------
		public override string									ApplicationName
		{
			get
			{
				Console.WriteLine(CDebugHelper.GetMethodCallString());
				throw(new Exception("The method or operation is not implemented."));
			}
			set
			{
				Console.WriteLine(CDebugHelper.GetMethodCallString());
				throw(new Exception("The method or operation is not implemented."));
			}
		}
//-------------------------------------------------------------------------------------------------------
		public override bool									EnablePasswordReset
		{
			get
			{
				Console.WriteLine(CDebugHelper.GetMethodCallString());
				throw(new Exception("The method or operation is not implemented."));
			}
		}
//-------------------------------------------------------------------------------------------------------
		public override bool									EnablePasswordRetrieval
		{
			get
			{
				Console.WriteLine(CDebugHelper.GetMethodCallString());
				throw(new Exception("The method or operation is not implemented."));
			}
		}
//-------------------------------------------------------------------------------------------------------
		public override int										MaxInvalidPasswordAttempts
		{
			get
			{
				Console.WriteLine(CDebugHelper.GetMethodCallString());
				throw(new Exception("The method or operation is not implemented."));
			}
		}
//-------------------------------------------------------------------------------------------------------
		public override int										MinRequiredNonAlphanumericCharacters
		{
			get
			{
				Console.WriteLine(CDebugHelper.GetMethodCallString());
				throw(new Exception("The method or operation is not implemented."));
			}
		}
//-------------------------------------------------------------------------------------------------------
		public override int										MinRequiredPasswordLength
		{
			get
			{
				Console.WriteLine(CDebugHelper.GetMethodCallString());
				throw(new Exception("The method or operation is not implemented."));
			}
		}
//-------------------------------------------------------------------------------------------------------
		public override int										PasswordAttemptWindow
		{
			get
			{
				Console.WriteLine(CDebugHelper.GetMethodCallString());
				throw(new Exception("The method or operation is not implemented."));
			}
		}
//-------------------------------------------------------------------------------------------------------
		public override MembershipPasswordFormat				PasswordFormat
		{
			get
			{
				Console.WriteLine(CDebugHelper.GetMethodCallString());
				throw(new Exception("The method or operation is not implemented."));
			}
		}
//-------------------------------------------------------------------------------------------------------
		public override string									PasswordStrengthRegularExpression
		{
			get
			{
				Console.WriteLine(CDebugHelper.GetMethodCallString());
				throw(new Exception("The method or operation is not implemented."));
			}
		}
//-------------------------------------------------------------------------------------------------------
		public override bool									RequiresQuestionAndAnswer
		{
			get
			{
				Console.WriteLine(CDebugHelper.GetMethodCallString());
				throw(new Exception("The method or operation is not implemented."));
			}
		}
//-------------------------------------------------------------------------------------------------------
		public override bool									RequiresUniqueEmail
		{
			get
			{
				Console.WriteLine(CDebugHelper.GetMethodCallString());
				throw(new Exception("The method or operation is not implemented."));
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public override bool ChangePassword(string Username, string OldPassword, string NewPassword)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());
			throw(new Exception("The method or operation is not implemented."));
		}
//-------------------------------------------------------------------------------------------------------
		public override bool ChangePasswordQuestionAndAnswer(string Username, string Password, string NewPasswordQuestion, string NewPasswordAnswer)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());
			throw(new Exception("The method or operation is not implemented."));
		}
//-------------------------------------------------------------------------------------------------------
		public override MembershipUser CreateUser(string Username, string Password, string Email, string PasswordQuestion, string PasswordAnswer, bool IsApproved, object ProviderUserKey, out MembershipCreateStatus Status)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());
			throw(new Exception("The method or operation is not implemented."));
		}
//-------------------------------------------------------------------------------------------------------
		public override bool DeleteUser(string Username, bool DeleteAllRelatedData)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());
			throw(new Exception("The method or operation is not implemented."));
		}
//-------------------------------------------------------------------------------------------------------
		public override MembershipUserCollection FindUsersByEmail(string EmailToMatch, int PageIndex, int PageSize, out int TotalRecords)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());
			throw(new Exception("The method or operation is not implemented."));
		}
//-------------------------------------------------------------------------------------------------------
		public override MembershipUserCollection FindUsersByName(string UsernameToMatch, int PageIndex, int PageSize, out int TotalRecords)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());
			throw(new Exception("The method or operation is not implemented."));
		}
//-------------------------------------------------------------------------------------------------------
		public override MembershipUserCollection GetAllUsers(int PageIndex, int PageSize, out int TotalRecords)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());
			throw(new Exception("The method or operation is not implemented."));
		}
//-------------------------------------------------------------------------------------------------------
		public override int GetNumberOfUsersOnline()
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());
			throw(new Exception("The method or operation is not implemented."));
		}
//-------------------------------------------------------------------------------------------------------
		public override string GetPassword(string Username, string Answer)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());
			throw(new Exception("The method or operation is not implemented."));
		}
//-------------------------------------------------------------------------------------------------------
		public override MembershipUser GetUser(string Username, bool UserIsOnline)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());
			throw(new Exception("The method or operation is not implemented."));
		}
//-------------------------------------------------------------------------------------------------------
		public override MembershipUser GetUser(object ProviderUserKey, bool UserIsOnline)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());
			throw(new Exception("The method or operation is not implemented."));
		}
//-------------------------------------------------------------------------------------------------------
		public override string GetUserNameByEmail(string Email)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());
			throw(new Exception("The method or operation is not implemented."));
		}
//-------------------------------------------------------------------------------------------------------
		public override string ResetPassword(string Username, string Answer)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());
			throw(new Exception("The method or operation is not implemented."));
		}
//-------------------------------------------------------------------------------------------------------
		public override bool UnlockUser(string UserName)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());
			throw(new Exception("The method or operation is not implemented."));
		}
//-------------------------------------------------------------------------------------------------------
		public override void UpdateUser(MembershipUser User)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());
			throw(new Exception("The method or operation is not implemented."));
		}
//-------------------------------------------------------------------------------------------------------
		public override bool ValidateUser(string Username, string Password)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());

			if (Username=="MySQLTest1" && Password=="aaaaaa1+")
				return(true);

			if (Username=="MySQLTest2" && Password=="aaaaaa2+")
				return(true);

			return(false);
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------