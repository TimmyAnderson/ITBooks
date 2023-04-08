using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Diagnostics;
using System.IO;
using System.Windows;
using System.Windows.Media;
using System.Windows.Markup;
using System.Windows.Navigation;
//-----------------------------------------------------------------------------------------------------------------
namespace WindowsApplication
{
//-----------------------------------------------------------------------------------------------------------------
	public partial class YellowPadAboutDialog
	{
//-----------------------------------------------------------------------------------------------------------------
        public YellowPadAboutDialog()
        {
            InitializeComponent();

            Uri				Uri=new Uri("pack://application:,,,/Images/Signature.xaml");
            Stream			LStream=Application.GetResourceStream(Uri).Stream;
            Drawing			LDrawing=(Drawing) XamlReader.Load(LStream);

            LStream.Close();

            MImgSignature.Source=new DrawingImage(LDrawing);
        }
//-----------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------
        private void LinkOnRequestNavigate(object Sender, RequestNavigateEventArgs Args)
        {
			// Spusti IE.
            Process.Start(Args.Uri.OriginalString);

            Args.Handled=true;
        }
//-----------------------------------------------------------------------------------------------------------------
	}
//-----------------------------------------------------------------------------------------------------------------
}
//-----------------------------------------------------------------------------------------------------------------