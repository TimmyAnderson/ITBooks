using System;
using System.Collections.Generic;
using System.Text;
using System.Diagnostics;
using System.Net.Security;
using System.Security.Principal;
//-------------------------------------------------------------------------------------------------------
namespace MEPLibrary
{
//-------------------------------------------------------------------------------------------------------
	public class CDebugHelper
	{
//-------------------------------------------------------------------------------------------------------
		public static string GetMethodName()
		{
			StackFrame		SF=new StackFrame(1);

			return(string.Format("{0}.{1}()",SF.GetMethod().DeclaringType.Name,SF.GetMethod().Name));
		}
//-------------------------------------------------------------------------------------------------------
		public static string GetExceptionString(Exception E)
		{
			StackFrame		SF=new StackFrame(1);

			return(string.Format("EXCEPTION ({0}): {1}.{2}() - {3} !",E.GetType().Name,SF.GetMethod().DeclaringType.Name,SF.GetMethod().Name,E.Message));
		}
//-------------------------------------------------------------------------------------------------------
		public static string GetExceptionString(Exception E, string Prefix)
		{
			StackFrame		SF=new StackFrame(1);

			return(string.Format("{0} ({1}): {2}.{3}() - {4} !",Prefix,E.GetType().Name,SF.GetMethod().DeclaringType.Name,SF.GetMethod().Name,E.Message));
		}
//-------------------------------------------------------------------------------------------------------
		public static string GetMethodCallString()
		{
			StackFrame		SF=new StackFrame(1);

			return(string.Format("{0}.{1}() called !",SF.GetMethod().DeclaringType.Name,SF.GetMethod().Name));
		}
//-------------------------------------------------------------------------------------------------------
		public static string GetConstructorCallString()
		{
			StackFrame		SF=new StackFrame(1);

			return(string.Format("{0}.CONSTRUCTOR() called !",SF.GetMethod().DeclaringType.Name));
		}
//-------------------------------------------------------------------------------------------------------
		public static string GetDestructorCallString()
		{
			StackFrame		SF=new StackFrame(1);

			return(string.Format("{0}.DESTRUCTOR() called !",SF.GetMethod().DeclaringType.Name));
		}
//-------------------------------------------------------------------------------------------------------
		public static string GetMethodCallString(int Position)
		{
			StackFrame		SF=new StackFrame(1);

			return(string.Format("{0}.{1}() called {2} !",SF.GetMethod().DeclaringType.Name,SF.GetMethod().Name,Position));
		}
//-------------------------------------------------------------------------------------------------------
		public static void GetWindowsUserInfo(WindowsIdentity WI)
		{
			Console.WriteLine(string.Format("Name: {0} !",WI.Name));

			Console.WriteLine(string.Format("IsAuthenticated: {0} !",WI.IsAuthenticated));
			Console.WriteLine(string.Format("AuthenticationType: {0} !",WI.AuthenticationType));
			Console.WriteLine(string.Format("Groups:"));
			
			foreach(IdentityReference IR in WI.Groups)
			{
				NTAccount		NTA=(NTAccount) IR.Translate(typeof(NTAccount));

				Console.WriteLine(string.Format("\t{0} !",NTA.Value));
			}
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------