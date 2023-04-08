using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Reflection;
using System.Runtime.Serialization;
using CreateBagNet;
//------------------------------------------------------------------------------------------------------
namespace BagAssemblyLoadingManager
{
//------------------------------------------------------------------------------------------------------
	class Program
	{
//------------------------------------------------------------------------------------------------------
		private static CBagNetRecords							MBagNetRecords;
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
		// !!! Vykonava RESOLVING ASSEMBLIES, ktore CLR pomocou standardneho ASSEMBLY PROBING nedokazal najst.
		private static Assembly CurrentDomainAssemblyResolve(object Sender, ResolveEventArgs Args)
		{
			Console.WriteLine(string.Format("Trying to RESOLVE ASSEMBLY [{0}] !",Args.Name));
			
			foreach (CBagNetRecord BagNetRecord in MBagNetRecords.BagNetRecords)
			{
				int												Position1=Args.Name.IndexOf(',');
				int												Position2=BagNetRecord.AssemblyIdentity.IndexOf(',');

				if (Position1==-1 || Position2==-1)
				{
					continue;
				}

				string											AssemblyToFindFriendlyName=Args.Name.Substring(0,Position1);
				string											AssemblyInStoreFriendlyName=BagNetRecord.AssemblyIdentity.Substring(0,Position2);

				if (AssemblyToFindFriendlyName==AssemblyInStoreFriendlyName)
				{
					try
					{
						// !!! ASSEMBLY vytvorim z BYTE ARRAY.
						Assembly								ResolvedAssembly=Assembly.Load(BagNetRecord.FileData);

						Console.WriteLine(string.Format("ASSEMBLY [{0}] was RESOLVED !",Args.Name));

						return(ResolvedAssembly);
					}
					catch(Exception E)
					{
						Console.WriteLine(string.Format("EXCEPTION [{0}] ! ASSEMBLY [{1}] was NOT RESOLVED !",E.Message,Args.Name));
						return(null);
					}
				}
			}

			Console.WriteLine(string.Format("ASSEMBLY [{0}] was NOT RESOLVED !",Args.Name));
			return(null);
		}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
		private static CBagNetRecords GetBag()
		{
			string												BagNetDirectory="..\\..\\..\\..\\!BagNet";
			string												BagNetFilePath=string.Format("{0}\\MyBagNet.bag",BagNetDirectory);
			CBagNetRecords										BagNetRecordsObject;

			using (FileStream FS=new FileStream(BagNetFilePath,FileMode.Open,FileAccess.Read))
			{
				DataContractSerializer							DCS=new DataContractSerializer(typeof(CBagNetRecords));

				BagNetRecordsObject=(CBagNetRecords) DCS.ReadObject(FS);
			}

			foreach (CBagNetRecord BagNetRecord in BagNetRecordsObject.BagNetRecords)
			{
				Console.WriteLine(string.Format("FILE [{0}] was READ from BAG NET with IDENTITY [{1}] !",BagNetRecord.FileName,BagNetRecord.AssemblyIdentity));
			}

			return(BagNetRecordsObject);
		}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
		private static void ReadAssembliesFromBagNetFile()
		{
			MBagNetRecords=GetBag();

			string												AssemblyIdentity="BagExecutable, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null";

			// !!! Zaregistruje ASSEMBLY RESOLVER.
			AppDomain.CurrentDomain.AssemblyResolve+=new ResolveEventHandler(CurrentDomainAssemblyResolve);

			Assembly											BagNetAssembly=Assembly.Load(AssemblyIdentity);

			// !!! Nacitam TYPE z ASSEMBLY nacitanej z CUSTOM STORE.
			Type												TypeToExecute=BagNetAssembly.GetType(MBagNetRecords.RunnableType,true,true);
			MethodInfo											MI=TypeToExecute.GetMethod("Main",BindingFlags.NonPublic | BindingFlags.Static);

			MI.Invoke(null,new object[]{null});

			Console.WriteLine(string.Format("MAIN METHOD in TYPE [{0}] was INVOKED in APP DOMAIN [{1}] !",MBagNetRecords.RunnableType,AppDomain.CurrentDomain.FriendlyName));
		}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			try
			{
				ReadAssembliesFromBagNetFile();
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