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
namespace Buttons
{
//------------------------------------------------------------------------------
	public class CResouceImageButton : Window
	{
//------------------------------------------------------------------------------
		public CResouceImageButton()
		{
            Title="Image the Button";

			// Na pristup k Resource pouzijem 'pack' syntax.
            Uri				Uri=new Uri("pack://application:,,/Images/Munch.png");
            BitmapImage		Bitmap=new BitmapImage(Uri);
            Image			Img=new Image();

            Img.Source=Bitmap;
            Img.Stretch=Stretch.None;

            Button			Btn=new Button();

            Btn.Content=Img;
            Btn.HorizontalAlignment=HorizontalAlignment.Center;
            Btn.VerticalAlignment=VerticalAlignment.Center;

            Content=Btn;
		}
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------