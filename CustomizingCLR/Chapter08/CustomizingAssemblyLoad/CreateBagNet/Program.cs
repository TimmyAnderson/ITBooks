using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Reflection;
using System.Runtime.Serialization;
//------------------------------------------------------------------------------------------------------
namespace CreateBagNet
{
//------------------------------------------------------------------------------------------------------
	class Program
	{
//------------------------------------------------------------------------------------------------------
		private static void CreateBag()
		{
			DirectoryInfo										BagDirectory=new DirectoryInfo("..\\..\\..\\..\\!BagNet");
			FileInfo[]											Files=BagDirectory.GetFiles();
			List<CBagNetRecord>									BagNetRecords=new List<CBagNetRecord>();

			foreach(FileInfo File in Files)
			{
				if (File.Extension.ToUpper()==".EXE" || File.Extension.ToUpper()==".DLL")
				{
					string										FileName=File.Name;
					bool										IsEXE=(File.Extension.ToUpper()==".EXE");
					string										AssemblyIdentity;
					byte[]										FileData;

					try
					{
						Assembly								FileAssembly=Assembly.LoadFile(File.FullName);

						AssemblyIdentity=FileAssembly.FullName;

						FileData=new byte[File.Length];

						using (FileStream FS=File.OpenRead())
						{
							FS.Read(FileData,0,(int) File.Length);
						}

						CBagNetRecord							BagNetRecord=new CBagNetRecord(FileName,IsEXE,AssemblyIdentity,FileData);

						BagNetRecords.Add(BagNetRecord);

						Console.WriteLine(string.Format("FILE [{0}] was ADDED to BAG NET !",File.Name));
					}
					catch(Exception E)
					{
						Console.WriteLine(string.Format("EXCEPTION [{0}] ! FILE will NOT be ADDED to BAG NET !",E.Message));
					}
				}
			}

			CBagNetRecords										BagNetRecordsObject=new CBagNetRecords("BagExecutable.exe","BagExecutable.Program",BagNetRecords.ToArray());

			using (FileStream FS=new FileStream(string.Format("{0}\\MyBagNet.bag",BagDirectory.FullName),FileMode.Create,FileAccess.Write))
			{
				DataContractSerializer							DCS=new DataContractSerializer(typeof(CBagNetRecords));

				DCS.WriteObject(FS,BagNetRecordsObject);
			}
		}
//------------------------------------------------------------------------------------------------------
		private static void ExtractBag()
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
				string											FilePath=string.Format("{0}\\{1}",BagNetDirectory,BagNetRecord.FileName);

				using (FileStream FS=new FileStream(FilePath,FileMode.Create,FileAccess.Write))
				{
					FS.Write(BagNetRecord.FileData,0,BagNetRecord.FileData.Length);

					Console.WriteLine(string.Format("FILE [{0}] was EXTRACTED from BAG NET !",BagNetRecord.FileName));
				}
			}
		}
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
				Console.WriteLine(string.Format("FILE [{0}] was READ from BAG NET !",BagNetRecord.FileName));
			}

			return(BagNetRecordsObject);
		}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			try
			{
				//CreateBag();
				//ExtractBag();
				GetBag();
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