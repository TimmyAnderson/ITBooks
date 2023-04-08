using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace ExtensionMethods
{
//-------------------------------------------------------------------------------------------------------
	public static class CExtensions
	{
//-------------------------------------------------------------------------------------------------------
		public static void EXT_Class(this CClass Value)
		{
			Console.WriteLine(string.Format("EXT_Class(): [{0}] !",Value));
		}
//-------------------------------------------------------------------------------------------------------
		public static void EXT_Interface(this IInterface Value)
		{
			Console.WriteLine(string.Format("EXT_Interface(): [{0}] !",Value));
		}
//-------------------------------------------------------------------------------------------------------
		public static void EXT_Enum(this EEnum Value)
		{
			Console.WriteLine(string.Format("EXT_Enum(): [{0}] !",Value));
		}
//-------------------------------------------------------------------------------------------------------
		public static void EXT_Struct(this SStruct Value)
		{
			Console.WriteLine(string.Format("EXT_Struct(): [{0}] !",Value));
		}
//-------------------------------------------------------------------------------------------------------
		public static void EXT_Delegate(this DDelegate Value)
		{
			Console.WriteLine(string.Format("EXT_Delegate(): [{0}] !",Value));
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------