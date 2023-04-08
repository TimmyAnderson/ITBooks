using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//------------------------------------------------------------------------------
namespace ApplicationShutDown
{
//------------------------------------------------------------------------------
	class Program
	{
//------------------------------------------------------------------------------
		[STAThread]
		static void Main(string[] args)
		{
			try
			{
				CShutDownApplication	App=new CShutDownApplication();

				App.Run();
			}
			catch(Exception E)
			{
				System.Diagnostics.Debug.WriteLine(string.Format("!!!!! EXCEPTION: [{0}] !",E));
			}
		}
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------