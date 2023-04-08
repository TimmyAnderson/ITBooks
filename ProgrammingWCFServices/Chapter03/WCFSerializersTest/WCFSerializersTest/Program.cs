using System;
using System.Collections.Generic;
using System.Text;
using System.Runtime.Serialization;
using System.IO;
//-------------------------------------------------------------------------------------------------------
namespace WCFSerializersTest
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		static void Test1()
		{
			CTestClass					TestClassIn=new CTestClass("Timmy","Anderson",12,"Minneapolis");
			CTestClass					TestClassOut;
			DataContractSerializer		DCS=new DataContractSerializer(typeof(CTestClass));

			Console.WriteLine("Object before serialization: [{0}] !",TestClassIn.ToString());

			using(Stream S=new MemoryStream())
			{
				DCS.WriteObject(S,TestClassIn);
				S.Seek(0,SeekOrigin.Begin);

				TestClassOut=(CTestClass) DCS.ReadObject(S);
			}

			Console.WriteLine("Object after serialization: [{0}] !",TestClassOut.ToString());
			Console.WriteLine();
		}
//-------------------------------------------------------------------------------------------------------
		static void Test2()
		{
			CTestClass								TestClassIn=new CTestClass("Timmy","Anderson",12,"Minneapolis");
			CTestClass								TestClassOut;
			CXmlObjectSerializerHelper<CTestClass>	DCS=new CXmlObjectSerializerHelper<CTestClass>();

			Console.WriteLine("Object before serialization: [{0}] !",TestClassIn.ToString());

			using(Stream S=new MemoryStream())
			{
				DCS.WriteObject(S,TestClassIn);
				S.Seek(0,SeekOrigin.Begin);

				TestClassOut=(CTestClass) DCS.ReadObject(S);
			}

			Console.WriteLine("Object after serialization: [{0}] !",TestClassOut.ToString());
			Console.WriteLine();
		}
//-------------------------------------------------------------------------------------------------------
		static void Test3()
		{
			CTestClass					TestClassIn1=new CTestClass("Timmy","Anderson",12,"Minneapolis");
			CTestClass					TestClassIn2=new CTestClass("Timmy","Anderson",12,"Minneapolis");
			CTestClass					TestClassOut1;
			CTestClass					TestClassOut2;
			DataContractSerializer		DCS=new DataContractSerializer(typeof(CTestClass));
			NetDataContractSerializer	NDCS=new NetDataContractSerializer();

			Console.WriteLine("Object before serialization: [{0}] !",TestClassIn1.ToString());

			try
			{
				using(Stream S=new MemoryStream())
				{
					// Objekt serializujem pomocou NetDataContractSerializer.
					NDCS.WriteObject(S,TestClassIn1);
					S.Seek(0,SeekOrigin.Begin);

					// Objekt deserializujem pomocou DataContractSerializer.
					TestClassOut1=(CTestClass) DCS.ReadObject(S);

					Console.WriteLine("Object after serialization: [{0}] !",TestClassOut1.ToString());
					Console.WriteLine();
					Console.WriteLine("NetDataContractSerializer -> DataContractSerializer SUCCEEDED !");
					Console.WriteLine();
				}
			}
			catch(Exception E)
			{
				Console.WriteLine("EXCEPTION: [{0}] !",E.Message);
				Console.WriteLine();
				Console.WriteLine("NetDataContractSerializer -> DataContractSerializer FAILED !");
				Console.WriteLine();
			}

			try
			{
				Console.WriteLine("Object before serialization: [{0}] !",TestClassIn1.ToString());

				using(Stream S=new MemoryStream())
				{
					// Objekt serializujem pomocou DataContractSerializer.
					DCS.WriteObject(S,TestClassIn2);
					S.Seek(0,SeekOrigin.Begin);

					// Objekt deserializujem pomocou NetDataContractSerializer.
					// !!! Hodi EXCEPTION, kedze NetDataContractSerializer nema v streame serailizovnom DataContractSerializer info o type.
					TestClassOut2=(CTestClass) NDCS.ReadObject(S);
					Console.WriteLine("Object after serialization: [{0}] !",TestClassOut2.ToString());
					Console.WriteLine();
					Console.WriteLine("DataContractSerializer -> NetDataContractSerializer SUCCEEDED !");
					Console.WriteLine();
				}
			}
			catch(Exception E)
			{
				Console.WriteLine("EXCEPTION: [{0}] !",E.Message);
				Console.WriteLine();
				Console.WriteLine("DataContractSerializer -> NetDataContractSerializer FAILED !");
				Console.WriteLine();
			}

			Console.WriteLine();
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			//Test1();
			//Test2();
			Test3();

			Console.WriteLine("Press any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------