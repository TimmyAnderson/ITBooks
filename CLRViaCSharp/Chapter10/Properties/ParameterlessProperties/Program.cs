using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Dynamic;
//-------------------------------------------------------------------------------------------------------
namespace ParameterlessProperties
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		private static void Test1()
		{
			try
			{
				CName											Name=new CName();

				Name.FirstName="Timmy";
				Name.LastName="Anderson";
				Name.Age=12;

				Console.WriteLine(string.Format("Name: [{0}] !",Name));

				Name.Age=-10;

				Console.WriteLine(string.Format("Name: [{0}] !",Name));
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION: [{0}] !",E.Message));
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test2()
		{
			CName												Name=new CName();

			Name.FirstName="Timmy";
			Name.LastName="Anderson";
			Name.Age=12;

			Console.WriteLine(string.Format("Name: [{0}] !",Name));
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test3()
		{
			CBase												Name=new CDerived();

			Console.WriteLine(string.Format("ABSTRACT - Name: [{0}] !",Name.Name));
			Console.WriteLine(string.Format("STATIC - Name: [{0}] !",CName.StaticName));
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test4()
		{
			CNameAutomaticProperties							Name=new CNameAutomaticProperties();

			Name.FirstName="Timmy";
			Name.LastName="Anderson";
			Name.Age=12;

			Console.WriteLine(string.Format("Name: [{0}] !",Name));
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test5()
		{
			CNameWithInternalSetters							Name=new CNameWithInternalSetters();

			Name.FirstName="Timmy";
			Name.LastName="Anderson";
			Name.Age=12;

			Console.WriteLine(string.Format("Name: [{0} {1}], Age [{2}] !",Name.FirstName,Name.LastName,Name.Age));
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test6()
		{
			// Vola sa SETTER.
			CInitializersTest									IT1=new CInitializersTest(){SimpleProperty="Timmy"};

			Console.WriteLine(string.Format("IT1.SimpleProperty: [{0}] !",IT1.SimpleProperty));

			// Vola sa SETTER.
			CInitializersTest									IT2=new CInitializersTest(){ArrayProperty=new string[]{"Timmy","Jenny","Atreyu"}};

			Console.WriteLine(string.Format("IT2.ArrayProperty.Length: [{0}] !",IT2.ArrayProperty.Length));

			// !!! Vola sa metoda List<T>.Add().
			CInitializersTest									IT3=new CInitializersTest(){ListProperty={"Timmy","Jenny","Atreyu"}};

			Console.WriteLine(string.Format("IT3.ListProperty.Count: [{0}] !",IT3.ListProperty.Count));

			/*
			// !!!!! Hodi EXCEPTION, lebo Queue<T> NEMA metodu Add().
			CInitializersTest									IT4=new CInitializersTest(){QueueProperty={"Timmy","Jenny","Atreyu"}};

			Console.WriteLine(string.Format("IT4.QueueProperty.Count: [{0}] !",IT4.QueueProperty.Count));
			*/

			// !!! Vola sa metoda List<T1,T2>.Add(T1,T2).
			CInitializersTest									IT5=new CInitializersTest(){DictionaryProperty={{"Timmy",12},{"Jenny",12},{"Atreyu",13}}};

			Console.WriteLine(string.Format("IT5.DictionaryProperty.Count: [{0}] !",IT5.DictionaryProperty.Count));
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test7()
		{
			var													AT1=new {FirstName="Timmy",LastName="Anderson",Age=12};

			Console.WriteLine(string.Format("AT1.ToString(): [{0}]",AT1.ToString()));
			Console.WriteLine(string.Format("AT1.GetType(): [{0}]",AT1.GetType()));
			Console.WriteLine(string.Format("AT1.GetType(): [{0}]",AT1.GetHashCode()));

			var													AT2=new {FirstName="Jenny",LastName="Thompson",Age=13};

			Console.WriteLine(string.Format("AT2.ToString(): [{0}]",AT2.ToString()));
			Console.WriteLine(string.Format("AT2.GetType(): [{0}]",AT2.GetType()));
			Console.WriteLine(string.Format("AT2.GetType(): [{0}]",AT2.GetHashCode()));

			if (AT1.GetType()==AT2.GetType())
			{
				Console.WriteLine("AT1 and AT2 has SAME TYPE !");
			}
			else
			{
				Console.WriteLine("AT1 and AT2 has DIFFERENT TYPE !");
			}

			var													AT3=new {FirstName="Timmy",LastName="Anderson",Age=12};

			Console.WriteLine(string.Format("AT3.ToString(): [{0}]",AT3.ToString()));
			Console.WriteLine(string.Format("AT3.GetType(): [{0}]",AT3.GetType()));
			Console.WriteLine(string.Format("AT3.GetType(): [{0}]",AT3.GetHashCode()));

			if (AT1.Equals(AT2)==true)
			{
				Console.WriteLine("AT1 and AT2 are EQUAL !");
			}
			else
			{
				Console.WriteLine("AT1 and AT2 are DIFFERENT !");
			}

			if (AT1.Equals(AT3)==true)
			{
				Console.WriteLine("AT1 and AT3 are EQUAL !");
			}
			else
			{
				Console.WriteLine("AT1 and AT3 are DIFFERENT !");
			}

			if (AT1.GetHashCode()==AT2.GetHashCode())
			{
				Console.WriteLine("AT1 and AT2 has SAME HASH CODE !");
			}
			else
			{
				Console.WriteLine("AT1 and AT2 has DIFFERENT HASH CODE !");
			}

			if (AT1.GetHashCode()==AT3.GetHashCode())
			{
				Console.WriteLine("AT1 and AT3 has SAME HASH CODE !");
			}
			else
			{
				Console.WriteLine("AT1 and AT3 has DIFFERENT HASH CODE !");
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test8()
		{
			Tuple<string,string,int>							Name1=new Tuple<string,string,int>("Timmy","Anderson",12);

			Console.WriteLine(string.Format("Name1: [{0}] !",Name1));
			
			// !!! Kompilator si INFERUJE TYPY z PARAMETROV.
			Tuple<string,string,int>							Name2=Tuple.Create("Timmy","Anderson",12);

			Console.WriteLine(string.Format("Name2: [{0}] !",Name2));

			// Teraz typy parametrov definujem explicitne.
			Tuple<string,string,int>							Name3=Tuple.Create<string,string,int>("Timmy","Anderson",12);

			Console.WriteLine(string.Format("Name3: [{0}] !",Name3));

			Tuple<string,string,string,string,string,string,string,Tuple<string,string,string>>	SuperTypeWith10Params=new Tuple<string,string,string,string,string,string,string,Tuple<string,string,string>>("1","2","3","4","5","6","7",Tuple.Create<string,string,string>("8","9","10"));
				
			Console.WriteLine(string.Format("SuperTypeWith10Params: [{0}] !",SuperTypeWith10Params));
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test9()
		{
			// Rozsirovatelny dynamicky objekt.
			dynamic												Name=new ExpandoObject();

			Name.FirstName="Timmy";
			Name.LastName="Anderson";
			Name.Age=12;

			Console.WriteLine(string.Format("Name.GetType(): [{0}] !",Name.GetType()));
			Console.WriteLine(string.Format("Name - FirstName: [{0}], LastName: [{1}], Age: [{2}] !",Name.FirstName,Name.LastName,Name.Age));

			IDictionary<string,object>							KeyValues=(IDictionary<string,object>) Name;

			Console.WriteLine("".PadRight(79,'-'));

			foreach(string PropertyName in KeyValues.Keys)
			{
				Console.WriteLine(string.Format("PROPERTY [{0}] - [{1}] !",PropertyName,KeyValues[PropertyName]));
			}

			Console.WriteLine("".PadRight(79,'-'));

			KeyValues.Remove("Age");

			foreach(string PropertyName in KeyValues.Keys)
			{
				Console.WriteLine(string.Format("PROPERTY [{0}] - [{1}] !",PropertyName,KeyValues[PropertyName]));
			}

			Console.WriteLine("".PadRight(79,'-'));
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
			Test9();

			Console.WriteLine("\nPress any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------