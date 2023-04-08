using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Runtime.Remoting;
//------------------------------------------------------------------------------------------------------
namespace ConfiguringAppDomains
{
//------------------------------------------------------------------------------------------------------
	class Program
	{
//------------------------------------------------------------------------------------------------------
		// !!! METHOD sa vola pri vytvoreni NOVEJ APP DOMAIN.
		private static void AppDomainInitializer(string[] Parameters)
		{
			Console.WriteLine("AppDomainInitializer() - APP DOMAIN [{0} - {1}], Parameter[0]: [{2}] !",AppDomain.CurrentDomain.Id,AppDomain.CurrentDomain.FriendlyName,Parameters[0]);
		}
//------------------------------------------------------------------------------------------------------
		private static void PrintAppDomainSettings(AppDomain Domain)
		{
			AppDomainSetup										DefaultAppDomainSetup=Domain.SetupInformation;

			Console.WriteLine(string.Format("ActivationArguments: [{0}] !",DefaultAppDomainSetup.ActivationArguments));
			Console.WriteLine(string.Format("AppDomainInitializer: [{0}] !",DefaultAppDomainSetup.AppDomainInitializer));
			//Console.WriteLine(string.Format("AppDomainInitializerArguments: [{0}] !",DefaultAppDomainSetup.AppDomainInitializerArguments));
			Console.WriteLine(string.Format("AppDomainManagerAssembly: [{0}] !",DefaultAppDomainSetup.AppDomainManagerAssembly));
			Console.WriteLine(string.Format("AppDomainManagerType: [{0}] !",DefaultAppDomainSetup.AppDomainManagerType));
			Console.WriteLine(string.Format("ApplicationBase: [{0}] !",DefaultAppDomainSetup.ApplicationBase));
			Console.WriteLine(string.Format("ApplicationName: [{0}] !",DefaultAppDomainSetup.ApplicationName));
			Console.WriteLine(string.Format("ApplicationTrust: [{0}] !",DefaultAppDomainSetup.ApplicationTrust));
			Console.WriteLine(string.Format("CachePath: [{0}] !",DefaultAppDomainSetup.CachePath));
			Console.WriteLine(string.Format("ConfigurationFile: [{0}] !",DefaultAppDomainSetup.ConfigurationFile));
			Console.WriteLine(string.Format("DisallowApplicationBaseProbing: [{0}] !",DefaultAppDomainSetup.DisallowApplicationBaseProbing));
			Console.WriteLine(string.Format("DisallowBindingRedirects: [{0}] !",DefaultAppDomainSetup.DisallowBindingRedirects));
			Console.WriteLine(string.Format("DisallowCodeDownload: [{0}] !",DefaultAppDomainSetup.DisallowCodeDownload));
			Console.WriteLine(string.Format("DisallowPublisherPolicy: [{0}] !",DefaultAppDomainSetup.DisallowPublisherPolicy));
			Console.WriteLine(string.Format("DynamicBase: [{0}] !",DefaultAppDomainSetup.DynamicBase));
			Console.WriteLine(string.Format("LicenseFile: [{0}] !",DefaultAppDomainSetup.LicenseFile));
			Console.WriteLine(string.Format("LoaderOptimization: [{0}] !",DefaultAppDomainSetup.LoaderOptimization));
			//Console.WriteLine(string.Format("PartialTrustVisibleAssemblies: [{0}] !",DefaultAppDomainSetup.PartialTrustVisibleAssemblies));
			Console.WriteLine(string.Format("PrivateBinPath: [{0}] !",DefaultAppDomainSetup.PrivateBinPath));
			Console.WriteLine(string.Format("PrivateBinPathProbe: [{0}] !",DefaultAppDomainSetup.PrivateBinPathProbe));
			Console.WriteLine(string.Format("SandboxInterop: [{0}] !",DefaultAppDomainSetup.SandboxInterop));
			Console.WriteLine(string.Format("ShadowCopyDirectories: [{0}] !",DefaultAppDomainSetup.ShadowCopyDirectories));
			Console.WriteLine(string.Format("ShadowCopyFiles: [{0}] !",DefaultAppDomainSetup.ShadowCopyFiles));
		}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
		private static void PrintAppDomainSettings()
		{
			AppDomainSetup										DefaultAppDomainSetup=AppDomain.CurrentDomain.SetupInformation;

			Console.WriteLine(string.Format("ActivationArguments: [{0}] !",DefaultAppDomainSetup.ActivationArguments));
			Console.WriteLine(string.Format("AppDomainInitializer: [{0}] !",DefaultAppDomainSetup.AppDomainInitializer));
			//Console.WriteLine(string.Format("AppDomainInitializerArguments: [{0}] !",DefaultAppDomainSetup.AppDomainInitializerArguments));
			Console.WriteLine(string.Format("AppDomainManagerAssembly: [{0}] !",DefaultAppDomainSetup.AppDomainManagerAssembly));
			Console.WriteLine(string.Format("AppDomainManagerType: [{0}] !",DefaultAppDomainSetup.AppDomainManagerType));
			Console.WriteLine(string.Format("ApplicationBase: [{0}] !",DefaultAppDomainSetup.ApplicationBase));
			Console.WriteLine(string.Format("ApplicationName: [{0}] !",DefaultAppDomainSetup.ApplicationName));
			Console.WriteLine(string.Format("ApplicationTrust: [{0}] !",DefaultAppDomainSetup.ApplicationTrust));
			Console.WriteLine(string.Format("CachePath: [{0}] !",DefaultAppDomainSetup.CachePath));
			Console.WriteLine(string.Format("ConfigurationFile: [{0}] !",DefaultAppDomainSetup.ConfigurationFile));
			Console.WriteLine(string.Format("DisallowApplicationBaseProbing: [{0}] !",DefaultAppDomainSetup.DisallowApplicationBaseProbing));
			Console.WriteLine(string.Format("DisallowBindingRedirects: [{0}] !",DefaultAppDomainSetup.DisallowBindingRedirects));
			Console.WriteLine(string.Format("DisallowCodeDownload: [{0}] !",DefaultAppDomainSetup.DisallowCodeDownload));
			Console.WriteLine(string.Format("DisallowPublisherPolicy: [{0}] !",DefaultAppDomainSetup.DisallowPublisherPolicy));
			Console.WriteLine(string.Format("DynamicBase: [{0}] !",DefaultAppDomainSetup.DynamicBase));
			Console.WriteLine(string.Format("LicenseFile: [{0}] !",DefaultAppDomainSetup.LicenseFile));
			Console.WriteLine(string.Format("LoaderOptimization: [{0}] !",DefaultAppDomainSetup.LoaderOptimization));
			//Console.WriteLine(string.Format("PartialTrustVisibleAssemblies: [{0}] !",DefaultAppDomainSetup.PartialTrustVisibleAssemblies));
			Console.WriteLine(string.Format("PrivateBinPath: [{0}] !",DefaultAppDomainSetup.PrivateBinPath));
			Console.WriteLine(string.Format("PrivateBinPathProbe: [{0}] !",DefaultAppDomainSetup.PrivateBinPathProbe));
			Console.WriteLine(string.Format("SandboxInterop: [{0}] !",DefaultAppDomainSetup.SandboxInterop));
			Console.WriteLine(string.Format("ShadowCopyDirectories: [{0}] !",DefaultAppDomainSetup.ShadowCopyDirectories));
			Console.WriteLine(string.Format("ShadowCopyFiles: [{0}] !",DefaultAppDomainSetup.ShadowCopyFiles));
		}
//------------------------------------------------------------------------------------------------------
		private static void ChangeApplicationBase()
		{
			AppDomainSetup										Setup=new AppDomainSetup();
			string												ApplicationBasePath=Environment.CurrentDirectory;

			ApplicationBasePath=ApplicationBasePath.Substring(0,ApplicationBasePath.LastIndexOf("\\"));
			ApplicationBasePath=ApplicationBasePath.Substring(0,ApplicationBasePath.LastIndexOf("\\"));
			ApplicationBasePath=ApplicationBasePath.Substring(0,ApplicationBasePath.LastIndexOf("\\"));
			ApplicationBasePath=ApplicationBasePath.Substring(0,ApplicationBasePath.LastIndexOf("\\"));
			ApplicationBasePath=Path.Combine(ApplicationBasePath,"!Assemblies\\");

			// !!! Nastavim DIRECTORY z ktorej sa budu citat ASSEMBLIES v danej APP DOMAIN.
			Setup.ApplicationBase=ApplicationBasePath;

			// !!! Nastavim DIRECTORY 'ReferencedAssemblies', ze sa ma pouzit na vyhladavanie ASSEMBLIES.
			Setup.PrivateBinPath="ReferencedAssemblies";

			AppDomain											Domain=AppDomain.CreateDomain("MyCustomDomain",null,Setup);

			Console.WriteLine(string.Format("BaseDirectory: [{0}] !",Domain.BaseDirectory));

			// !!! Zmena Setup.ApplicationBase NEMA VPLYV na miesto odkial sa natiahne ASSEMBLY v ExecuteAssembly.
			Domain.ExecuteAssembly("..\\..\\..\\..\\!Assemblies\\PrintTextAssembly.exe",new string[]{"Timmy Anderson"});

			Console.WriteLine(string.Format("BaseDirectory: [{0}] !",Domain.BaseDirectory));
		}
//------------------------------------------------------------------------------------------------------
		private static void ReadConfigurationFileFromFile()
		{
			AppDomainSetup										Setup=new AppDomainSetup();

			// !!! Nastavim nazov .CONFIG FILE pre danu APP DOMAIN.
			Setup.ConfigurationFile="MyApp.config";

			AppDomain											Domain=AppDomain.CreateDomain("MyCustomDomain",null,Setup);

			Domain.ExecuteAssembly("ReadConfigFile.exe");
		}
//------------------------------------------------------------------------------------------------------
		private static void ReadConfigurationFileForBinary()
		{
			AppDomainSetup										Setup=new AppDomainSetup();
			byte[]												ConfigFile;

			// !!! Nacitam .CONFIG FILE z disku.
			using(FileStream FS=new FileStream("MyApp.config",FileMode.Open))
			{
				ConfigFile=new byte[FS.Length];

				FS.Read(ConfigFile,0,(int) FS.Length);
			}

			// !!! Nastavim nacitany .CONFIG FILE v BINARNY formate pre danu APP DOMAIN.
			// ????? Bohuzial CLR sa zda, ze IGNORUJE toto nastavenie.
			Setup.SetConfigurationBytes(ConfigFile);

			AppDomain											Domain=AppDomain.CreateDomain("MyCustomDomain",null,Setup);

			Domain.ExecuteAssembly("ReadConfigFile.exe");
		}
//------------------------------------------------------------------------------------------------------
		private static void ShadowCopy()
		{
			AppDomainSetup										Setup=new AppDomainSetup();

			Setup.ConfigurationFile="MyApp.config";
			
			// !!! Zapnem SHADOW COPY tym, ze do PROPERTY zapisem STRING 'true'.
			Setup.ShadowCopyFiles="true";
			Setup.CachePath=string.Format("{0}\\{1}",Environment.CurrentDirectory,"MyAssemblyCache");
			Setup.ApplicationName="MyApplication";

			AppDomain											Domain=AppDomain.CreateDomain("MyCustomDomain",null,Setup);

			Domain.ExecuteAssembly("ReadConfigFile.exe");

			string												AssemblyPath=string.Format("{0}\\{1}",Environment.CurrentDirectory,"ReadConfigFile.exe");

			try
			{
				// !!!!! Pokusim sa zmazat UZ NACITANU ASSEMBLY. Kedze som pouzil SHADOW COPY, tak sa zmazanie PODARI, lebo na ASSEMBLY FILE [ReadConfigFile.exe] NEAPLIKOVAL LOCK.
				File.Delete(AssemblyPath);

				Console.WriteLine(string.Format("ASSEMBLY FILE [{0}] was SUCCESSFULLY DELETED !",AssemblyPath));
			}
			catch
			{
				Console.WriteLine(string.Format("!!! ASSEMBLY FILE [{0}] FAILED to DELETE !",AssemblyPath));
			}
		}
//------------------------------------------------------------------------------------------------------
		private static void MarshalByValueMethodCallToRemoteAssembly()
		{
			Console.WriteLine("MarshalByValueMethodCallToRemoteAssembly() - APP DOMAIN [{0} - {1}] !",AppDomain.CurrentDomain.Id,AppDomain.CurrentDomain.FriendlyName);

			AppDomainSetup										Setup=new AppDomainSetup();
			AppDomain											Domain=AppDomain.CreateDomain("MyCustomDomain",null,Setup);
			
			// !!! Vytvorim OBJECT v REMOTE DOMAIN.
			ObjectHandle										RemoteObject=Domain.CreateInstance("ConfiguringAppDomains",typeof(CMarshalByValue).FullName);
			
			// !!!!! Kedze CMarshalByValue NEDEDI z MarshalByRefObject, ale je SERIALIZABLE, tak volanie Unwrap() vytvori KOPIU OBJECT v DEFAULT APP DOMAIN.
			// !!!!! Vysledom je, ze v DEFAULT APP DOMAIN je JEDNA instancia CMarshalByValue a v REMOTE APP DOMAIN je DRUHA INSTANCIA CLASS CMarshalByValue.
			CMarshalByValue										RemoteTypedObject=(CMarshalByValue) RemoteObject.Unwrap();

			// !!!!! Kedze CMarshalByValue NEDEDI z MarshalByRefObject, ale je SERIALIZABLE, tak METHOD PrintAppDomain() je volana v DEFAULT APP DOMAIN.
			RemoteTypedObject.PrintAppDomain();

			Console.WriteLine("MarshalByValueMethodCallToRemoteAssembly() - APP DOMAIN [{0} - {1}] !",AppDomain.CurrentDomain.Id,AppDomain.CurrentDomain.FriendlyName);
		}
//------------------------------------------------------------------------------------------------------
		private static void MarshalByReferenceMethodCallToRemoteAssembly()
		{
			Console.WriteLine("MarshalByReferenceMethodCallToRemoteAssembly() - APP DOMAIN [{0} - {1}] !",AppDomain.CurrentDomain.Id,AppDomain.CurrentDomain.FriendlyName);

			AppDomainSetup										Setup=new AppDomainSetup();
			AppDomain											Domain=AppDomain.CreateDomain("MyCustomDomain",null,Setup);

			// !!! Vytvorim OBJECT v REMOTE DOMAIN.
			ObjectHandle										RemoteObject=Domain.CreateInstance("ConfiguringAppDomains",typeof(CMarshalByReference).FullName);
			
			// !!!!! Kedze CMarshalByValue DEDI z MarshalByRefObject, tak volanie Unwrap() vytvori PROXY na OBJECT v REMOTE APP DOMAIN.
			// !!!!! Vysledom je, ze v DEFAULT APP DOMAIN aj REMOTE APP DOMAIN maju iba JEDINU INSTANCIU CMarshalByReference ku ktorej sa z DEFAULT APP DOMAIN pristupuje cez PROXY OBJECT 'RemoteTypedObject'.
			// !!! OBJECT 'RemoteTypedObject' je teda PROXY OBJECT odkazujuci na REMOTE OBJECT v REMOTE APP DOMAIN.
			CMarshalByReference									RemoteTypedObject=(CMarshalByReference) RemoteObject.Unwrap();

			// !!!!! Kedze CMarshalByValue DEDI z MarshalByRefObject, tak volanie Unwrap() vytvori PROXY na OBJECT v REMOTE APP DOMAIN a METHOD PrintAppDomain() je volana v REMOTE APP DOMAIN.
			RemoteTypedObject.PrintAppDomain();

			Console.WriteLine("MarshalByReferenceMethodCallToRemoteAssembly() - APP DOMAIN [{0} - {1}] !",AppDomain.CurrentDomain.Id,AppDomain.CurrentDomain.FriendlyName);
		}
//------------------------------------------------------------------------------------------------------
		private static void CallMethodOnRemoteAppDomain()
		{
			Console.WriteLine("CallMethodOnRemoteAppDomain() - APP DOMAIN [{0} - {1}] !",AppDomain.CurrentDomain.Id,AppDomain.CurrentDomain.FriendlyName);

			AppDomainSetup										Setup=new AppDomainSetup();

			Setup.AppDomainInitializer=AppDomainInitializer;
			Setup.AppDomainInitializerArguments=new string[]{"Timmy Anderson"};

			// !!! Pri vytvarani APP DOMAIN sa v tejto v vytvorenej APP DOMAIN vola METHOD urcena v PROPERTY AppDomainSetup.AppDomainInitializer.
			AppDomain											Domain=AppDomain.CreateDomain("MyCustomDomain",null,Setup);

			Console.WriteLine("CallMethodOnRemoteAppDomain() - APP DOMAIN [{0} - {1}] !",AppDomain.CurrentDomain.Id,AppDomain.CurrentDomain.FriendlyName);
		}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			try
			{
				//PrintAppDomainSettings();
				//ChangeApplicationBase();
				//ReadConfigurationFileFromFile();
				//ReadConfigurationFileForBinary();
				//ShadowCopy();
				//MarshalByValueMethodCallToRemoteAssembly();
				//MarshalByReferenceMethodCallToRemoteAssembly();
				CallMethodOnRemoteAppDomain();
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION [{0}] !",E.Message));
			}

			Console.WriteLine("Press any KEY to EXIT !");
			Console.ReadLine();
		}
//------------------------------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------------------------------