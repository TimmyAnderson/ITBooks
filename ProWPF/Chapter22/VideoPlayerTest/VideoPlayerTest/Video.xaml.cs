using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
//------------------------------------------------------------------------
namespace VideoPlayerTest
{
//------------------------------------------------------------------------
	public partial class Video:Window
	{
//------------------------------------------------------------------------
		public Video()
		{
			InitializeComponent();
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
        private void CmdPlay_Click(object Sender, RoutedEventArgs E)
        {
            MVideo.Position=TimeSpan.Zero;
            MVideo.Play();
        }
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------