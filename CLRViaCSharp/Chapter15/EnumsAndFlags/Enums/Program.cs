using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace Enums
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		private static void Test1()
		{
			EColors												Color=EColors.E_C_GREEN;
			EByteColors											ByteColor=EByteColors.E_C_GREEN;

			Console.WriteLine(string.Format("Color: [{0}] !",Color));

			Console.WriteLine(string.Format("EColors: [{0}] !",Enum.GetUnderlyingType(typeof(EColors))));
			Console.WriteLine(string.Format("EByteColors: [{0}] !",Enum.GetUnderlyingType(typeof(EByteColors))));
			Console.WriteLine(string.Format("Color.CompareTo(EColors.E_C_BLUE): [{0}] !",Color.CompareTo(EColors.E_C_BLUE)));
			Console.WriteLine(string.Format("Color.GetTypeCode(): [{0}] !",Color.GetTypeCode()));
			Console.WriteLine(string.Format("ByteColor.GetTypeCode(): [{0}] !",ByteColor.GetTypeCode()));
			Console.WriteLine(string.Format("Enum.ToObject(typeof(EColors),EColors.E_C_GREEN): [{0}] !",Enum.ToObject(typeof(EColors),EColors.E_C_GREEN)));
			Console.WriteLine(string.Format("Enum.ToObject(typeof(EColors),EColors.E_C_GREEN).GetType(): [{0}] !",Enum.ToObject(typeof(EColors),EColors.E_C_GREEN).GetType()));
			Console.WriteLine(string.Format("Enum.ToObject(typeof(EColors),2): [{0}] !",Enum.ToObject(typeof(EColors),2)));
			Console.WriteLine(string.Format("Enum.ToObject(typeof(EColors),2).GetType(): [{0}] !",Enum.ToObject(typeof(EColors),2).GetType()));
			Console.WriteLine(string.Format("Enum.GetName(typeof(EColors),2): [{0}] !",Enum.GetName(typeof(EColors),2)));
			Console.WriteLine(string.Format("Enum.IsDefined(typeof(EColors),2): [{0}] !",Enum.IsDefined(typeof(EColors),2)));
			Console.WriteLine(string.Format("Enum.IsDefined(typeof(EColors),4): [{0}] !",Enum.IsDefined(typeof(EColors),4)));

			Console.WriteLine(string.Format("Color: [{0}] !",Color.ToString("D")));
			Console.WriteLine(string.Format("Color: [{0}] !",Color.ToString("X")));
			Console.WriteLine(string.Format("ByteColor: [{0}] !",ByteColor.ToString("X")));
			Console.WriteLine(string.Format("ByteColor.Format(): [{0}] !",Enum.Format(typeof(EByteColors),EByteColors.E_C_BLUE,"X")));
			Console.WriteLine(string.Format("ByteColor - FLAGS SYNTAX: [{0}] !",((EByteColors) 7).ToString("F")));

			EByteColors											ParsedByteColor=(EByteColors) Enum.Parse(typeof(EByteColors),"E_C_RED",false);

			Console.WriteLine(string.Format("ParsedByteColor: [{0}] !",ParsedByteColor));

			EFileAccessFlags									FileAccessFlags=EFileAccessFlags.E_FAF_READ | EFileAccessFlags.E_FAF_WRITE;

			Console.WriteLine(string.Format("FileAccessFlags.HasFlag(EFileAccessFlags.E_FAF_READ): [{0}] !",FileAccessFlags.HasFlag(EFileAccessFlags.E_FAF_READ)));
			Console.WriteLine(string.Format("FileAccessFlags: [{0}] !",FileAccessFlags));

			// Parse() je schopna parsovat i viacero FLAGS oddelenych ciarkou.
			EFileAccessFlags									ParsedFileAccess=(EFileAccessFlags) Enum.Parse(typeof(EFileAccessFlags),"E_FAF_READ, E_FAF_WRITE",false);

			Console.WriteLine(string.Format("ParsedFileAccess: [{0}] !",ParsedFileAccess));

			// Ani pri FLAGS hodnota 3 NIE JE DEFINED. Namiesto METHOD Enum.IsDefined) je treba pouzit METHOD Enum.HasFlags().
			Console.WriteLine(string.Format("Enum.IsDefined(typeof(EFileAccessFlags),3): [{0}] !",Enum.IsDefined(typeof(EFileAccessFlags),3)));

			Console.WriteLine(string.Format("Enum.IsDefined(typeof(EFileAccessFlags),\"E_FAF_READ\"): [{0}] !",Enum.IsDefined(typeof(EFileAccessFlags),"E_FAF_READ")));

			Console.WriteLine(string.Format("Enum.IsDefined(typeof(EFileAccessFlags),\"E_FAF_Read\"): [{0}] !",Enum.IsDefined(typeof(EFileAccessFlags),"E_FAF_Read")));
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test2()
		{
			EColors												Color1=EColors.E_C_RED;
			EColors												Color2=EColors.E_C_GREEN;

			Console.WriteLine(string.Format("Color1<Color2: [{0}] !",Color1<Color2));
			Console.WriteLine(string.Format("Color1&Color2: [{0}] !",Color1&Color2));
			Console.WriteLine(string.Format("Color1|Color2: [{0}] !",Color1|Color2));
			// COMPILER hodi ERROR.
			//Console.WriteLine(string.Format("Color1+Color2: [{0}] !",Color1+Color2));
			Console.WriteLine(string.Format("Color1+1: [{0}] !",Color1+1));
			Console.WriteLine(string.Format("Color1++: [{0}] !",Color1++));

			EFileAccessFlags									FileAccessFlags1=EFileAccessFlags.E_FAF_READ;
			EFileAccessFlags									FileAccessFlags2=EFileAccessFlags.E_FAF_WRITE;

			Console.WriteLine(string.Format("FileAccessFlags1<FileAccessFlags2: [{0}] !",FileAccessFlags1<FileAccessFlags2));
			Console.WriteLine(string.Format("FileAccessFlags1&FileAccessFlags2: [{0}] !",FileAccessFlags1&FileAccessFlags2));
			Console.WriteLine(string.Format("FileAccessFlags1|FileAccessFlags2: [{0}] !",FileAccessFlags1|FileAccessFlags2));
			// COMPILER hodi ERROR.
			//Console.WriteLine(string.Format("FileAccessFlags1+FileAccessFlags2: [{0}] !",FileAccessFlags1+FileAccessFlags2));
			Console.WriteLine(string.Format("FileAccessFlags1+1: [{0}] !",FileAccessFlags1+1));
			Console.WriteLine(string.Format("FileAccessFlags1++: [{0}] !",FileAccessFlags1++));
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test3()
		{
			foreach(EColors Value in Enum.GetValues(typeof(EColors)))
			{
				Console.WriteLine(string.Format("Value: [{0}] !",Value));
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test4()
		{
			foreach(string Name in Enum.GetNames(typeof(EColors)))
			{
				Console.WriteLine(string.Format("Name: [{0}] !",Name));
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test5()
		{
			EColors												Color=EColors.E_C_GREEN;

			Console.WriteLine(string.Format("EXTENSION METHOD OUTPUT: [{0}] !",Color.NiceString()));
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
			Test5();

			Console.WriteLine("\nPress any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------