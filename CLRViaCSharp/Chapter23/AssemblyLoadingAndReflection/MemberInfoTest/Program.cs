using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Reflection;
using Microsoft.CSharp.RuntimeBinder;
//-------------------------------------------------------------------------------------------------------
namespace MemberInfoTest
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		private static void Show(int Indent, string Format, params Object[] Args)
		{
			Console.WriteLine(new string(' ',3*Indent)+Format,Args);
		}
//-------------------------------------------------------------------------------------------------------
		private static bool TypeFilter(Type T, object FilterCriteria)
		{
			return(true);
		}
//-------------------------------------------------------------------------------------------------------
		private static void EventHandler1(string Value)
		{
			Console.WriteLine(string.Format("EventHandler1() CALLED with VALUE [{0}] !",Value));
		}
//-------------------------------------------------------------------------------------------------------
		private static void EventHandler2(string Value)
		{
			Console.WriteLine(string.Format("EventHandler2() CALLED with VALUE [{0}] !",Value));
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		private static void Test1()
		{
			CName												Name=new CName("Timmy","Anderson",12);
			Type												T=Name.GetType();

			foreach(MemberInfo MI in T.GetMethods())
			{
				Console.WriteLine(string.Format("MemberInfo: [{0}], DeclaringType: [{1}], ReflectedType: [{2}] !",MI.Name,MI.DeclaringType,MI.ReflectedType));
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test2()
		{
			CName												Name=new CName("Timmy","Anderson",12);
			Type												T=Name.GetType();
			// !!!!! Konvertuje Type na TypeInfo.
			TypeInfo											TI=T.GetTypeInfo();

			foreach(MemberInfo MI in TI.GetMethods())
			{
				Console.WriteLine(string.Format("MemberInfo: [{0}], DeclaringType: [{1}], ReflectedType: [{2}] !",MI.Name,MI.DeclaringType,MI.ReflectedType));
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test3()
		{
			Assembly[]											Assemblies=AppDomain.CurrentDomain.GetAssemblies();

			foreach (Assembly A in Assemblies)
			{
				Show(0,"ASSEMBLY: [{0}] !",A);

				foreach(Type T in A.GetExportedTypes())
				{
					Show(1,"TYPE: [{0}] !",T);

					const BindingFlags							BF=BindingFlags.DeclaredOnly | BindingFlags.NonPublic | BindingFlags.Public | BindingFlags.Instance | BindingFlags.Static;

					foreach (MemberInfo MI in T.GetMembers(BF))
					{
						string									TypeName=string.Empty;

						if ((MI is Type)==true)
						{
							TypeName="(NESTED) TYPE";
						}

						if ((MI is FieldInfo)==true)
						{
							TypeName="FIELD INFO";
						}

						if ((MI is MethodInfo)==true)
						{
							TypeName="METHOD INFO";
						}

						if ((MI is ConstructorInfo)==true)
						{
							TypeName="CONSTRUCTOR INFO";
						}

						if ((MI is PropertyInfo)==true)
						{
							TypeName="PROPERTY INFO";
						}

						if ((MI is EventInfo)==true)
						{
							TypeName="EVENT INFO";
						}

						Show(2,"[{0}]: [{1}] !",TypeName,MI);
					}
				}
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test4()
		{
			Assembly[]											Assemblies=AppDomain.CurrentDomain.GetAssemblies();

			foreach (Assembly A in Assemblies)
			{
				Show(0,"ASSEMBLY: [{0}] !",A);

				// !!! Konvertuje sa Type na TypeInfo.
				foreach(TypeInfo TI in A.GetExportedTypes().Select(P => P.GetTypeInfo()))
				{
					Show(1,"TYPE: [{0}] !",TI);

					const BindingFlags							BF=BindingFlags.DeclaredOnly | BindingFlags.NonPublic | BindingFlags.Public | BindingFlags.Instance | BindingFlags.Static;

					foreach (MemberInfo MI in TI.GetMembers(BF))
					{
						string									TypeName=string.Empty;

						if ((MI is Type)==true)
						{
							TypeName="(NESTED) TYPE";
						}

						if ((MI is FieldInfo)==true)
						{
							TypeName="FIELD INFO";
						}

						if ((MI is MethodInfo)==true)
						{
							TypeName="METHOD INFO";
						}

						if ((MI is ConstructorInfo)==true)
						{
							TypeName="CONSTRUCTOR INFO";
						}

						if ((MI is PropertyInfo)==true)
						{
							TypeName="PROPERTY INFO";
						}

						if ((MI is EventInfo)==true)
						{
							TypeName="EVENT INFO";
						}

						Show(2,"[{0}]: [{1}] !",TypeName,MI);
					}
				}
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test5()
		{
			CTestClass											TestClass=new CTestClass("Timmy","Anderson",12);
			Type												T=TestClass.GetType();
			// !!!!! Konvertuje Type na TypeInfo.
			TypeInfo											TI=T.GetTypeInfo();
			// !!! Spatna konverzia TypeInfo na Type.
			Type												ConvertedType=TI.AsType();

			foreach(MemberInfo MI in ConvertedType.GetMethods())
			{
				Console.WriteLine(string.Format("MemberInfo: [{0}], DeclaringType: [{1}], ReflectedType: [{2}] !",MI.Name,MI.DeclaringType,MI.ReflectedType));
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test6()
		{
			Type												T=typeof(CMyRetailer);
			Type[]												Interfaces=T.FindInterfaces(TypeFilter,null);

			Console.WriteLine("CMyRetailer IMPLEMENTS following INTERFACES (defined in this ASSEMBLY):");

			foreach(Type Interface in Interfaces)
			{
				Console.WriteLine(string.Format("\nINTERFACE: [{0}] !",Interface));

				// Ziskam InterfaceMapping.
				InterfaceMapping								Map=T.GetInterfaceMap(Interface);

				for (int Index=0;Index<Map.InterfaceMethods.Length;Index++)
				{
					Console.WriteLine(string.Format("\t[{0}] is implemented by [{1}] !",Map.InterfaceMethods[Index],Map.TargetMethods[Index]));
				}
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test7()
		{
			Type												T=typeof(CMyRetailer);
			TypeInfo											TI=T.GetTypeInfo();
			Type[]												Interfaces=TI.ImplementedInterfaces.ToArray();

			Console.WriteLine("CMyRetailer IMPLEMENTS following INTERFACES (defined in this ASSEMBLY):");

			foreach(Type Interface in Interfaces)
			{
				Console.WriteLine(string.Format("\nINTERFACE: [{0}] !",Interface));

				// Ziskam InterfaceMapping.
				InterfaceMapping								Map=T.GetInterfaceMap(Interface);

				for (int Index=0;Index<Map.InterfaceMethods.Length;Index++)
				{
					Console.WriteLine(string.Format("\t[{0}] is implemented by [{1}] !",Map.InterfaceMethods[Index],Map.TargetMethods[Index]));
				}
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test8()
		{
			Type												TestClassType=typeof(CTestClass);
			// !!! CLASS TypeInfo DERIVED z CLASS Type ma dodatocne METHODS, ktore zjednodusuju pristup k MEMBERS.
			TypeInfo											TestClassTypeInfo=TestClassType.GetTypeInfo();

			// Vracia PRIVATE a PUBLIC FIELDS.
			FieldInfo[]											TestClassFieldInfos=TestClassTypeInfo.DeclaredFields.ToArray();
			// Vracia PRIVATE a PUBLIC METHODS. Vracia aj GETTER a SETTER METHODS ci ADD a REMOVE EVENT METHODS.
			MethodInfo[]										TestClassMethodInfos=TestClassTypeInfo.DeclaredMethods.ToArray();
			// Vracia PRIVATE a PUBLIC CONSTRUCTORS.
			ConstructorInfo[]									TestClassConstructorInfos=TestClassTypeInfo.DeclaredConstructors.ToArray();
			// Vracia PRIVATE a PUBLIC EVENTS.
			EventInfo[]											TestClassEventInfos=TestClassTypeInfo.DeclaredEvents.ToArray();
			// Vracia PRIVATE a PUBLIC PROPERTIES.
			PropertyInfo[]										TestClassPropertyInfos=TestClassTypeInfo.DeclaredProperties.ToArray();
			// Vracia PRIVATE a PUBLIC PROPERTIES.
			TypeInfo[]											TestClassNestedClassInfos=TestClassTypeInfo.DeclaredNestedTypes.ToArray();

			Console.WriteLine("-------------------------------------------------------------------------------");

			foreach(FieldInfo TestClassFieldInfo in TestClassFieldInfos)
			{
				Console.WriteLine(string.Format("FIELD [{0}] !",TestClassFieldInfo.Name));
			}

			Console.WriteLine("-------------------------------------------------------------------------------");

			foreach(MethodInfo TestClassMethodInfo in TestClassMethodInfos)
			{
				Console.WriteLine(string.Format("METHOD [{0}] !",TestClassMethodInfo.Name));
			}

			Console.WriteLine("-------------------------------------------------------------------------------");

			foreach(ConstructorInfo TestClassConstructorInfo in TestClassConstructorInfos)
			{
				Console.WriteLine(string.Format("CONSTRUCTOR [{0}] !",TestClassConstructorInfo.Name));
			}

			Console.WriteLine("-------------------------------------------------------------------------------");

			foreach(EventInfo TestClassEventInfo in TestClassEventInfos)
			{
				Console.WriteLine(string.Format("EVENT [{0}] !",TestClassEventInfo.Name));
			}

			Console.WriteLine("-------------------------------------------------------------------------------");

			foreach(PropertyInfo TestClassPropertyInfo in TestClassPropertyInfos)
			{
				Console.WriteLine(string.Format("PROPERTY [{0}] !",TestClassPropertyInfo.Name));
			}

			Console.WriteLine("-------------------------------------------------------------------------------");

			foreach(TypeInfo TestClassNestedClassInfo in TestClassNestedClassInfos)
			{
				Console.WriteLine(string.Format("NESTED CLASS [{0}] !",TestClassNestedClassInfo.Name));
			}

			Console.WriteLine("-------------------------------------------------------------------------------");
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test9()
		{
			Type												TestClassType=typeof(CTestClass);
			// !!! CLASS TypeInfo DERIVED z CLASS Type ma dodatocne METHODS, ktore zjednodusuju pristup k MEMBERS.
			TypeInfo											TestClassTypeInfo=TestClassType.GetTypeInfo();
			
			// Vracia PUBLIC FIELD podla NAME.
			FieldInfo											TestClassFieldInfo=TestClassTypeInfo.GetDeclaredField("MField");
			// Vracia PUBLIC METHOD podla NAME.
			MethodInfo											TestClassMethodInfo=TestClassTypeInfo.GetDeclaredMethod("PrintField");
			// Vracia PUBLIC EVENT podla NAME.
			EventInfo											TestClassEventInfo=TestClassTypeInfo.GetDeclaredEvent("MEvent");
			// Vracia PUBLIC PROPERTY podla NAME.
			PropertyInfo										TestClassPropertyInfo=TestClassTypeInfo.GetDeclaredProperty("Field");
			// Vracia PUBLIC NESTED CLASS podla NAME.
			TypeInfo											TestClassNestedClassInfo=TestClassTypeInfo.GetDeclaredNestedType("CPublicNestedType");

			// !!! Vyvolanim CONSTRUCTOR sa vytvori instancia CLASS.
			CTestClass											TestClass=(CTestClass) TestClassTypeInfo.InvokeMember(null,BindingFlags.CreateInstance,null,null,new object[]{"XXX","Timmy Anderson",12},null);

			Console.WriteLine("-------------------------------------------------------------------------------");
			
			Console.WriteLine(string.Format("TestClass.MField [{0}] !",TestClassFieldInfo.GetValue(TestClass)));

			TestClassFieldInfo.SetValue(TestClass,"YYY");

			Console.WriteLine(string.Format("TestClass.MField [{0}] !",TestClass.MField));

			Console.WriteLine("-------------------------------------------------------------------------------");

			// Vyvolanie METHOD cez MethodInfo.Invoke().
			TestClassMethodInfo.Invoke(TestClass,new object[0]);
			
			// Vyvolanie METHOD cez Type.InvokeMember().
			TestClassTypeInfo.InvokeMember("PrintField",BindingFlags.InvokeMethod | BindingFlags.Public | BindingFlags.Instance,null,TestClass,new object[0]);

			// Vyvolanie PRIVATE METHOD cez Type.InvokeMember().
			TestClassTypeInfo.InvokeMember("PrivateMethod",BindingFlags.InvokeMethod | BindingFlags.NonPublic | BindingFlags.Instance,null,TestClass,new object[0]);

			Console.WriteLine("-------------------------------------------------------------------------------");

			Console.WriteLine(string.Format("TestClassNestedClassInfo [{0}] !",TestClassNestedClassInfo.Name));

			Console.WriteLine("-------------------------------------------------------------------------------");

			Delegate											Delegate1=new Action<string>(EventHandler1);
			Delegate											Delegate2=new Action<string>(EventHandler2);

			TestClassEventInfo.AddEventHandler(TestClass,Delegate1);
			TestClassEventInfo.AddEventHandler(TestClass,Delegate2);
			
			// Vyvola sa EVENT.
			TestClass.RunEvent();

			Console.WriteLine("-------------------------------------------------------------------------------");

			TestClassEventInfo.RemoveEventHandler(TestClass,Delegate1);

			// Vyvola sa EVENT.
			TestClass.RunEvent();

			Console.WriteLine("-------------------------------------------------------------------------------");

			TestClassTypeInfo.InvokeMember("add_MEvent",BindingFlags.InvokeMethod | BindingFlags.Instance | BindingFlags.Public,null,TestClass,new object[]{Delegate1});

			// Vyvola sa EVENT.
			TestClass.RunEvent();

			Console.WriteLine("-------------------------------------------------------------------------------");

			TestClassTypeInfo.InvokeMember("remove_MEvent",BindingFlags.InvokeMethod | BindingFlags.Instance | BindingFlags.Public,null,TestClass,new object[]{Delegate1});

			// Vyvola sa EVENT.
			TestClass.RunEvent();

			Console.WriteLine("-------------------------------------------------------------------------------");

			// !!! Vola sa PROPERTY SETTER METHOD.
			TestClassTypeInfo.InvokeMember("set_Field",BindingFlags.InvokeMethod | BindingFlags.Instance | BindingFlags.Public,null,TestClass,new object[]{"ZZZ"});

			Console.WriteLine(string.Format("Field [{0}] !",TestClass.Field));

			Console.WriteLine("-------------------------------------------------------------------------------");
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test10()
		{
			Type												T=typeof(CName);

			Console.WriteLine("-------------------------------------------------------------------------------");

			// Dynamicky sa vytvori instancia objektu cez DEFAULT BINDER.
			CName												Name1=(CName) T.InvokeMember(null,BindingFlags.CreateInstance,null,null,new object[]{"Timmy","Anderson",12},null);

			Console.WriteLine(string.Format("NAME - DEFAULT BINDER: [{0}] !",Name1));

			Console.WriteLine("-------------------------------------------------------------------------------");

			CMySimpleBinder										CustomBinder=new CMySimpleBinder();

			// Pomocou PARAMETER BindingFlags.CreateInstance sa vytvori NOVA INSTANCIA OBJECT.
			CName												Name2=(CName) T.InvokeMember(null,BindingFlags.CreateInstance,CustomBinder,null,new object[]{"Timmy","Anderson",12},null);

			Console.WriteLine("-------------------------------------------------------------------------------");

			Console.WriteLine(string.Format("NAME - CUSTOM BINDER: [{0}] !",Name2));

			Console.WriteLine("-------------------------------------------------------------------------------");

			// Dynamicky sa vyvola metodu PrintName() BEZ PARAMETRS cez CUSTOM BINDER.
			T.InvokeMember("PrintName",BindingFlags.InvokeMethod | BindingFlags.Instance | BindingFlags.Public,CustomBinder,Name2,new object[0],null,null,null);

			Console.WriteLine("-------------------------------------------------------------------------------");

			// Dynamicky sa vyvola metodu PrintName() s 1 PARAMETR cez CUSTOM BINDER.
			T.InvokeMember("PrintName",BindingFlags.InvokeMethod | BindingFlags.Instance | BindingFlags.Public,CustomBinder,Name2,new object[]{"HELLO"},null,null,null);

			Console.WriteLine("-------------------------------------------------------------------------------");
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test11()
		{
			Type												T=typeof(CName);
			CName												Name=new CName("Timmy","Anderson",12);

			// Rucne sa NAJPRV spravi BINDING.
			MethodInfo											MI=T.GetMethod("ToString");

			// !!! A teraz sa spravi INVOKING BEZ BINING, ktory je mozne opakovat viackrat bez opakovaneho vykonania casovo narocneho BINDING.
			string												Text=(string) MI.Invoke(Name,new object[0]);
			
			Console.WriteLine(string.Format("Name: [{0}] !",Text));
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test12()
		{
			dynamic												Name=new CName("Timmy","Anderson",12);

			// Robi sa BINDING aj INVOKING
			string												Text=(string) Name.ToString();
			
			Console.WriteLine(string.Format("NAME: [{0}] !",Text));

			// !!! Teraz je uz INVOKING OPTIMALIZOVANY, pretoze DEFAULT BINDER ulozi vysledok BINDING do CACHE a NEVYKONAVA opatovny BIDNING, ale rovno spravi INVOKING.
			Text=(string) Name.ToString();

			Console.WriteLine(string.Format("NAME: [{0}] !",Text));
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test13()
		{
			Type												T=typeof(CName);
			CName												Name=new CName("Timmy","Anderson",12);
			FieldInfo											FI=T.GetField("MFirstName",BindingFlags.Instance | BindingFlags.NonPublic);

			// Konveruje sa FieldInfo na RuntimeFieldHandle.
			RuntimeFieldHandle									RFH=FI.FieldHandle;

			// Konveruje sa RuntimeFieldHandle na MethodBase.
			FieldInfo											MB=FieldInfo.GetFieldFromHandle(RFH);

			string												Text=(string) MB.GetValue(Name);

			Console.WriteLine(string.Format("Name: [{0}] !",Text));
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test14()
		{
			Type												T=typeof(CName);
			CName												Name=new CName("Timmy","Anderson",12);
			MethodInfo											MI=T.GetMethod("ToString");

			// Konveruje sa MethodInfo na RuntimeMethodHandle.
			RuntimeMethodHandle									RMH=MI.MethodHandle;

			// Konveruje sa RuntimeMethodHandle na MethodBase.
			MethodBase											MB=MethodInfo.GetMethodFromHandle(RMH);

			string												Text=(string) MB.Invoke(Name,new object[0]);

			Console.WriteLine(string.Format("Name: [{0}] !",Text));
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test15()
		{
			CName												Name=new CName("Timmy","Anderson",12);
			
			// Konveruje sa Type na RuntimeTypeHandle.
			RuntimeTypeHandle									RTH=Type.GetTypeHandle(Name);

			// Konveruje sa RuntimeTypeHandle na Type.
			Type												TB=Type.GetTypeFromHandle(RTH);

			string												Text=(string) TB.InvokeMember("ToString",BindingFlags.InvokeMethod | BindingFlags.Public | BindingFlags.Instance,null,Name,new object[0]);

			Console.WriteLine(string.Format("Name: [{0}] !",Text));
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