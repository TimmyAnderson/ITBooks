using System;
using System.Collections.Generic;
using System.Text;
using System.Diagnostics;
//-------------------------------------------------------------------------------------------------------
namespace FTCSharedLibrary
{
//-------------------------------------------------------------------------------------------------------
/*
	Trieda obsahujuca pomocne metody.
*/
//-------------------------------------------------------------------------------------------------------
	public class CDebugHelper
	{
//-------------------------------------------------------------------------------------------------------
		public static string GetIntID(int Size)
		{
			Random				RND=new Random();
			string				ID=RND.Next().ToString();

			if (Size<=0)
				throw(new ArgumentOutOfRangeException("Size","Size must be greater of 0 !"));

			if (ID.Length>=Size)
			{
				return(ID.Substring(0,Size));
			}
			else
			{
				int				Diff=Size-ID.Length;
				StringBuilder	SB=new StringBuilder();

				for (int i=0;i<Diff;i++)
					SB.Append('0');

				SB.Append(ID);
				return(SB.ToString());
			}
		}
//-------------------------------------------------------------------------------------------------------
		public static string GetGUIDShortuct(Guid GUID, string Prefix)
		{
			string		GUIDShortcut=GUID.ToString().Substring(0,Math.Min(GUID.ToString().Length,5));

			if (Prefix!=null)
				return(string.Format("{0}_{1}",Prefix,GUIDShortcut));
			else
				return(string.Format("{0}",GUIDShortcut));
		}
//-------------------------------------------------------------------------------------------------------
		public static string GetIDShortuct(string ID, string Prefix)
		{
			string		IDShortcut=ID.Substring(0,Math.Min(ID.Length,5));

			if (Prefix!=null)
				return(string.Format("{0}_{1}",Prefix,IDShortcut));
			else
				return(string.Format("{0}",IDShortcut));
		}
//-------------------------------------------------------------------------------------------------------
		public static string GetTypeNameWOArity(string Name)
		{
			int		Position;

			if ((Position=Name.LastIndexOf('`'))!=-1)
				return(Name.Remove(Position));
			else
				return(Name);
		}
//-------------------------------------------------------------------------------------------------------
		// Vrati meno triedy s generic parametrami, alebo iba do urovne 1.
		public static string GetTypeName(Type Type)
		{
			Type[]				GenericTypes=Type.GetGenericArguments();

			if (GenericTypes.Length==0)
				return(Type.Name);

			StringBuilder		SB=new StringBuilder();

			SB.Append(GetTypeNameWOArity(Type.Name));
			SB.Append("<");

			for (int i=0;i<GenericTypes.Length;i++)
			{
				if (i!=0)
					SB.Append(",");

				SB.Append(GenericTypes[i].Name);
			}

			SB.Append(">");

			return(SB.ToString());
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public static string GetMethodName()
		{
			StackFrame		SF=new StackFrame(1);

			return(string.Format("{0}.{1}()",GetTypeName(SF.GetMethod().DeclaringType),SF.GetMethod().Name));
		}
//-------------------------------------------------------------------------------------------------------
		public static string GetMethodName(int StackDepth)
		{
			StackFrame		SF=new StackFrame(StackDepth);

			return(string.Format("{0}.{1}()",GetTypeName(SF.GetMethod().DeclaringType),SF.GetMethod().Name));
		}
//-------------------------------------------------------------------------------------------------------
		public static string GetExceptionString(Exception E)
		{
			StackFrame		SF=new StackFrame(1);

			return(string.Format("EXCEPTION ({0}): {1}.{2}() - {3} !",E.GetType().Name,GetTypeName(SF.GetMethod().DeclaringType),SF.GetMethod().Name,E.Message));
		}
//-------------------------------------------------------------------------------------------------------
		public static string GetExceptionString(Exception E, string Prefix)
		{
			StackFrame		SF=new StackFrame(1);

			return(string.Format("{0} ({1}): {2}.{3}() - {4} !",Prefix,E.GetType().Name,GetTypeName(SF.GetMethod().DeclaringType),SF.GetMethod().Name,E.Message));
		}
//-------------------------------------------------------------------------------------------------------
		public static string GetMethodCallString()
		{
			StackFrame		SF=new StackFrame(1);

			return(string.Format("{0}.{1}() called !",GetTypeName(SF.GetMethod().DeclaringType),SF.GetMethod().Name));
		}
//-------------------------------------------------------------------------------------------------------
		public static string GetConstructorCallString()
		{
			StackFrame		SF=new StackFrame(1);

			return(string.Format("{0}.CONSTRUCTOR() called !",GetTypeName(SF.GetMethod().DeclaringType)));
		}
//-------------------------------------------------------------------------------------------------------
		public static string GetDestructorCallString()
		{
			StackFrame		SF=new StackFrame(1);

			return(string.Format("{0}.DESTRUCTOR() called !",GetTypeName(SF.GetMethod().DeclaringType)));
		}
//-------------------------------------------------------------------------------------------------------
		public static string GetMethodCallString(int Position)
		{
			StackFrame		SF=new StackFrame(1);

			return(string.Format("{0}.{1}() called {2} !",GetTypeName(SF.GetMethod().DeclaringType),SF.GetMethod().Name,Position));
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------