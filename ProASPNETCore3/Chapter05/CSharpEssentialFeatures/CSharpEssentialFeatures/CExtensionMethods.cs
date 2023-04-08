using System;
using System.Collections.Generic;
using System.Text;
//----------------------------------------------------------------------------------------------------------------------
namespace CSharpEssentialFeatures
{
//----------------------------------------------------------------------------------------------------------------------
	// !!! EXTENSION METHODS mozu byt definovane IBA v STATIC CLASSES.
	internal static class CExtensionMethods
	{
//----------------------------------------------------------------------------------------------------------------------
		// !!! EXTENSION METHODS MUSIA byt STATIC METHODS.
		public static string Print(this CClass1 This)
		{
			StringBuilder										SB=new StringBuilder();

			SB.AppendFormat($"VALUE 1 [{This.Value1}] VALUE 2 [{This.Value2}] VALUE 3 [VALUE 1 [{This.Value3.Value1}] VALUE 2 [{This.Value3.Value2}]]");

			return(SB.ToString());
		}
//----------------------------------------------------------------------------------------------------------------------
		// !!! EXTENSION METHOD moze byt aplikovana aj na INTERFACE.
		public static string Print(this IEnumerable<string> This)
		{
			StringBuilder										SB=new StringBuilder();
			bool												AddSeparator=false;

			foreach(string Value in This)
			{
				if (AddSeparator==false)
				{
					AddSeparator=true;
				}
				else
				{
					SB.Append(" ");
				}

				SB.AppendFormat($"[{Value}]");
			}

			return(SB.ToString());
		}
//----------------------------------------------------------------------------------------------------------------------
		// !!! EXTENSION METHOD moze byt aplikovana ako LINQ EXPRESSION.
		public static IEnumerable<int> Filter(this IEnumerable<int> This, int ValueToCompare)
		{
			foreach(int Value in This)
			{
				if (Value<ValueToCompare)
				{
					yield return(Value);
				}
			}
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------