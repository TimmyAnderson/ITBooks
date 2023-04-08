using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace Operators
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		private static void Test1()
		{
			CMyInt												MyInt1=new CMyInt(5);
			CMyInt												MyInt2=new CMyInt(6);

			CMyInt												Result1=MyInt1+MyInt2;

			Console.WriteLine(string.Format("Result1: [{0}] !",Result1.Int));

			CMyInt												Result2=MyInt1+7;

			Console.WriteLine(string.Format("Result2: [{0}] !",Result2.Int));
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test2()
		{
			CMyInt												MyInt1=new CMyInt(5);
			CMyInt												MyInt2=new CMyInt(6);
			CMyInt												MyInt3=new CMyInt(6);

			Console.WriteLine(string.Format("[MyInt1==MyInt2]: [{0}] !",MyInt1==MyInt2));
			Console.WriteLine(string.Format("[MyInt1==MyInt3]: [{0}] !",MyInt1==MyInt3));
			Console.WriteLine(string.Format("[MyInt2==MyInt3]: [{0}] !",MyInt2==MyInt3));
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test3()
		{
			SMyInt												MyInt1=new SMyInt(5);
			SMyInt												MyInt2=new SMyInt(6);

			SMyInt												Result1=MyInt1+MyInt2;

			Console.WriteLine(string.Format("Result1: [{0}] !",Result1.Int));

			SMyInt												Result2=MyInt1+7;

			Console.WriteLine(string.Format("Result2: [{0}] !",Result2.Int));
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test4()
		{
			Console.WriteLine("STEP 1 !");

			// Pouzijem EXPLICITNY OPERATOR PRETYPOVANIA.
			CMyInt												MyInt=(CMyInt) 12;

			Console.WriteLine("STEP 2 !");
			Console.WriteLine(string.Format("MyInt: [{0}] !",MyInt.Int));

			// Pouzijem EXPLICITNY OPERATOR PRETYPOVANIA.
			int													Int=MyInt;

			Console.WriteLine("STEP 3 !");
			Console.WriteLine(string.Format("Int: [{0}] !",Int));
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test5()
		{
			Console.WriteLine("STEP 1 !");

			// Pouzijem EXPLICITNY OPERATOR PRETYPOVANIA.
			SMyInt												MyInt=(SMyInt) 12;

			Console.WriteLine("STEP 2 !");
			Console.WriteLine(string.Format("MyInt: [{0}] !",MyInt.Int));

			// Pouzijem EXPLICITNY OPERATOR PRETYPOVANIA.
			int													Int=MyInt;

			Console.WriteLine("STEP 3 !");
			Console.WriteLine(string.Format("Int: [{0}] !",Int));
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