using System;
using System.Collections.Generic;
using System.Windows.Forms;
//-------------------------------------------------------------------------------------------------------
namespace SCCallbackClient
{
//-------------------------------------------------------------------------------------------------------
	static class Program
	{
//-------------------------------------------------------------------------------------------------------
		[STAThread]
		static void Main()
		{
			Application.EnableVisualStyles();
			Application.SetCompatibleTextRenderingDefault(false);
			Application.Run(new CMainForm());
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------