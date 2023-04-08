using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Input;
using System.Windows.Controls;
using System.Windows.Media;
using System.Windows.Media.Imaging;
//------------------------------------------------------------------------------
namespace StackAndWrapPanels
{
//------------------------------------------------------------------------------
	public class CWrapPanel : Window
	{
//------------------------------------------------------------------------------
		public CWrapPanel()
		{
            Title="Wrap Panel";

			Random				R=new Random();
			WrapPanel			WP=new WrapPanel();

			Content=WP;

			for (int i=0;i<50;i++)
			{
				Button			B=new Button();
				int				Size=R.Next(10);
				StringBuilder	SB=new StringBuilder();

				for (int j=0;j<Size;j++)
					SB.Append("A");

				B.Content=SB.ToString();
				WP.Children.Add(B);
			}
		}
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------