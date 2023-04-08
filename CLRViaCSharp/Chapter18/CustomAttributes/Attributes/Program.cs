using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Reflection;
//-------------------------------------------------------------------------------------------------------
namespace Attributes
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		private static void Test1()
		{
			Type												T=typeof(CSimpleClass);
			object[]											ClassAttributes=T.GetCustomAttributes(false);

			Console.WriteLine("CLASS ATTRIBUTES:");

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
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test2()
		{
			TypeInfo 											GenericType=typeof(CGenericType<>).GetTypeInfo();
			Type[]												GenericArguments=GenericType.GenericTypeParameters;

			foreach(Type GenericArgument in GenericArguments)
			{
				Attribute[]										GenericArgumentCustomAttributes=GenericArgument.GetCustomAttributes().ToArray();

				foreach(Attribute GenericArgumentCustomAttribute in GenericArgumentCustomAttributes)
				{
					Console.WriteLine(string.Format("GENERIC ARGUMENT [{0}] - ATTRIBUTE [{1}] !",GenericArgument,GenericArgumentCustomAttribute));
				}
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test3()
		{
			TypeInfo 											ClassType=typeof(CClass).GetTypeInfo();
			MethodInfo											Method=ClassType.GetMethod("SomeMethod",BindingFlags.Public | BindingFlags.Instance);
			object[]											ReturnValueCustomAttributes=Method.ReturnTypeCustomAttributes.GetCustomAttributes(true);

			foreach(object ReturnValueCustomAttribute in ReturnValueCustomAttributes)
			{
				Console.WriteLine(string.Format("RETURN VALUE ATTRIBUTE [{0}] !",ReturnValueCustomAttributes));
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test4()
		{
			TypeInfo 											ClassType=typeof(CClass).GetTypeInfo();
			EventInfo 											Event=ClassType.GetEvent("SomeEvent",BindingFlags.Public | BindingFlags.Instance);

			MethodInfo											EventAddMethod=Event.GetAddMethod();
			MethodInfo											EventRemoveMethod=Event.GetAddMethod();

			Attribute[]											EventAddMethodAttributes=EventAddMethod.GetCustomAttributes().ToArray();
			Attribute[]											EventRemoveMethodAttributes=EventRemoveMethod.GetCustomAttributes().ToArray();

			foreach(Attribute EventAddMethodAttribute in EventAddMethodAttributes)
			{
				Console.WriteLine(string.Format("ADD METHOD ATTRIBUTE [{0}] !",EventAddMethodAttribute));
			}

			foreach(Attribute EventRemoveMethodAttribute in EventRemoveMethodAttributes)
			{
				Console.WriteLine(string.Format("REMOVE METHOD ATTRIBUTE [{0}] !",EventRemoveMethodAttribute));
			}

			FieldInfo[]											Fields=ClassType.GetFields(BindingFlags.Instance | BindingFlags.NonPublic);

			foreach(FieldInfo Field in Fields)
			{
				// Najde sa skryty EVENT FIELD.
				if (Field.FieldType==typeof(EventHandler))
				{
					Attribute[]									EventFieldAttributes=Field.GetCustomAttributes().ToArray();

					foreach(Attribute EventFieldAttribute in EventFieldAttributes)
					{
						Console.WriteLine(string.Format("EVENT FIELD ATTRIBUTE [{0}] !",EventFieldAttributes));
					}
				}
			}

			Attribute[]											EventAttributes=Event.GetCustomAttributes().ToArray();

			foreach(Attribute EventAttribute in EventAttributes)
			{
				Console.WriteLine(string.Format("EVENT ATTRIBUTE [{0}] !",EventAttribute));
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
			Test4();

			Console.WriteLine("\nPress any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------