using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Diagnostics;//-----------------------------------------------------------------------------
namespace ManagedStackAllock
{
//-----------------------------------------------------------------------------
	class Program
	{
//-----------------------------------------------------------------------------
		private unsafe static void Test()
		{
			string			Text="Hello World !";
			int				Len=Text.Length;
			char*			OnStack=stackalloc char[Len];
			char*			P=OnStack;

			for(int i=0;i<Len;i++)
			{
				*P=Text[i];
				P++;
			}

			StringBuilder	SB=new StringBuilder();
			P=OnStack;

			for(int i=0;i<Len;i++)
			{
				SB.Append(*P);
				P++;
			}

			Console.WriteLine(string.Format("Text: [{0}] !",SB.ToString()));
		}
//-----------------------------------------------------------------------------
		static void Main(string[] args)
		{
			Test();

			Console.WriteLine("Press any key to EXIT !");
			Console.ReadLine();
		}
//-----------------------------------------------------------------------------
	}
//-----------------------------------------------------------------------------
}
//-----------------------------------------------------------------------------