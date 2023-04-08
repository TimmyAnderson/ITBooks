using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Input;
using System.Windows.Controls;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
using System.Windows.Threading;
//------------------------------------------------------------------------------
namespace CustomPanels
{
//------------------------------------------------------------------------------
	public class CCustomUniformGridWindow : Window
	{
//------------------------------------------------------------------------------
        public CCustomUniformGridWindow(int TestIndex)
        {
            Title="Duplicate Uniform Grid";

            CCustomUniformGrid	Unigrid=new CCustomUniformGrid();

            Unigrid.Columns=5;
            Content=Unigrid;

            Random				Rand=new Random();

            for (int Index=0;Index<48;Index++)
            {
                Button			Btn=new Button();

                Btn.Name="Button"+Index;
                Btn.Content=Btn.Name;
				// Kazdy Button ma inu velkost fontu.
                Btn.FontSize+=Rand.Next(10);
                Unigrid.Children.Add(Btn);
            }

			// Pripojim RE na Click k Window.
            AddHandler(Button.ClickEvent, new RoutedEventHandler(ButtonOnClick));

			if (TestIndex==2)
			{
				SizeToContent=SizeToContent.WidthAndHeight;
			}
			else if (TestIndex==3)
			{
				Unigrid.HorizontalAlignment=HorizontalAlignment.Center;
				Unigrid.VerticalAlignment=VerticalAlignment.Center;
			}
			else if (TestIndex==4)
			{
				for (int Index=0;Index<48;Index++)
				{
					Button			Btn=(Button) Unigrid.Children[Index];

					Btn.HorizontalAlignment=HorizontalAlignment.Center;
					Btn.VerticalAlignment=VerticalAlignment.Center;
				}
			}
			else if (TestIndex==5)
			{
				// Velkost okna dam MENSIU ako velkost potrebnej plochy.
				Width=300;
				Height=200;
			}
        }
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
        private void ButtonOnClick(object Sender, RoutedEventArgs Args)
        {
            Button			Btn=Args.Source as Button;

            MessageBox.Show(string.Format("[{0}] has been clicked !",Btn.Name), Title);
        }
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------