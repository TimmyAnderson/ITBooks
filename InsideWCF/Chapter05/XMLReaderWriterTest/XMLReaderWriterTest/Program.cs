using System;
using System.Collections.Generic;
using System.Text;
using System.Xml;
using System.IO;
//-------------------------------------------------------------------------------------------------------
namespace XMLReaderWriterTest
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		private static void WriteStreamToFile(string FileName, Stream StreamToWrite)
		{
			DirectoryInfo	WorkingDir=new DirectoryInfo(AppDomain.CurrentDomain.BaseDirectory);
			string			ParentDir=WorkingDir.Parent.Parent.Parent.FullName;
			string			DestinationDir=string.Format("{0}\\!XML",ParentDir);
			string			Path=string.Format("{0}\\{1}",DestinationDir,FileName);

			StreamToWrite.Seek(0,SeekOrigin.Begin);

			using(FileStream FS=new FileStream(Path,FileMode.Create))
			{
				StreamToWrite.CopyTo(FS);
				StreamToWrite.Flush();
			}
		}
//-------------------------------------------------------------------------------------------------------
		static void WriteStreamToConsole(MemoryStream Stream)
		{
			byte[]						Bytes;

			Console.WriteLine("XmlDictionaryWriter (Text-UTF8) wrote [{0}] bytes !", Stream.Position);

			Stream.Position=0;
			Bytes=Stream.ToArray();

			Console.WriteLine(string.Format("Bytes: [{0}] !",BitConverter.ToString(Bytes)));
			Console.WriteLine(string.Format("\nData read from stream:\n{0}\n", new StreamReader(Stream).ReadToEnd()));
		}
//-------------------------------------------------------------------------------------------------------
		// Volana pri UZATVARANI XmlDictionaryReader.
		private static void OnReaderFinished(XmlDictionaryReader XDR)
		{
			Console.WriteLine("XmlDictionaryReader CLOSED !!!");
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		static void XMLDictionaryTest()
		{
			XmlDictionary				Dictionary=new XmlDictionary();
			List<XmlDictionaryString>	StringList=new List<XmlDictionaryString>();

			// !!! Po pridani stringu do Dictionary vrati XmlDictionaryString, ktory si ulozim do List kolekcie aby som ho mohol vypisat.
			// !!! XmlDictionary neumoznuje ITERACIU ULOZENYCH ITEMS, ani odoberat ITEMS.
			StringList.Add(Dictionary.Add("ReleaseDate"));
			StringList.Add(Dictionary.Add("GoodSongs"));
			StringList.Add(Dictionary.Add("Studio"));

			foreach(XmlDictionaryString Entry in StringList)
				Console.WriteLine("Key = [{0}], Value = [{1}] !", Entry.Key, Entry.Value);
		}
//-------------------------------------------------------------------------------------------------------
		static void TextFormatTest()
		{
			MemoryStream				Stream=new MemoryStream();

			// Otvoril som Writer v Text kodovani.
			// Hodnota true v poslednom parametri znamenat, ze XmlDictionaryWriter vlastni stream a jeho uzavretie uzavrie Stream.
			using(XmlDictionaryWriter Writer=XmlDictionaryWriter.CreateTextWriter(Stream, Encoding.UTF8, true))
			{
				// Ma velke mnozstvo pretazenych metod.
				Writer.WriteStartElement("Names","Namespace1");
				Writer.WriteElementString("FullName", "Namespace2", "Timmy Anderson");
				Writer.WriteElementString("FullName", "Namespace2", "Jenny Thompson");
				Writer.WriteEndElement();

				Writer.Flush();

				WriteStreamToConsole(Stream);

				WriteStreamToFile("Text.xml",Stream);
			}
		}
//-------------------------------------------------------------------------------------------------------
		static void MTOMFormatTest()
		{
			MemoryStream				Stream1=new MemoryStream();
			MemoryStream				Stream2=new MemoryStream();

			// Otvoril som Writer v MTOM kodovani.
			using(XmlDictionaryWriter Writer=XmlDictionaryWriter.CreateMtomWriter(Stream1,Encoding.UTF8,1000,"Application/soap+xml"))
			{
				// Ma velke mnozstvo pretazenych metod.
				Writer.WriteStartElement("Names","Namespace1");
				Writer.WriteElementString("FullName", "Namespace2", "Timmy Anderson");
				Writer.WriteElementString("FullName", "Namespace2", "Jenny Thompson");
				Writer.WriteEndElement();

				Writer.Flush();

				WriteStreamToConsole(Stream1);
				WriteStreamToFile("MTOM1.xml",Stream1);
			}

			// Otvoril som Writer v MTOM kodovani.
			// !!! Iny sposob vytvorenia, kde mam VACSIU KONTROLU NAD MTOM, ale pri nespravnom nastaveni ak RECEIVER toto nastavenie NEPOZNA, moze byt takto serializovany XML byt na strane RECEIVER NECITATELNY.
			using(XmlDictionaryWriter Writer=XmlDictionaryWriter.CreateMtomWriter(Stream2,Encoding.UTF8,1000,"startInfo","boundry","urn:startUri",true,true))
			{
				// Ma velke mnozstvo pretazenych metod.
				Writer.WriteStartElement("Names","Namespace1");
				Writer.WriteElementString("FullName", "Namespace2", "Timmy Anderson");
				Writer.WriteElementString("FullName", "Namespace2", "Jenny Thompson");
				Writer.WriteEndElement();

				Writer.Flush();

				WriteStreamToConsole(Stream2);
				WriteStreamToFile("MTOM2.xml",Stream2);
			}
		}
//-------------------------------------------------------------------------------------------------------
		static void BinaryFormatTest1()
		{
			MemoryStream				Stream=new MemoryStream();

			// Otvoril som Writer v Binary kodovani.
			// !!! Kedze ako DICTIONARY davam NULL, tak sa DICTIONARY NEBUDE POUZIVAT a NEDOJDE ku KOMPRESII na zaklade DICTIONARY.
			using(XmlDictionaryWriter Writer=XmlDictionaryWriter.CreateBinaryWriter(Stream,null,null))
			{
				// Ma velke mnozstvo pretazenych metod.
				Writer.WriteStartElement("Names","Namespace1");
				Writer.WriteElementString("FullName", "Namespace2", "Timmy Anderson");
				Writer.WriteElementString("FullName", "Namespace2", "Jenny Thompson");
				Writer.WriteEndElement();

				Writer.Flush();

				WriteStreamToConsole(Stream);
				WriteStreamToFile("BinaryNoDictionary.xml",Stream);
			}
		}
//-------------------------------------------------------------------------------------------------------
		static void BinaryFormatTest2()
		{
			MemoryStream				Stream=new MemoryStream();
			XmlDictionary				Dictionary=new XmlDictionary();
			List<XmlDictionaryString>	StringList=new List<XmlDictionaryString>();

			// Vytvorim DICTIONARY s menami ELEMENTS a NAMESPACES.
			StringList.Add(Dictionary.Add("Namespace1"));
			StringList.Add(Dictionary.Add("Namespace2"));
			StringList.Add(Dictionary.Add("Names"));
			StringList.Add(Dictionary.Add("FullName"));

			// Otvoril som Writer v Binary kodovani.
			// Pouzijem dictionary, cim je vysledny stream ovela kratsi.
			using(XmlDictionaryWriter Writer=XmlDictionaryWriter.CreateBinaryWriter(Stream,Dictionary))
			{
				// !!!!! Aby sa APLIKOVALA KOMPRESIA cez XmlDictionary je treba pouzivat metody, ktore ako parametre maju XmlDictionaryString.
				Writer.WriteStartElement(StringList[2],StringList[0]);
				Writer.WriteElementString(StringList[3],StringList[1],"Timmy Anderson");
				Writer.WriteElementString(StringList[3],StringList[1],"Jenny Thompson");
				Writer.WriteEndElement();

				Writer.Flush();

				WriteStreamToConsole(Stream);
				WriteStreamToFile("BinaryWithDictionary.xml",Stream);
			}
		}
//-------------------------------------------------------------------------------------------------------
		static void BinaryFormatTest3()
		{
			MemoryStream				Stream=new MemoryStream();
			XmlDictionary				Dictionary=new XmlDictionary();
			List<XmlDictionaryString>	StringList=new List<XmlDictionaryString>();

			XmlBinaryWriterSession		Session=new XmlBinaryWriterSession();

			// Vytvorim DICTIONARY s menami ELEMENTS a NAMESPACES.
			StringList.Add(Dictionary.Add("Namespace1"));
			StringList.Add(Dictionary.Add("Namespace2"));
			StringList.Add(Dictionary.Add("Names"));
			StringList.Add(Dictionary.Add("FullName"));

			int							Key;

			foreach(XmlDictionaryString XDS in StringList)
			{
				Session.TryAdd(XDS,out Key);
				Console.WriteLine(string.Format("Key: [{0}], Value: [{1}] !",Key,XDS.Value));
			}

			// Otvoril som Writer v Binary kodovani.
			// Pouzijem dictionary, cim je vysledny stream ovela kratsi.
			using(XmlDictionaryWriter Writer=XmlDictionaryWriter.CreateBinaryWriter(Stream,Dictionary,Session))
			{
				// !!!!! Aby sa APLIKOVALA KOMPRESIA cez XmlDictionary je treba pouzivat metody, ktore ako parametre maju XmlDictionaryString.
				Writer.WriteStartElement(StringList[2],StringList[0]);
				Writer.WriteElementString(StringList[3],StringList[1],"Timmy Anderson");
				Writer.WriteElementString(StringList[3],StringList[1],"Jenny Thompson");
				Writer.WriteEndElement();

				Writer.Flush();

				WriteStreamToConsole(Stream);
				WriteStreamToFile("BinaryWithDictionaryAndWithSession.xml",Stream);
			}
		}
//-------------------------------------------------------------------------------------------------------
		static void ReaderTest()
		{
			MemoryStream				Stream=new MemoryStream();

			// Otvoril som Writer v Text kodovani.
			// Hodnota true v poslednom parametri znamenat, ze XmlDictionaryWriter vlastni stream a jeho uzavretie uzavrie Stream.
			using(XmlDictionaryWriter Writer=XmlDictionaryWriter.CreateTextWriter(Stream, Encoding.UTF8, true))
			{
				// Ma velke mnozstvo pretazenych metod.
				Writer.WriteStartElement("Names","Namespace1");
				Writer.WriteElementString("FullName", "Namespace2", "Timmy Anderson");
				Writer.WriteElementString("FullName", "Namespace2", "Jenny Thompson");
				Writer.WriteEndElement();

				Writer.Flush();

				WriteStreamToConsole(Stream);

				Stream.Position=0;

				// Vytvorim READER.
				// DEFINUJEM DELEGATE OnXmlDictionaryReaderClose.
				XmlDictionaryReader		Reader=XmlDictionaryReader.CreateTextReader(Stream,Encoding.UTF8,new XmlDictionaryReaderQuotas(),new OnXmlDictionaryReaderClose(OnReaderFinished));

				Reader.MoveToContent();
        
				Console.WriteLine(string.Format("Read XML Content: [{0}] !", Reader.ReadOuterXml()));
				Console.WriteLine("Reader.Close() !");
				Reader.Close();
			}
		}
//-------------------------------------------------------------------------------------------------------
		static void RoundTripTest()
		{
			MemoryStream				Stream=new MemoryStream();

			// Vytvorim dictionary a naplnim ho.
			XmlDictionary				Dictionary=new XmlDictionary();
			List<XmlDictionaryString>	StringList=new List<XmlDictionaryString>();

			StringList.Add(Dictionary.Add("Namespace1"));
			StringList.Add(Dictionary.Add("Namespace2"));
			StringList.Add(Dictionary.Add("Names"));
			StringList.Add(Dictionary.Add("FullName"));

			using(XmlDictionaryWriter Writer=XmlDictionaryWriter.CreateBinaryWriter(Stream, Dictionary, null))
			{
				// Zapisem data do XmlDictionaryWriter.
				Writer.WriteStartElement(StringList[2],StringList[0]);
				Writer.WriteElementString(StringList[3],StringList[1],"Timmy Anderson");
				Writer.WriteElementString(StringList[3],StringList[1],"Jenny Thompson");
				Writer.WriteEndElement();

				Writer.Flush();
				
				Console.WriteLine(string.Format("Using Dictionary, wrote [{0}] bytes !", Stream.Position));

				Stream.Position=0;
				
				Byte[]					Bytes=Stream.ToArray();

				Console.WriteLine(string.Format("\nBytes: [{0}] !",BitConverter.ToString(Bytes)));

				// Vytvorim XmlDictionaryReader a nacitam data z XmlDictionaryWriter.
				XmlDictionaryReader		Reader=XmlDictionaryReader.CreateBinaryReader(Stream, Dictionary, new XmlDictionaryReaderQuotas());

				Reader.Read();

				Console.WriteLine(string.Format("\nData read from stream:\n{0}\n", Reader.ReadOuterXml()));
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			//XMLDictionaryTest();
			//TextFormatTest();
			//MTOMFormatTest();
			//BinaryFormatTest1();
			//BinaryFormatTest2();
			//BinaryFormatTest3();
			//ReaderTest();
			RoundTripTest();

			Console.WriteLine();
			Console.WriteLine("Press any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------