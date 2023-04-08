using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Reflection;
using System.Runtime.Remoting;
//-------------------------------------------------------------------------------------------------------
namespace ObjectCreation
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		private static void DelegateMethod()
		{
			Console.WriteLine("DelegateMethod() CALLED !");
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		private static void Test1()
		{
			// Vytvorenie CLASS.
			CName												Name=(CName) Activator.CreateInstance(typeof(CName),"Timmy","Anderson",12);

			Console.WriteLine(string.Format("Name: [{0}] !",Name));
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test2()
		{
			// Vytvorenie STRUCT.
			CNameStruct											Name=(CNameStruct) Activator.CreateInstance(typeof(CNameStruct),"Timmy","Anderson",12);

			Console.WriteLine(string.Format("Name: [{0}] !",Name));
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test3()
		{
			// Vytvorenie STRUCT.
			CNameStructNoConstructor							Name=(CNameStructNoConstructor) Activator.CreateInstance(typeof(CNameStructNoConstructor));

			Name.FirstName="Timmy";
			Name.LastName="Anderson";
			Name.Age=12;

			Console.WriteLine(string.Format("Name: [{0}] !",Name));
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test4()
		{
			// Vytvorim OBJECT HANDLE, ktory je treba rozbalit pomocou metody Unwrap() do APP DOMAIN.
			ObjectHandle										OH=AppDomain.CurrentDomain.CreateInstance("ObjectCreation","ObjectCreation.CName",false,BindingFlags.InvokeMethod,null,new object[]{"Timmy","Anderson",12},null,null);

			// Rozbalim ObjectHandle do APP DOMAIN.
			CName												Name=(CName) OH.Unwrap();

			Console.WriteLine(string.Format("Name: [{0}] !",Name));
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test5()
		{
			CName												Name=(CName) AppDomain.CurrentDomain.CreateInstanceAndUnwrap("ObjectCreation","ObjectCreation.CName",false,BindingFlags.InvokeMethod,null,new object[]{"Timmy","Anderson",12},null,null);

			Console.WriteLine(string.Format("Name: [{0}] !",Name));
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test6()
		{
			Type												T=typeof(CName);
			CName												Name=(CName) T.InvokeMember(null,BindingFlags.CreateInstance,null,null,new object[]{"Timmy","Anderson",12},null);

			Console.WriteLine(string.Format("Name: [{0}] !",Name));
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test7()
		{
			Type												T=typeof(CName);
			ConstructorInfo										CI=T.GetConstructor(new Type[]{typeof(string),typeof(string),typeof(int)});
			CName												Name=(CName) CI.Invoke(new object[]{"Timmy","Anderson",12});

			Console.WriteLine(string.Format("Name: [{0}] !",Name));
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test8()
		{
			// Vytvorenie ARRAY.
			CName[]												Names=(CName[]) Array.CreateInstance(typeof(CName),10);

			Console.WriteLine(string.Format("Name.Length: [{0}] !",Names.Length));
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test9()
		{
			// Vytvorenie ARRAY.
			CName[,]											Names=(CName[,]) Array.CreateInstance(typeof(CName),10,20);
			
			Console.WriteLine(string.Format("Name.Length_1: [{0}], Name.Length_2: [{1}], Name.Length: [{2}] !",Names.GetLength(0),Names.GetLength(1),Names.Length));
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test10()
		{
			MethodInfo											MI=typeof(Program).GetMethod("DelegateMethod",BindingFlags.Static | BindingFlags.NonPublic);
			Action												A=(Action) Delegate.CreateDelegate(typeof(Action),MI);

			A();
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test11()
		{
			// Vytvorim CLOSED TYPE.
			Type												OpenedType=typeof(List<>);
			// Z neho pomocou MakeGenericType() vytvorim OPENED TYPE.
			Type												ClosedType=OpenedType.MakeGenericType(typeof(string));
			List<string>										ListString=(List<string>) ClosedType.InvokeMember(null,BindingFlags.CreateInstance,null,null,null,null);

			Console.WriteLine(string.Format("ListString: [{0}], ListString.Count: [{1}] !",ListString,ListString.Count));
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
			Test11();

			Console.WriteLine("\nPress any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------