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
	public class CMyWindow : Window
	{
//------------------------------------------------------------------------------
        public CMyWindow()
        {
            Title="Inherit App & Window";
        }
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
        protected override void OnMouseDown(MouseButtonEventArgs Args)
        {
            base.OnMouseDown(Args);

            string			StrMessage=string.Format("Window clicked with {0} button at point ({1}) !", Args.ChangedButton, Args.GetPosition(this));

            MessageBox.Show(StrMessage,Title);
        }
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------