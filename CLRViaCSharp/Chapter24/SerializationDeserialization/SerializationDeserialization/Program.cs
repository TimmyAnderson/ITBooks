using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Runtime.Serialization;
using System.Runtime.Serialization.Formatters.Binary;
using System.Runtime.Serialization.Formatters.Soap;
using System.IO;
using System.Xml;
//-------------------------------------------------------------------------------------------------------
namespace SerializationDeserialization
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		private static void DumpStream(Stream StreamData)
		{
			StreamReader										SR=new StreamReader(StreamData);
			string												Content=SR.ReadToEnd();

			Console.WriteLine(Content);
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		private static void Test1()
		{
			DataContractSerializer								Serializer1=new DataContractSerializer(typeof(CDataContractBase));
			NetDataContractSerializer							Serializer2=new NetDataContractSerializer();
			CDataContractDerived								OriginalObject=new CDataContractDerived("Timmy","Anderson");
			CDataContractDerived								DeserializedObject1;
			CDataContractDerived								DeserializedObject2;

			using(MemoryStream MS=new MemoryStream())
			{
				Serializer1.WriteObject(MS,OriginalObject);

				Console.WriteLine(string.Format("STREAM 1 LENGTH [{0}] !",MS.Length));

				Console.WriteLine("".PadRight(79,'-'));

				MS.Seek(0,SeekOrigin.Begin);

				DumpStream(MS);

				Console.WriteLine("".PadRight(79,'-'));

				MS.Seek(0,SeekOrigin.Begin);

				DeserializedObject1=(CDataContractDerived) Serializer1.ReadObject(MS);
			}

			Console.WriteLine("DESERIALIZED OBJECT 1 [{0}] !",DeserializedObject1.ToString());
			Console.WriteLine("".PadRight(79,'-'));

			using(MemoryStream MS=new MemoryStream())
			{
				Serializer2.WriteObject(MS,OriginalObject);

				Console.WriteLine(string.Format("STREAM 2 LENGTH [{0}] !",MS.Length));

				Console.WriteLine("".PadRight(79,'-'));

				MS.Seek(0,SeekOrigin.Begin);

				DumpStream(MS);

				Console.WriteLine("".PadRight(79,'-'));

				MS.Seek(0,SeekOrigin.Begin);

				DeserializedObject2=(CDataContractDerived) Serializer2.ReadObject(MS);
			}

			Console.WriteLine("DESERIALIZED OBJECT 2 [{0}] !",DeserializedObject2.ToString());
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test2()
		{
			DataContractSerializer								Serializer1=new DataContractSerializer(typeof(DifferentAssembly.CDataContractBase));
			NetDataContractSerializer							Serializer2=new NetDataContractSerializer();
			DifferentAssembly.CDataContractDerived				OriginalObject=new DifferentAssembly.CDataContractDerived("Timmy","Anderson");
			DifferentAssembly.CDataContractDerived				DeserializedObject1;
			DifferentAssembly.CDataContractDerived				DeserializedObject2;

			using(MemoryStream MS=new MemoryStream())
			{
				Serializer1.WriteObject(MS,OriginalObject);

				Console.WriteLine(string.Format("STREAM 1 LENGTH [{0}] !",MS.Length));

				Console.WriteLine("".PadRight(79,'-'));

				MS.Seek(0,SeekOrigin.Begin);

				DumpStream(MS);

				Console.WriteLine("".PadRight(79,'-'));

				MS.Seek(0,SeekOrigin.Begin);

				DeserializedObject1=(DifferentAssembly.CDataContractDerived) Serializer1.ReadObject(MS);
			}

			Console.WriteLine("DESERIALIZED OBJECT 1 [{0}] !",DeserializedObject1.ToString());
			Console.WriteLine("".PadRight(79,'-'));

			using(MemoryStream MS=new MemoryStream())
			{
				Serializer2.WriteObject(MS,OriginalObject);

				Console.WriteLine(string.Format("STREAM 2 LENGTH [{0}] !",MS.Length));

				Console.WriteLine("".PadRight(79,'-'));

				MS.Seek(0,SeekOrigin.Begin);

				DumpStream(MS);

				Console.WriteLine("".PadRight(79,'-'));

				MS.Seek(0,SeekOrigin.Begin);

				DeserializedObject2=(DifferentAssembly.CDataContractDerived) Serializer2.ReadObject(MS);
			}

			Console.WriteLine("DESERIALIZED OBJECT 2 [{0}] !",DeserializedObject2.ToString());
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test3()
		{
			CNameSerializable									NameIn=new CNameSerializable("Timmy","Anderson",12);

			Console.WriteLine(string.Format("BEFORE SERIALIZATION - Name: [{0}] !",NameIn));

			BinaryFormatter										BF1=new BinaryFormatter();
			MemoryStream										MS=new MemoryStream();

			BF1.Serialize(MS,NameIn);

			Console.WriteLine(string.Format("STREAM LENGTH [{0}] !",MS.Length));

			Console.WriteLine("".PadRight(79,'-'));

			MS.Seek(0,SeekOrigin.Begin);

			DumpStream(MS);

			Console.WriteLine("".PadRight(79,'-'));

			MS.Seek(0,SeekOrigin.Begin);

			BinaryFormatter										BF2=new BinaryFormatter();
			CNameSerializable									NameOut=(CNameSerializable) BF2.Deserialize(MS);

			Console.WriteLine(string.Format("AFTER SERIALIZATION - Name: [{0}] !",NameOut));
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test4()
		{
			CNameSerializable									NameIn1=new CNameSerializable("Timmy","Anderson",12);
			CNameSerializable									NameIn2=new CNameSerializable("Jenny","Thompson",13);

			Console.WriteLine(string.Format("BEFORE SERIALIZATION - Name: [{0}] !",NameIn1));
			Console.WriteLine(string.Format("BEFORE SERIALIZATION - Name: [{0}] !",NameIn2));

			BinaryFormatter										BF1=new BinaryFormatter();
			MemoryStream										MS=new MemoryStream();

			// Do jedneho STREAM mozem naraz serializovat i VIAC OBJEKTOV.
			BF1.Serialize(MS,NameIn1);
			BF1.Serialize(MS,NameIn2);

			Console.WriteLine(string.Format("STREAM LENGTH [{0}] !",MS.Length));

			Console.WriteLine("".PadRight(79,'-'));

			MS.Seek(0,SeekOrigin.Begin);

			DumpStream(MS);

			Console.WriteLine("".PadRight(79,'-'));

			MS.Seek(0,SeekOrigin.Begin);

			BinaryFormatter										BF2=new BinaryFormatter();
			CNameSerializable									NameOut1=(CNameSerializable) BF1.Deserialize(MS);
			CNameSerializable									NameOut2=(CNameSerializable) BF2.Deserialize(MS);

			Console.WriteLine(string.Format("AFTER SERIALIZATION - Name: [{0}] !",NameOut1));
			Console.WriteLine(string.Format("AFTER SERIALIZATION - Name: [{0}] !",NameOut2));
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test5()
		{
			CNameSerializable									NameIn=new CNameSerializable("Timmy","Anderson",12);

			Console.WriteLine(string.Format("BEFORE SERIALIZATION - Name: [{0}] !",NameIn));

			SoapFormatter										SF1=new SoapFormatter();
			MemoryStream										MS=new MemoryStream();

			SF1.Serialize(MS,NameIn);

			Console.WriteLine(string.Format("STREAM LENGTH [{0}] !",MS.Length));

			Console.WriteLine("".PadRight(79,'-'));

			MS.Seek(0,SeekOrigin.Begin);

			DumpStream(MS);

			Console.WriteLine("".PadRight(79,'-'));

			MS.Seek(0,SeekOrigin.Begin);

			SoapFormatter										SF2=new SoapFormatter();
			CNameSerializable									NameOut=(CNameSerializable) SF2.Deserialize(MS);

			Console.WriteLine(string.Format("AFTER SERIALIZATION - Name: [{0}] !",NameOut));
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test6()
		{
			CSimpleNameBase										NameIn=new CSimpleNameDerived("Timmy","Anderson");

			Console.WriteLine(string.Format("BEFORE SERIALIZATION - Name: [{0}] !",NameIn));

			BinaryFormatter										BF1=new BinaryFormatter();
			MemoryStream										MS=new MemoryStream();

			BF1.Serialize(MS,NameIn);

			Console.WriteLine(string.Format("STREAM LENGTH [{0}] !",MS.Length));

			Console.WriteLine("".PadRight(79,'-'));

			MS.Seek(0,SeekOrigin.Begin);

			DumpStream(MS);

			Console.WriteLine("".PadRight(79,'-'));

			MS.Seek(0,SeekOrigin.Begin);

			BinaryFormatter										BF2=new BinaryFormatter();
			CSimpleNameDerived									NameOut=(CSimpleNameDerived) BF2.Deserialize(MS);

			Console.WriteLine(string.Format("AFTER SERIALIZATION - Name: [{0}] !",NameOut));
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test7()
		{
			CNameSerializableWithSerializationEvents			NameIn=new CNameSerializableWithSerializationEvents("Timmy","Anderson",12);

			Console.WriteLine(string.Format("BEFORE SERIALIZATION - Name: [{0}] !",NameIn));

			BinaryFormatter										BF1=new BinaryFormatter();
			MemoryStream										MS=new MemoryStream();

			BF1.Serialize(MS,NameIn);

			MS.Seek(0,SeekOrigin.Begin);

			BinaryFormatter										BF2=new BinaryFormatter();
			CNameSerializableWithSerializationEvents			NameOut=(CNameSerializableWithSerializationEvents) BF2.Deserialize(MS);

			Console.WriteLine(string.Format("AFTER SERIALIZATION - Name: [{0}] !",NameOut));
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test8()
		{
			CNameSerializableWithSerializationCallbacks			NameIn=new CNameSerializableWithSerializationCallbacks("Timmy","Anderson",12);

			Console.WriteLine(string.Format("BEFORE SERIALIZATION - Name: [{0}] !",NameIn));

			BinaryFormatter										BF1=new BinaryFormatter();
			MemoryStream										MS=new MemoryStream();

			BF1.Serialize(MS,NameIn);

			MS.Seek(0,SeekOrigin.Begin);

			BinaryFormatter										BF2=new BinaryFormatter();
			CNameSerializableWithSerializationCallbacks			NameOut=(CNameSerializableWithSerializationCallbacks) BF2.Deserialize(MS);

			Console.WriteLine(string.Format("AFTER SERIALIZATION - Name: [{0}] !",NameOut));
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test9()
		{
			CDerivedNameISerializable							NameIn=new CDerivedNameISerializable("Timmy","Anderson",12);

			Console.WriteLine(string.Format("BEFORE SERIALIZATION - Name: [{0}] !",NameIn));

			BinaryFormatter										BF1=new BinaryFormatter();
			MemoryStream										MS=new MemoryStream();

			BF1.Serialize(MS,NameIn);

			MS.Seek(0,SeekOrigin.Begin);

			BinaryFormatter										BF2=new BinaryFormatter();
			CDerivedNameISerializable							NameOut=(CDerivedNameISerializable) BF2.Deserialize(MS);

			Console.WriteLine(string.Format("AFTER SERIALIZATION - Name: [{0}] !",NameOut));
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test10()
		{
			CDerivedNameISerializable							NameIn=new CDerivedNameISerializable("Timmy","Anderson",12);

			Console.WriteLine(string.Format("BEFORE SERIALIZATION - Name: [{0}] !",NameIn));

			BinaryFormatter										BF1=new BinaryFormatter();
			StreamingContext									SC1=new StreamingContext(StreamingContextStates.Clone,"HELLO 1");

			// Nastavim StreamingContext.
			BF1.Context=SC1;

			MemoryStream										MS=new MemoryStream();

			BF1.Serialize(MS,NameIn);

			MS.Seek(0,SeekOrigin.Begin);

			BinaryFormatter										BF2=new BinaryFormatter();
			StreamingContext									SC2=new StreamingContext(StreamingContextStates.Clone,"HELLO 2");

			// Nastavim StreamingContext.
			BF2.Context=SC2;

			CDerivedNameISerializable							NameOut=(CDerivedNameISerializable) BF2.Deserialize(MS);

			Console.WriteLine(string.Format("AFTER SERIALIZATION - Name: [{0}] !",NameOut));
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test11()
		{
			CSingleton[]										A1={CSingleton.GetSingleton(),CSingleton.GetSingleton()};

			Console.WriteLine(string.Format("(A1[0]==A1[1]): [{0}] !",(A1[0]==A1[1])));

			using (MemoryStream Stream=new MemoryStream())
			{
				BinaryFormatter									Formatter=new BinaryFormatter();

				Console.WriteLine("BEFORE SERIALIZE !");

				Formatter.Serialize(Stream,A1);

				Console.WriteLine("AFTER SERIALIZE !");

				Stream.Position=0;

				Console.WriteLine("BEFORE DESERIALIZE !");

				CSingleton[]									A2=(CSingleton[]) Formatter.Deserialize(Stream);

				Console.WriteLine("AFTER DESERIALIZE !");

				Console.WriteLine(string.Format("(A2[0]==A2[1]): [{0}] !",(A2[0]==A2[1])));
				Console.WriteLine(string.Format("(A1[0]==A2[0]): [{0}] !",(A1[0]==A2[0])));
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test12()
		{
			// !!! CLASS CNonSerializableName NIE JE SERIALIZABLE a preto je NUTNE pouzit SERIALIZABLE SURROGATE.
			CNonSerializableName								NameIn=new CNonSerializableName("Timmy","Anderson",12);

			Console.WriteLine(string.Format("BEFORE SERIALIZATION - Name: [{0}] !",NameIn));

			BinaryFormatter										BF1=new BinaryFormatter();
			SurrogateSelector									SS1=new SurrogateSelector();

			// Nastavim SURROGATE.
			// !!! Ako 2. parameter musim nastavit StreamingContext z FORMATTER, inak moj SURROGATE IGNORUJE.
			SS1.AddSurrogate(typeof(CNonSerializableName),BF1.Context,new CNameSerializationSurrogate());

			BF1.SurrogateSelector=SS1;

			MemoryStream										MS=new MemoryStream();
			
			BF1.Serialize(MS,NameIn);

			MS.Seek(0,SeekOrigin.Begin);

			BinaryFormatter										BF2=new BinaryFormatter();
			SurrogateSelector									SS2=new SurrogateSelector();

			// Nastavim SURROGATE.
			// !!! Ako 2. parameter musim nastavit StreamingContext z FORMATTER, inak moj SURROGATE IGNORUJE.
			SS2.AddSurrogate(typeof(CNonSerializableName),BF2.Context,new CNameSerializationSurrogate());

			BF2.SurrogateSelector=SS2;

			CNonSerializableName								NameOut=(CNonSerializableName) BF2.Deserialize(MS);

			Console.WriteLine(string.Format("AFTER SERIALIZATION - Name: [{0}] !",NameOut));
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test13()
		{
			CNameForBinder										NameIn=new CNameForBinder("Timmy","Anderson",12);
			// !!! Nastavi CUSTOM BINDER, ktory vymeni ASSEMBLY NAME a TYPE NAME za CUSTOM STRINGS.
			CBinder												MyBinder1=new CBinder();

			Console.WriteLine(string.Format("BEFORE SERIALIZATION - Name: [{0}] !",NameIn));

			BinaryFormatter										BF1=new BinaryFormatter();

			BF1.Binder=MyBinder1;

			MemoryStream										MS=new MemoryStream();

			BF1.Serialize(MS,NameIn);

			MS.Seek(0,SeekOrigin.Begin);

			StreamReader										SR=new StreamReader(MS);
			string												SerializedStream=SR.ReadLine();

			Console.WriteLine("".PadRight(79,'-'));

			Console.WriteLine(string.Format("STREAM WAS SERIALIZED as: [{0}] !",SerializedStream));

			Console.WriteLine("".PadRight(79,'-'));

			MS.Seek(0,SeekOrigin.Begin);

			// !!! Nastavi CUSTOM BINDER, ktory vymeni ASSEMBLY NAME a TYPE NAME za CUSTOM STRINGS.
			CBinder												MyBinder2=new CBinder();
			BinaryFormatter										BF2=new BinaryFormatter();

			BF2.Binder=MyBinder2;

			CNameForBinder										NameOut=(CNameForBinder) BF2.Deserialize(MS);

			Console.WriteLine(string.Format("AFTER SERIALIZATION - Name: [{0}] !",NameOut));
		}
//-------------------------------------------------------------------------------------------------------
		// Zapise FILES, ktore by mali byt citane v Test15().
		private static void Test14()
		{
			DataContractSerializer								Serializer11=new DataContractSerializer(typeof(CDataContractDerived));
			DataContractSerializer								Serializer12=new DataContractSerializer(typeof(CDataContractDerived[]));
			DataContractSerializer								Serializer21=new DataContractSerializer(typeof(CDataContractDerived));
			DataContractSerializer								Serializer22=new DataContractSerializer(typeof(CDataContractDerived[]));
			CDataContractDerived								DataContractDerived=new CDataContractDerived("Timmy","Anderson");
			CDataContractDerived[]								DataContractDerivedArray=new CDataContractDerived[10];

			for(int Index=0;Index<DataContractDerivedArray.Length;Index++)
			{
				DataContractDerivedArray[Index]=new CDataContractDerived(string.Format("FirstName{0}",Index+1),string.Format("LastName{0}",Index+1));
			}

			using(FileStream MS=new FileStream("..\\..\\..\\!Files\\Text1.txt",FileMode.Create))
			{
				Serializer11.WriteObject(MS,DataContractDerived);
			}

			using(FileStream MS=new FileStream("..\\..\\..\\!Files\\Text2.txt",FileMode.Create))
			{
				Serializer12.WriteObject(MS,DataContractDerivedArray);
			}

			using(FileStream MS=new FileStream("..\\..\\..\\!Files\\Binary1.txt",FileMode.Create))
			{
				using(XmlDictionaryWriter Writer=XmlDictionaryWriter.CreateBinaryWriter(MS))
				{
					// Zapise BINARY STREAM.
					Serializer21.WriteObject(Writer,DataContractDerived);
				}
			}

			using(FileStream MS=new FileStream("..\\..\\..\\!Files\\Binary2.txt",FileMode.Create))
			{
				using(XmlDictionaryWriter Writer=XmlDictionaryWriter.CreateBinaryWriter(MS))
				{
					// Zapise BINARY STREAM.
					Serializer22.WriteObject(Writer,DataContractDerivedArray);
				}
			}

			Console.WriteLine("FILES were WRITTEN !");
		}
//-------------------------------------------------------------------------------------------------------
		// Zapise FILES, ktore by mali byt zapisane v Test14().
		private static void Test15()
		{
			DataContractSerializer								Serializer11=new DataContractSerializer(typeof(CDataContractDerived));
			DataContractSerializer								Serializer12=new DataContractSerializer(typeof(CDataContractDerived[]));
			DataContractSerializer								Serializer21=new DataContractSerializer(typeof(CDataContractDerived));
			DataContractSerializer								Serializer22=new DataContractSerializer(typeof(CDataContractDerived[]));
			CDataContractDerived								DataContractDerived1=new CDataContractDerived("Timmy","Anderson");
			CDataContractDerived								DataContractDerived2=new CDataContractDerived("Timmy","Anderson");
			CDataContractDerived[]								DataContractDerivedArray1=new CDataContractDerived[10];
			CDataContractDerived[]								DataContractDerivedArray2=new CDataContractDerived[10];

			using(FileStream MS=new FileStream("..\\..\\..\\!Files\\Text1.txt",FileMode.Open))
			{
				DataContractDerived1=(CDataContractDerived) Serializer11.ReadObject(MS);
			}

			using(FileStream MS=new FileStream("..\\..\\..\\!Files\\Text2.txt",FileMode.Open))
			{
				DataContractDerivedArray1=(CDataContractDerived[]) Serializer12.ReadObject(MS);
			}

			using(FileStream MS=new FileStream("..\\..\\..\\!Files\\Binary1.txt",FileMode.Open))
			{
				using(XmlDictionaryReader Reader=XmlDictionaryReader.CreateBinaryReader(MS,XmlDictionaryReaderQuotas.Max))
				{
					// Nacita BINARY STREAM.
					DataContractDerived2=(CDataContractDerived) Serializer21.ReadObject(Reader);
				}
			}

			using(FileStream MS=new FileStream("..\\..\\..\\!Files\\Binary2.txt",FileMode.Open))
			{
				using(XmlDictionaryReader Reader=XmlDictionaryReader.CreateBinaryReader(MS,XmlDictionaryReaderQuotas.Max))
				{
					// Nacita BINARY STREAM.
					DataContractDerivedArray2=(CDataContractDerived[]) Serializer22.ReadObject(Reader);
				}
			}

			Console.WriteLine(string.Format("DataContractDerived1: [{0}] !",DataContractDerived1));
			Console.WriteLine(string.Format("DataContractDerived2: [{0}] !",DataContractDerived2));

			for(int Index=0;Index<DataContractDerivedArray1.Length;Index++)
			{
				CDataContractDerived							DataContractDerived=DataContractDerivedArray1[Index];

				Console.WriteLine(string.Format("DataContractDerived1[{0}]: [{1}] !",Index+1,DataContractDerived));
			}

			for(int Index=0;Index<DataContractDerivedArray2.Length;Index++)
			{
				CDataContractDerived							DataContractDerived=DataContractDerivedArray2[Index];

				Console.WriteLine(string.Format("DataContractDerived2[{0}]: [{1}] !",Index+1,DataContractDerived));
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			//Test1();
			//Test2();
			//Test3();
			//Test4();
			//Test5();
			//Test6();
			//Test7();
			//Test8();
			//Test9();
			//Test10();
			//Test11();
			//Test12();
			//Test13();
			//Test14();
			Test15();

			Console.WriteLine("\nPress any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------