using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Globalization;
using System.Configuration;
using System.Runtime.InteropServices;
using System.Windows.Forms;
using System.IO;
using System.Diagnostics;
//-------------------------------------------------------------------------------------------------------
namespace Strings
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		// Vypisanie vsetkych TEXTOVYCH ELEMENTOV (znakov) pre jazyky Dalekeho Vychodu.
		private static void EnumText(string String)
		{
			string												Output=string.Empty;
			
			Console.WriteLine(string.Format("EnumText() - String.Length [{0}] !",String.Length));

			for(int Index=0;Index<String.Length;Index++)
			{
				Output+=string.Format("Text element at index {0} is '{1}' !{2}",Index,String[Index],Environment.NewLine);
			}

			MessageBox.Show(Output,"Result of FOREACH");
		}
//-------------------------------------------------------------------------------------------------------
		// Vypisanie vsetkych TEXTOVYCH ELEMENTOV (znakov) pre jazyky Dalekeho Vychodu.
		private static void EnumTextElements(string String)
		{
			StringInfo											SI=new StringInfo(String);
			string												Output=string.Empty;
			TextElementEnumerator								CharEnum=StringInfo.GetTextElementEnumerator(String);
			
			Console.WriteLine(string.Format("EnumTextElement() - SI.LengthInTextElements [{0}] !",SI.LengthInTextElements));

			while (CharEnum.MoveNext()==true)
			{
				Output+=string.Format("Text element at index {0} is '{1}' !{2}",CharEnum.ElementIndex,CharEnum.GetTextElement(),Environment.NewLine);
			}

			MessageBox.Show(Output,"Result of GetTextElementEnumerator()");
		}
//-------------------------------------------------------------------------------------------------------
		private static void EnumTextElementIndexes(string String)
		{
			StringInfo											SI=new StringInfo(String);
			string												Output=string.Empty;
			int[]												TextElemIndex=StringInfo.ParseCombiningCharacters(String);

			Console.WriteLine(string.Format("EnumTextElementIndexes() - SI.LengthInTextElements [{0}] !",SI.LengthInTextElements));

			for (int Index=0;Index<TextElemIndex.Length;Index++)
			{
				Output+=string.Format("Text element {0} starts at index {1} !{2}",Index,TextElemIndex[Index],Environment.NewLine);
			}

			MessageBox.Show(Output,"Result of ParseCombiningCharacters()");
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		private static void Test1()
		{
			// Tento retazec sa uklada do METADATA.
			string												Text="Hello Timmy";

			Console.WriteLine(string.Format("String: [{0}] !",Text));
		}
//-------------------------------------------------------------------------------------------------------
		private unsafe static void Test2()
		{
			string												Text="Hello Timmy";
			IntPtr												Buffer=Marshal.AllocHGlobal(100);
			char*												StringBuffer=(char*) Buffer;

			for(int Index=0;Index<Text.Length;Index++)
			{
				StringBuffer[Index]=Text[Index];
			}

			StringBuffer[Text.Length]='\0';

			// STRING sa vytvori z [char*].
			string												NewText=new string(StringBuffer);

			Console.WriteLine(string.Format("String: [{0}] !",NewText));

			Marshal.FreeHGlobal(Buffer);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test3()
		{
			string												S1="Strasse";
			string												S2="Straße";
			bool												IsEqual;

			// ORDINAL porovnanie.
			IsEqual=(string.Compare(S1,S2,StringComparison.Ordinal)==0);

			Console.WriteLine(string.Format("ORDINAL comparison: [{0}] {2} [{1}] !",S1,S2,IsEqual ? "==" : "!="));

			// Specifikujem CULTURE na 'de-DE'.
			CultureInfo											CI=new CultureInfo("de-DE");

			// CULTURE AWARE porovnanie.
			IsEqual=(string.Compare(S1,S2,true,CI)==0);

			Console.WriteLine(string.Format("CULTURE-AWARE comparison: [{0}] {2} [{1}] !",S1,S2,IsEqual ? "==" : "!="));

			// CULTURE AWARE porovnanie s pouzitim CLASS CompareInfo.
			IsEqual=(CI.CompareInfo.Compare(S1,S2,CompareOptions.StringSort)==0);

			Console.WriteLine(string.Format("CULTURE-AWARE STRING SORT comparison: [{0}] {2} [{1}] !",S1,S2,IsEqual ? "==" : "!="));

			// Porovnanie OPERATOROM - ORDINAL porovnanie.
			IsEqual=(S1==S2);

			Console.WriteLine(string.Format("OPERATOR comparison: [{0}] {2} [{1}] !",S1,S2,IsEqual ? "==" : "!="));
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test4()
		{
			string												S1="Hello Timmy";
			string												S2="Hello " + ConfigurationManager.AppSettings["SomeString"].ToString();
			
			// Kedze NEPOUZIVAM STRING INTERNING a jedna sa o 2 ROZLICNE OBJEKTY porovnane REFERENCII vrati FALSE.
			Console.WriteLine(string.Format("DEFAULT: [{0}] !",object.ReferenceEquals(S1, S2)));

			S1=string.Intern(S1);
			S2=string.Intern(S2);

			// Kedze EXPLICITNE pouzivam STRING INTERNING vrati VZDY TRUE, lebo STRING INTERNING sposobi, ze sa v HashTable ktoru interne pouziva vytvori iba 1 OBJEKT pre 2 STRINGS obsahujuce tu istu hodnotu.
			Console.WriteLine(string.Format("INTERN: [{0}] !",object.ReferenceEquals(S1, S2)));
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test5()
		{
			// Japonske znaky o dlzke 4 BYTES.
			string												S="a\u0304\u0308bc\u0327";

			EnumText(S);
			EnumTextElements(S);
			EnumTextElementIndexes(S);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test6()
		{
			StringBuilder										SB=new StringBuilder(1000);

			// CHAINING METHODS.
			SB.Append("Hello").Append(" ").Append("Timmy !");

			Console.WriteLine(string.Format("Text: [{0}] !",SB.ToString()));

			SB.Replace("Timmy","Jenny");

			Console.WriteLine(string.Format("Text: [{0}] !",SB.ToString()));
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test7()
		{
			// TYPES Double aj DateTime implementuju INTERFACE IFormatable.
			double												Value1=10.123;
			DateTime											Value2=DateTime.Now;

			Console.WriteLine(string.Format("Value1 [{0}] !",Value1.ToString()));
			Console.WriteLine(string.Format("Value1 [{0}] !",Value1.ToString("C")));
			Console.WriteLine(string.Format("Value1 [{0}] !",Value1.ToString("E")));
			Console.WriteLine(string.Format("Value1 [{0}] !",Value1.ToString("C",new CultureInfo("sk-SK"))));
			Console.WriteLine(string.Format("Value1 [{0}] !",Value1.ToString("E",new CultureInfo("sk-SK"))));

			Console.WriteLine(string.Format("Value2 [{0}] !",Value2.ToString()));
			Console.WriteLine(string.Format("Value2 [{0}] !",Value2.ToString("dd/MM/yyyy hh:mm:ss")));
			Console.WriteLine(string.Format("Value2 [{0}] !",Value2.ToString("dd/MM/yyyy hh:mm:ss",new CultureInfo("sk-SK"))));
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test8()
		{
			string												Text=string.Format("Number [{0:X}], Number [{1:E}], Date [{2:D}], Time [{3:T}] !",101,10.123,DateTime.Now,DateTime.Now);

			Console.WriteLine(Text);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test9()
		{
			// !!! CUSTOM FORMATTING (1. PARAMETER) pridava do STRING definovany typ ZATVORIEK.
			string												Text=string.Format(new CCustomFormatterAddBrackets(),"!!!!! Value1 {0:[]}, Value2 [{1:()}] !","Timmy Anderson",12);

			Console.WriteLine(Text);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test10()
		{
			int													Value;

			try
			{
				Value=int.Parse("100");

				Console.WriteLine(string.Format("Value: [{0}] !",Value));
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION: [{0}] !",E.Message));
			}

			try
			{
				// Hodi EXCEPTION.
				Value=int.Parse("1 00");

				Console.WriteLine(string.Format("Value: [{0}] !",Value));
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION: [{0}] !",E.Message));
			}

			try
			{
				Value=int.Parse(" 100");

				Console.WriteLine(string.Format("Value: [{0}] !",Value));
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION: [{0}] !",E.Message));
			}

			try
			{
				// Hodi EXCEPTION.
				Value=int.Parse(" 100",NumberStyles.None);

				Console.WriteLine(string.Format("Value: [{0}] !",Value));
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION: [{0}] !",E.Message));
			}

			try
			{
				// Hodi EXCEPTION.
				Value=int.Parse("0x30",NumberStyles.HexNumber);

				Console.WriteLine(string.Format("Value: [{0}] !",Value));
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION: [{0}] !",E.Message));
			}

			try
			{
				Value=int.Parse("1A",NumberStyles.HexNumber);

				Console.WriteLine(string.Format("Value: [{0}] !",Value));
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION: [{0}] !",E.Message));
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test11()
		{
			using(FileStream FS=new FileStream(@"..\..\..\!Output\UTF8.txt",FileMode.Create,FileAccess.ReadWrite))
			{
				using(StreamWriter SW=new StreamWriter(FS))
				{
					// Zapisem anglicky text.
					SW.WriteLine("Timmy !");

					// Zapisem slovensky text.
					// !!! Zapise sa VIAC ZNAKOV, lebo sa STANDARDNE pouziva UTF-8, ktora ma VARIABILNU DLZKU ZNAKU.
					SW.WriteLine("Čšťĺž !");
				}
			}

			using(FileStream FS=new FileStream(@"..\..\..\!Output\UTF8.txt",FileMode.Open,FileAccess.ReadWrite))
			{
				using(StreamReader SR=new StreamReader(FS))
				{
					// Nacitam anglicky text.
					string										Text1=SR.ReadLine();

					// Nacitam slovensky text.
					string										Text2=SR.ReadLine();

					Console.WriteLine(string.Format("Text1: [{0}] !",Text1));

					// !!! Na KONZOLE to NEZOBRAZI SPRAVNE, ale TEXT SPRAVNE OBSAHUJE i DIAKRITIKU.
					Console.WriteLine(string.Format("Text2: [{0}] !",Text2));

					// !!! V Output Window sa zobrazi spravne.
					Debug.WriteLine(string.Format("Text2: [{0}] !",Text2));
				}
			}

			// Pouzijem UTF-16.
			using(FileStream FS=new FileStream(@"..\..\..\!Output\UTF16.txt",FileMode.Create,FileAccess.ReadWrite))
			{
				using(StreamWriter SW=new StreamWriter(FS,Encoding.Unicode))
				{
					// Zapisem anglicky text.
					SW.WriteLine("Timmy !");

					// Zapisem slovensky text.
					// !!! Zapise sa ROVNAKY POCET ZNAKOV, lebo pouzivam UTF-16, ktora ma KONSTANTU DLZKU ZNAKU.
					SW.WriteLine("Čšťĺž !");
				}
			}

			using(FileStream FS=new FileStream(@"..\..\..\!Output\UTF16.txt",FileMode.Open,FileAccess.ReadWrite))
			{
				using(StreamReader SR=new StreamReader(FS,Encoding.Unicode))
				{
					// Nacitam anglicky text.
					string										Text1=SR.ReadLine();

					// Nacitam slovensky text.
					string										Text2=SR.ReadLine();

					Console.WriteLine(string.Format("Text1: [{0}] !",Text1));

					// !!! Na KONZOLE to NEZOBRAZI SPRAVNE, ale TEXT SPRAVNE OBSAHUJE i DIAKRITIKU.
					Console.WriteLine(string.Format("Text2: [{0}] !",Text2));

					// !!! V Output Window sa zobrazi spravne.
					Debug.WriteLine(string.Format("Text2: [{0}] !",Text2));
				}
			}

			// Pouzijem UTF-32.
			using(FileStream FS=new FileStream(@"..\..\..\!Output\UTF32.txt",FileMode.Create,FileAccess.ReadWrite))
			{
				using(StreamWriter SW=new StreamWriter(FS,Encoding.UTF32))
				{
					// Zapisem anglicky text.
					SW.WriteLine("Timmy !");

					// Zapisem slovensky text.
					// !!! Zapise sa ROVNAKY POCET ZNAKOV, lebo pouzivam UTF-32, ktora ma KONSTANTU DLZKU ZNAKU.
					SW.WriteLine("Čšťĺž !");
				}
			}

			using(FileStream FS=new FileStream(@"..\..\..\!Output\UTF32.txt",FileMode.Open,FileAccess.ReadWrite))
			{
				using(StreamReader SR=new StreamReader(FS,Encoding.UTF32))
				{
					// Nacitam anglicky text.
					string										Text1=SR.ReadLine();

					// Nacitam slovensky text.
					string										Text2=SR.ReadLine();

					Console.WriteLine(string.Format("Text1: [{0}] !",Text1));

					// !!! Na KONZOLE to NEZOBRAZI SPRAVNE, ale TEXT SPRAVNE OBSAHUJE i DIAKRITIKU.
					Console.WriteLine(string.Format("Text2: [{0}] !",Text2));

					// !!! V Output Window sa zobrazi spravne.
					Debug.WriteLine(string.Format("Text2: [{0}] !",Text2));
				}
			}

			// Pouzijem CODE PAGE 852.
			using(FileStream FS=new FileStream(@"..\..\..\!Output\UTFCodePage852.txt",FileMode.Create,FileAccess.ReadWrite))
			{
				using(StreamWriter SW=new StreamWriter(FS,Encoding.GetEncoding(852)))
				{
					// Zapisem anglicky text.
					SW.WriteLine("Timmy !");

					// Zapisem slovensky text.
					SW.WriteLine("Čšťĺž !");
				}
			}

			using(FileStream FS=new FileStream(@"..\..\..\!Output\UTFCodePage852.txt",FileMode.Open,FileAccess.ReadWrite))
			{
				using(StreamReader SR=new StreamReader(FS,Encoding.GetEncoding(852)))
				{
					// Nacitam anglicky text.
					string										Text1=SR.ReadLine();

					// Nacitam slovensky text.
					string										Text2=SR.ReadLine();

					Console.WriteLine(string.Format("Text1: [{0}] !",Text1));

					// !!! Na KONZOLE to NEZOBRAZI SPRAVNE, ale TEXT SPRAVNE OBSAHUJE i DIAKRITIKU.
					Console.WriteLine(string.Format("Text2: [{0}] !",Text2));

					// !!! V Output Window sa zobrazi spravne.
					Debug.WriteLine(string.Format("Text2: [{0}] !",Text2));
				}
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test12()
		{
			char[]												Chars="Timmy Anderson".ToCharArray();

			// Vytvori sa instancia CLASS Encoder.
			Encoder												EncoderObject=Encoding.UTF32.GetEncoder();
			// Vrati pocet BYTES potrebnych na ulozenie ENCODED STRING.
			int													ByteBufferSize=EncoderObject.GetByteCount(Chars,0,Chars.Length,true);
			byte[]												ByteBuffer=new byte[ByteBufferSize];

			EncoderObject.GetBytes(Chars,0,Chars.Length,ByteBuffer,0,true);

			StringBuilder										SB=new StringBuilder();

			SB.Append("BYTES [");

			for(int Index=0;Index<ByteBuffer.Length;Index++)
			{
				if (Index!=0)
				{
					SB.Append(",");
				}

				// Formatuje sa ako HEXA VALUE.
				SB.AppendFormat("0x{0}",ByteBuffer[Index].ToString("X2"));
			}

			SB.AppendLine("] !");

			Console.WriteLine(SB.ToString());

			// Vytvori sa instancia CLASS Decoder.
			Decoder												DecoderObject=Encoding.UTF32.GetDecoder();
			// Vrati pocet CHARACTERS potrebnych na ulozenie DECODED STRING.
			int													CharBufferSize=DecoderObject.GetCharCount(ByteBuffer,0,ByteBuffer.Length,true);
			char[]												CharBuffer=new char[CharBufferSize];

			DecoderObject.GetChars(ByteBuffer,0,ByteBuffer.Length,CharBuffer,0,true);

			string												Text=new string(CharBuffer);

			Console.WriteLine(string.Format("Text [{0}] !",Text));
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test13()
		{
			string												InputText="Timmy Anderson";
			string												Base64=Convert.ToBase64String(Encoding.ASCII.GetBytes(InputText));

			Console.WriteLine(string.Format("Base64 [{0}] !",Base64));

			byte[]												RawBytes=Convert.FromBase64String(Base64);
			string												OutputText=Encoding.ASCII.GetString(RawBytes);

			Console.WriteLine(string.Format("OutputText [{0}] !",OutputText));
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
			Test13();

			Console.WriteLine("Press any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------