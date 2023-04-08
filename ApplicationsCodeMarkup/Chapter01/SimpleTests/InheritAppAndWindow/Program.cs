using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//------------------------------------------------------------------------------
namespace InheritAppAndWindow
{
//------------------------------------------------------------------------------
	public class Program
	{
//------------------------------------------------------------------------------
        [STAThread]
		static void Main(string[] args)
		{
			try
			{
	            CMyApplication		App=new CMyApplication();
            
				App.Run();
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION: [{0}] !",E));
			}

			Console.WriteLine("Press any key to EXIT !");
			Console.ReadKey();
		}
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------