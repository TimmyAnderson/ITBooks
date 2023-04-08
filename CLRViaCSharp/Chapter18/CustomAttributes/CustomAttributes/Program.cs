using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Reflection;
//-------------------------------------------------------------------------------------------------------
namespace CustomAttributes
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		private static void Test1()
		{
			Type												T=typeof(CSimpleClass);
			object[]											ClassAttributes=T.GetCustomAttributes(false);

			Console.WriteLine(string.Format("{0} CLASS ATTRIBUTES:",T));

			foreach(object CA in ClassAttributes)
			{
				Console.WriteLine(string.Format("\t{0} !",CA));
			}

			Console.WriteLine();
			Console.WriteLine("METHOD ATTRIBUTES:");

			MethodInfo											MI=T.GetMethod("ToUpper",BindingFlags.Public | BindingFlags.Instance);
			object[]											MethodAttributes=MI.GetCustomAttributes(false);

			foreach(object MA in MethodAttributes)
			{
				Console.WriteLine(string.Format("\t{0} !",MA));
			}

			ParameterInfo										PI=MI.GetParameters()[0];

			Console.WriteLine();
			Console.WriteLine("PARAMETER ATTRIBUTES:");

			object[]											ParameterAttributes=PI.GetCustomAttributes(false);

			foreach(object PA in ParameterAttributes)
			{
				Console.WriteLine(string.Format("\t{0} !",PA));
			}

			ParameterInfo										RPI=MI.ReturnParameter;

			Console.WriteLine();
			Console.WriteLine("RETURN ATTRIBUTES:");

			object[]											ReturnAttributes=RPI.GetCustomAttributes(false);

			foreach(object RA in ReturnAttributes)
			{
				Console.WriteLine(string.Format("\t{0} !",RA));
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test2()
		{
			Type												T=typeof(CDerivedClass);
			// Chcem aj DERIVED ATTRIBUTES.
			object[]											ClassAttributes=T.GetCustomAttributes(true);

			Console.WriteLine(string.Format("{0} CLASS ATTRIBUTES:",T));

			foreach(object CA in ClassAttributes)
			{
				Console.WriteLine(string.Format("\t{0} !",CA));
			}

			Console.WriteLine();
			Console.WriteLine("METHOD ToUpper() ATTRIBUTES:");

			MethodInfo											MI=T.GetMethod("ToUpper",BindingFlags.Public | BindingFlags.Instance);
			object[]											MethodAttributes=MI.GetCustomAttributes(false);

			foreach(object MA in MethodAttributes)
			{
				Console.WriteLine(string.Format("\t{0} !",MA));
			}

			Console.WriteLine();
			Console.WriteLine("METHOD VirtualMethod1() ATTRIBUTES:");

			MethodInfo											MI1=T.GetMethod("VirtualMethod1",BindingFlags.Public | BindingFlags.Instance);
			object[]											MethodAttributes1=MI1.GetCustomAttributes(true);

			foreach(object MA in MethodAttributes1)
			{
				Console.WriteLine(string.Format("\t{0} !",MA));
			}

			Console.WriteLine();
			Console.WriteLine("METHOD VirtualMethod2() ATTRIBUTES:");

			MethodInfo											MI2=T.GetMethod("VirtualMethod2",BindingFlags.Public | BindingFlags.Instance);
			object[]											MethodAttributes2=MI2.GetCustomAttributes(true);

			foreach(object MA in MethodAttributes2)
			{
				Console.WriteLine(string.Format("\t{0} !",MA));
			}

			ParameterInfo										PI=MI.GetParameters()[0];

			Console.WriteLine();
			Console.WriteLine("PARAMETER ATTRIBUTES:");

			object[]											ParameterAttributes=PI.GetCustomAttributes(false);

			foreach(object PA in ParameterAttributes)
			{
				Console.WriteLine(string.Format("\t{0} !",PA));
			}

			ParameterInfo										RPI=MI.ReturnParameter;

			Console.WriteLine();
			Console.WriteLine("RETURN ATTRIBUTES:");

			object[]											ReturnAttributes=RPI.GetCustomAttributes(false);

			foreach(object RA in ReturnAttributes)
			{
				Console.WriteLine(string.Format("\t{0} !",RA));
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test3()
		{
			Type												T=typeof(CSimpleClass);
			MethodInfo											MI1=T.GetMethod("ToUpper",BindingFlags.Public | BindingFlags.Instance);
			MethodInfo											MI2=T.GetMethod("DoNothing",BindingFlags.Public | BindingFlags.Instance);
			ParameterInfo										PI=MI1.GetParameters()[0];
			ParameterInfo										RPI=MI1.ReturnParameter;

			// !!! NESPOSOBUJE DESERIALIZATION daneho ATTRIBUTE ani volanie jeho CONSTRUCTOR.
			bool												IsDefinedMI1=Attribute.IsDefined(MI1,typeof(CMySuperAttribute));
			// !!! Na DoNothing() bol aplikovany ATTRIBUTE [CMyDerivedSuperAttribute], ktory je ZDEDENY z CMySuperAttribute.
			// !!!!! Vrati TRUE, lebo i DERIVED ATTRIBUTES povazuje za aplikovanie BASE ATTRIBUTE.
			bool												IsDefinedMI2=Attribute.IsDefined(MI2,typeof(CMySuperAttribute));
			bool												IsDefinedMI3=Attribute.IsDefined(MI2,typeof(CMyDerivedSuperAttribute));

			Console.WriteLine(string.Format("IsDefinedMI1: [{0}] !",IsDefinedMI1));
			Console.WriteLine(string.Format("IsDefinedMI2: [{0}] !",IsDefinedMI2));
			Console.WriteLine(string.Format("IsDefinedMI3: [{0}] !",IsDefinedMI3));

			Console.WriteLine();
			Console.WriteLine("RETURN ATTRIBUTES:");

			// !!! SPOSOBUJE DESERIALIZATION daneho ATTRIBUTE a volanie jeho CONSTRUCTOR.
			// METHOD vracia aj vsetky vyskyty TOHO ISTEHO ATTRIBUTE, ak ten isty ATTRIBUTE moze byt VIACKRAT aplikovany na RETURN VALUE.
			Attribute[]											ReturnAttributes=Attribute.GetCustomAttributes(RPI);

			foreach(object ReturnAttribute in ReturnAttributes)
			{
				Console.WriteLine(string.Format("\t{0} !",ReturnAttribute));
			}

			// !!! SPOSOBUJE DESERIALIZATION daneho ATTRIBUTE a volanie jeho CONSTRUCTOR.
			// Ak by bol TEN ISTY ATTRIBUE aplikovany VIACKRAT, METHOD by hodila EXCEPTION.
			Attribute											PA=Attribute.GetCustomAttribute(PI,typeof(CMySuperAttribute));

			Console.WriteLine();
			Console.WriteLine(string.Format("Parameter ATTRIBUTE: [{0}] !",PA));
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test4()
		{
			Type												T=typeof(CSimpleClass);
			CMySuperAttribute									Attribute1=new CMySuperAttribute("Anderson");
			CMySuperAttribute									Attribute2=new CMySuperAttribute("Anderson");

			Attribute2.FirstName="Timmy";

			Attribute											AttributeToCompare=Attribute.GetCustomAttribute(T,typeof(CMySuperAttribute));

			Console.WriteLine(string.Format("Attribute1.Equals() [{0}] !",Attribute1.Equals(AttributeToCompare)));
			Console.WriteLine(string.Format("Attribute2.Equals() [{0}] !",Attribute2.Equals(AttributeToCompare)));
			Console.WriteLine(string.Format("Attribute1.Match() [{0}] !",Attribute1.Match(AttributeToCompare)));
			Console.WriteLine(string.Format("Attribute2.Match() [{0}] !",Attribute2.Match(AttributeToCompare)));
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test5()
		{
			Type												T=typeof(CSimpleClass);
			MethodInfo											MI=T.GetMethod("ToUpper",BindingFlags.Public | BindingFlags.Instance);
			ParameterInfo										PI=MI.GetParameters()[0];

			// Instancie ATTRIBUTES sa NEVYTVARAJU sa NEVOLA sa ani ZIADEN CODE ich CONSTRUCTORS ci STATIC CONSTRUCTORS.
			IList<CustomAttributeData>							CADCollection=CustomAttributeData.GetCustomAttributes(PI);

			foreach(CustomAttributeData CAD in CADCollection)
			{
				Console.WriteLine(string.Format("ATTRIBUTE: [{0}] !",CAD.AttributeType));

				Console.WriteLine(string.Format("CONSTRUCTOR: [{0}] !",CAD.Constructor));

				foreach(CustomAttributeTypedArgument CATA in CAD.ConstructorArguments)
				{
					Console.WriteLine(string.Format("CONSTRUCTOR ARGUMENT: [{0}]:[{1}] !",CATA.ArgumentType,CATA.Value));
				}

				foreach(CustomAttributeNamedArgument CANA in CAD.NamedArguments)
				{
					Console.WriteLine(string.Format("NAMED ARGUMENT: [{0}]:[{1}] !",CANA.MemberInfo,CANA.TypedValue));
				}
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test6()
		{
			Type												T=typeof(CSomeClass);

			// !!! HODNOTA ZAVISI od toho ci je to DEBUG BUILD, alebo RELEASE BUILD.
			bool												IsDefined=Attribute.IsDefined(T,typeof(CConditionalAttribute));

			Console.WriteLine(string.Format("IsDefined: [{0}] !",IsDefined));
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
			Test6();

			Console.WriteLine("\nPress any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------