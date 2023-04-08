using System;
using System.Reflection;
using System.IO;
//-------------------------------------------------------------------------------------------------------
namespace HelloWorld
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			Assembly		A=Assembly.GetAssembly(typeof(Program));
			string[]		Resources=A.GetManifestResourceNames();

			Console.WriteLine(string.Format("Resource COUNT: [{0}] !",Resources.Length));

			foreach(string Resource in Resources)
				Console.WriteLine(string.Format("Resource: [{0}] !",Resource));

			Stream			S=A.GetManifestResourceStream(Resources[0]);

			Console.WriteLine(string.Format("Resource length: [{0}] !",S.Length));
			Console.WriteLine();
			Console.WriteLine("Resource CONTENT:");
			Console.WriteLine();

			using (StreamReader SR=new StreamReader(S))
			{
				string		ResourceContent=SR.ReadToEnd();

				Console.WriteLine(ResourceContent);
			}

			S.Close();			

			Console.WriteLine();
			Console.WriteLine();
			Console.WriteLine("\nPress any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------