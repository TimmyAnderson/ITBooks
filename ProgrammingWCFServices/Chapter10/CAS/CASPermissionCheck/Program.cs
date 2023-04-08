using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Security;
using System.Security.Permissions;
using System.Security.Policy;
using System.Reflection;
//-------------------------------------------------------------------------------------------------------
namespace CASPermissionCheck
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		private static void PermittedToWriteToFile()
		{
			try
			{
				WriteToFile("PermittedToWriteToFile()");
				Console.WriteLine("PermittedToWriteToFile() - SUCESSFULLY CALLED !");
			}
			catch(SecurityException E)
			{
				Console.WriteLine(string.Format("PermittedToWriteToFile() - SECURITY EXCEPTION: {0} !",E.Message));
			}
		}
//-------------------------------------------------------------------------------------------------------
		/*
		// !!!!! SecurityAction.Deny uz NIE JE SUPPORTED v .NET 4.0..
		// ZAKAZEM pristup k FILE SYSTEM.
		[FileIOPermission(SecurityAction.Deny,AllLocalFiles=FileIOPermissionAccess.AllAccess)]
		private static void DENIEDToWriteToFile()
		{
			try
			{
				WriteToFile("DENIEDToWriteToFile()");
				Console.WriteLine("DENIEDToWriteToFile() - SUCESSFULLY CALLED !");
			}
			catch(SecurityException E)
			{
				Console.WriteLine(string.Format("DENIEDToWriteToFile() - SECURITY EXCEPTION: {0} !",E.Message));
			}
		}
		*/
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		private static void WriteToFile(string Message)
		{
			try
			{
				using (StreamWriter SW=new StreamWriter("..\\..\\TEST.txt",true))
				{
					SW.WriteLine(string.Format("Time: [{0}], Message: [{1}] !",DateTime.Now.ToString(),Message));
				}
			}
			catch(IOException E)
			{
				Console.WriteLine(string.Format("EXCEPTION: {0} !",E.Message));
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void SimpleTest()
		{
			PermittedToWriteToFile();
			//DENIEDToWriteToFile();

			try
			{
				// Vyskusam zapisat do suboru po volani DENIEDToWriteToFile().
				WriteToFile("Test()");
				Console.WriteLine("Test() - SUCESSFULLY CALLED !");
			}
			catch(SecurityException E)
			{
				Console.WriteLine(string.Format("Test() - SECURITY EXCEPTION: {0} !",E.Message));
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void TestNewAppDomain()
		{
			// NASTAVIM PERMISSIONS pre AppDomain.
			PermissionSet				PS=new PermissionSet(PermissionState.Unrestricted);

			// !!! ASSEMBLY MUSI BYT STRONG ASSEMBLY.
			StrongName					SN=typeof(CClassInSeparateAppDomain).Assembly.Evidence.GetHostEvidence<StrongName>();
			
			AppDomainSetup				AS=new AppDomainSetup();

			AS.ApplicationBase=Path.GetFullPath(".");

			AppDomain					AD=AppDomain.CreateDomain("SecondAppDomain",null,AS,PS,SN);
			string						AssemblyName=Assembly.GetAssembly(typeof(CClassInSeparateAppDomain)).FullName;

			// Vytvorim instanciu objektu v NOVEJ APP DOMAIN.
			// !!! Je to vlastne REMOTING PROXY.
			CClassInSeparateAppDomain	ObjectInNewAppDomain=AD.CreateInstanceAndUnwrap(AssemblyName,typeof(CClassInSeparateAppDomain).ToString()) as CClassInSeparateAppDomain;

			// !!! Volam metodu CEZ PROXY na 2. APP DOMAIN.
			ObjectInNewAppDomain.Test();
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			SimpleTest();
			//TestNewAppDomain();

			Console.WriteLine(string.Format("Press any key to EXIT !"));
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------