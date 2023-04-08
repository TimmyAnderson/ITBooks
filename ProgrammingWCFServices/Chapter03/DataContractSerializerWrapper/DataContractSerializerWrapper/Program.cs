using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
//-------------------------------------------------------------------------------------------------------
namespace DataContractSerializerWrapper
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		private static void TestReadAndWrite()
		{
			CFullName1							ObjIN=new CFullName1("Timmy","Anderson",12);
			DataContractSerializer<CFullName1>	Formatter=new DataContractSerializer<CFullName1>();

			using(Stream Stream=new MemoryStream())
			{
				Formatter.WriteObject(Stream,ObjIN);
				Stream.Seek(0,SeekOrigin.Begin);

				CFullName1						ObjOUT=Formatter.ReadObject(Stream);

				Console.WriteLine(string.Format("NAME: [{0}] !",ObjOUT));

				string							Dump=Formatter.Dump(ObjOUT,true);

				Console.WriteLine("");
				Console.WriteLine(Dump);
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void Print()
		{
			// !!! CFullName1 je [DataContract].
			// !!! CFullName2 je [Serializable].

			CFullName1							Obj1=new CFullName1("Timmy","Anderson",12);
			CFullName2							Obj2=new CFullName2("Timmy","Anderson",12);

			DataContractSerializer<CFullName1>	Formatter1=new DataContractSerializer<CFullName1>();
			DataContractSerializer<CFullName2>	Formatter2=new DataContractSerializer<CFullName2>();

			string								Text1=Formatter1.Dump(Obj1,true);
			string								Text2=Formatter2.Dump(Obj2,true);

			Console.WriteLine("[DataContract]");
			Console.WriteLine(Text1);
			Console.WriteLine("");
			Console.WriteLine("\n[Serializable]");
			Console.WriteLine(Text2);
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			//TestReadAndWrite();
			Print();

			Console.WriteLine("\nPress any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------