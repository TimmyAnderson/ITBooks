using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Reflection;
using System.Runtime.Remoting;
//-------------------------------------------------------------------------------------------------------
namespace AssemblyLoading
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//------------------------------------------------------------------------------------------------------
		private static void HasPrintTextAssembly()
		{
			Assembly											HasPrintTextAssembly=AppDomain.CurrentDomain.GetAssemblies().Where(P => P.FullName.Contains("PrintTextAssembly")==true).FirstOrDefault();

			if (HasPrintTextAssembly!=null)
			{
				Console.WriteLine("!!! APP DOMAIN [{0} - {1}] HAS ASSEBLY PrintTextAssembly !",AppDomain.CurrentDomain.Id,AppDomain.CurrentDomain.FriendlyName);
			}
			else
			{
				Console.WriteLine("APP DOMAIN [{0} - {1}] HAS NOT ASSEBLY PrintTextAssembly !",AppDomain.CurrentDomain.Id,AppDomain.CurrentDomain.FriendlyName);
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void CurrentDomainAssemblyLoad(object Sender, AssemblyLoadEventArgs Argument)
		{
			Console.WriteLine(string.Format("ASSEMBLY [{0}] was LOADED to APP DOMAIN [{1}] !",Argument.LoadedAssembly.FullName,AppDomain.CurrentDomain.FriendlyName));
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		private static void LateBindingLoading()
		{
			string												AssemblyPath=string.Format("{0}\\{1}",Environment.CurrentDirectory,"PrintTextAssembly.dll");

			// Nacitam ASSEMBLY cez LATE BINDING.
			Assembly											LateBoundAssembly=Assembly.LoadFile(AssemblyPath);
			
			Console.WriteLine(string.Format("LateBoundAssembly.Location: [{0}] !",LateBoundAssembly.Location));
			Console.WriteLine(string.Format("LateBoundAssembly.CodeBase: [{0}] !",LateBoundAssembly.CodeBase));
			Console.WriteLine(string.Format("LateBoundAssembly.GlobalAssemblyCache: [{0}] !",LateBoundAssembly.GlobalAssemblyCache));

			// Ziska CLASS definovany v LATE BOUND ASSEMBLY.
			Type												LateBoundAssemblyType=LateBoundAssembly.GetType("PrintTextAssembly.CPrintText");

			// Vytvori OBJECT z CLASS definovanej v LATE BOUND ASSEMBLY.
			object												ObjectFromLateBoundAssembly=LateBoundAssembly.CreateInstance("PrintTextAssembly.CPrintText");

			// Ziska METHOD z CLASS definovanej v LATE BOUND ASSEMBLY.
			MethodInfo											MI=LateBoundAssemblyType.GetMethod("PrintText");

			// !!! Vyvola METHOD z CLASS definovanej v LATE BOUND ASSEMBLY.
			MI.Invoke(ObjectFromLateBoundAssembly,new object[]{"Timmy Anderson"});
		}
//------------------------------------------------------------------------------------------------------
		private static void MarshalByValueMethodCallToRemoteAssembly()
		{
			Console.WriteLine("MarshalByValueMethodCallToRemoteAssembly() - APP DOMAIN [{0} - {1}] !",AppDomain.CurrentDomain.Id,AppDomain.CurrentDomain.FriendlyName);

			AppDomainSetup										Setup=new AppDomainSetup();
			AppDomain											Domain=AppDomain.CreateDomain("MyCustomDomain",null,Setup);
			
			// !!! Vytvorim OBJECT v REMOTE DOMAIN.
			ObjectHandle										RemoteObject=Domain.CreateInstance("AssemblyLoading",typeof(CMarshalByValue).FullName);
			
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
			ObjectHandle										RemoteObject=Domain.CreateInstance("AssemblyLoading",typeof(CMarshalByReference).FullName);
			
			// !!!!! Kedze CMarshalByValue DEDI z MarshalByRefObject, tak volanie Unwrap() vytvori PROXY na OBJECT v REMOTE APP DOMAIN.
			// !!!!! Vysledom je, ze v DEFAULT APP DOMAIN aj REMOTE APP DOMAIN maju iba JEDINU INSTANCIU CMarshalByReference ku ktorej sa z DEFAULT APP DOMAIN pristupuje cez PROXY OBJECT 'RemoteTypedObject'.
			// !!! OBJECT 'RemoteTypedObject' je teda PROXY OBJECT odkazujuci na REMOTE OBJECT v REMOTE APP DOMAIN.
			CMarshalByReference									RemoteTypedObject=(CMarshalByReference) RemoteObject.Unwrap();

			// !!!!! Kedze CMarshalByValue DEDI z MarshalByRefObject, tak volanie Unwrap() vytvori PROXY na OBJECT v REMOTE APP DOMAIN a METHOD PrintAppDomain() je volana v REMOTE APP DOMAIN.
			RemoteTypedObject.PrintAppDomain();

			Console.WriteLine("MarshalByReferenceMethodCallToRemoteAssembly() - APP DOMAIN [{0} - {1}] !",AppDomain.CurrentDomain.Id,AppDomain.CurrentDomain.FriendlyName);
		}
//-------------------------------------------------------------------------------------------------------
		private static void WrongAssemblyLoad()
		{
			HasPrintTextAssembly();

			AppDomainSetup										Setup=new AppDomainSetup();
			AppDomain											Domain=AppDomain.CreateDomain("MyCustomDomain",null,Setup);

			ObjectHandle										RemoteObject=Domain.CreateInstance("AssemblyLoading",typeof(CMarshalByReference).FullName);
			CMarshalByReference									RemoteTypedObject=(CMarshalByReference) RemoteObject.Unwrap();

			RemoteTypedObject.HasPrintTextAssembly();
			HasPrintTextAssembly();

			// !!!!! METHOD AppDomain.Load() nacita ASSEMBLY do REMOTE APP DOMAIN, no kedze RETURN VALUE (Assembly OBJECT) sa prenasa do LOCAL DOMAIN a AssemblyClass je MARSHAL-by-VALUE, tak sa spravi KOPIA ASSEMBLY aj v LOCAL APP DOMAIN co NIE JE PRAVE NAJLEPSIE. Preto by sa METHOD AppDomain.Load() mala pouzivat iba na nacitavanie ASSEMBLIES v AppDomain OBJECTS, ktore reprezentuju LOCAL APP DOMAIN a NIE REMOTE APP DOMAIN. Inak bude ASSEMBLY nacitana v OBOCH APP DOMAINS.
			Domain.Load("PrintTextAssembly");

			RemoteTypedObject.HasPrintTextAssembly();
			HasPrintTextAssembly();
		}
//-------------------------------------------------------------------------------------------------------
		private static void AssemblyLoadFailure()
		{
			try
			{
				// !!! Umyselne dam ZLY NAZOV ASSEMBLY.
				string											AssemblyPath=string.Format("{0}\\{1}",Environment.CurrentDirectory,"XXX.DLL");

				// Nacitam ASSEMBLY cez LATE BINDING.
				Assembly										LateBoundAssembly=Assembly.LoadFile(AssemblyPath);

				Console.WriteLine(string.Format("LateBoundAssembly.Location: [{0}] !",LateBoundAssembly.Location));
				Console.WriteLine(string.Format("LateBoundAssembly.CodeBase: [{0}] !",LateBoundAssembly.CodeBase));
				Console.WriteLine(string.Format("LateBoundAssembly.GlobalAssemblyCache: [{0}] !",LateBoundAssembly.GlobalAssemblyCache));

				// Ziska CLASS definovany v LATE BOUND ASSEMBLY.
				Type											LateBoundAssemblyType=LateBoundAssembly.GetType("PrintTextAssembly.CPrintText");

				// Vytvori OBJECT z CLASS definovanej v LATE BOUND ASSEMBLY.
				object											ObjectFromLateBoundAssembly=LateBoundAssembly.CreateInstance("PrintTextAssembly.CPrintText");

				// Ziska METHOD z CLASS definovanej v LATE BOUND ASSEMBLY.
				MethodInfo										MI=LateBoundAssemblyType.GetMethod("PrintText");

				// !!! Vyvola METHOD z CLASS definovanej v LATE BOUND ASSEMBLY.
				MI.Invoke(ObjectFromLateBoundAssembly,new object[]{"Timmy Anderson"});
			}
			catch(FileNotFoundException E)
			{
				// !!!!! Zobrazi sa obsah PROPERTY FusionLog.
				Console.WriteLine(string.Format("EXCEPTION [{0}], FusionLog: [{1}] !",E.Message,E.FusionLog));
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void AssemblyLoadEvent()
		{
			// !!! EVENT je volany pri nacitany ASSEMBLY do APP DOMAIN.
			AppDomain.CurrentDomain.AssemblyLoad+=new AssemblyLoadEventHandler(CurrentDomainAssemblyLoad);

			string												AssemblyPath=string.Format("{0}\\{1}",Environment.CurrentDirectory,"PrintTextAssembly.dll");

			// Nacitam ASSEMBLY cez LATE BINDING.
			Assembly											LateBoundAssembly=Assembly.LoadFile(AssemblyPath);
			
			Console.WriteLine(string.Format("LateBoundAssembly.Location: [{0}] !",LateBoundAssembly.Location));
			Console.WriteLine(string.Format("LateBoundAssembly.CodeBase: [{0}] !",LateBoundAssembly.CodeBase));
			Console.WriteLine(string.Format("LateBoundAssembly.GlobalAssemblyCache: [{0}] !",LateBoundAssembly.GlobalAssemblyCache));
			Console.WriteLine(string.Format("LateBoundAssembly.ImageRuntimeVersion: [{0}] !",LateBoundAssembly.ImageRuntimeVersion));

			// Ziska CLASS definovany v LATE BOUND ASSEMBLY.
			Type												LateBoundAssemblyType=LateBoundAssembly.GetType("PrintTextAssembly.CPrintText");

			// Vytvori OBJECT z CLASS definovanej v LATE BOUND ASSEMBLY.
			object												ObjectFromLateBoundAssembly=LateBoundAssembly.CreateInstance("PrintTextAssembly.CPrintText");

			// Ziska METHOD z CLASS definovanej v LATE BOUND ASSEMBLY.
			MethodInfo											MI=LateBoundAssemblyType.GetMethod("PrintText");

			// !!! Vyvola METHOD z CLASS definovanej v LATE BOUND ASSEMBLY.
			MI.Invoke(ObjectFromLateBoundAssembly,new object[]{"Timmy Anderson"});
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			try
			{
				//LateBindingLoading();
				//MarshalByValueMethodCallToRemoteAssembly();
				//MarshalByReferenceMethodCallToRemoteAssembly();
				//WrongAssemblyLoad();
				//AssemblyLoadFailure();
				AssemblyLoadEvent();
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION [{0}] !",E.Message));
			}

			Console.WriteLine("Press any KEY to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------