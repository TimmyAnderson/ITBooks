using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Reflection;
using System.Windows;
using System.Windows.Markup;
//-----------------------------------------------------------------------------------------------------------------
namespace DumpContentPropertyAttributes
{
//-----------------------------------------------------------------------------------------------------------------
	class Program
	{
//-----------------------------------------------------------------------------------------------------------------
		[STAThread]
		static void Main(string[] args)
		{
			UIElement						Dummy1=new UIElement();
			FrameworkElement				Dummy2=new FrameworkElement();
			SortedList<string, string>		ListClass=new SortedList<string, string>();
			string							StrFormat1="{0,-35}{1}";
			string							StrFormat2="{0,-35}{1} !";

			// Prejdem vsetky assemblies.
			foreach (AssemblyName AssemblyName in Assembly.GetExecutingAssembly().GetReferencedAssemblies())
			{
				// Prejdem vsetky typy.
				foreach (Type LType in Assembly.Load(AssemblyName).GetTypes())
				{
					// Prejdem vsetky ATTRIBUTES.
					foreach (object Obj in LType.GetCustomAttributes(typeof(ContentPropertyAttribute), true))
					{
						// Zistim ci je to ContentPropertyAttribute.
						if (LType.IsPublic==true && (Obj as ContentPropertyAttribute)!=null)
							ListClass.Add(LType.Name, (Obj as ContentPropertyAttribute).Name);
					}
				}
			}

			Console.WriteLine(StrFormat1, "Class", "Content Property");
			Console.WriteLine(StrFormat1, "-----", "----------------");

			foreach (string StrClass in ListClass.Keys)
				Console.WriteLine(StrFormat2, StrClass, ListClass[StrClass]);

			Console.ReadLine();
		}
//-----------------------------------------------------------------------------------------------------------------
	}
//-----------------------------------------------------------------------------------------------------------------
}
//-----------------------------------------------------------------------------------------------------------------