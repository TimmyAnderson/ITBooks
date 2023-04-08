using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Input;
//------------------------------------------------------------------------------
namespace InheritAppAndWindow
{
//------------------------------------------------------------------------------
	public class CMyApplication : Application
	{
//------------------------------------------------------------------------------
        protected override void OnStartup(StartupEventArgs Args)
        {
            base.OnStartup(Args);

            CMyWindow			Win=new CMyWindow();

            Win.Show();
        }
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------