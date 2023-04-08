using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Shapes;
//-----------------------------------------------------------------------------------------------------------------
namespace WindowsApplication
{
//-----------------------------------------------------------------------------------------------------------------
	public class CColorListBoxItem : ListBoxItem
	{
//-----------------------------------------------------------------------------------------------------------------
        private string								MStr;
        private Rectangle							MRect;
        private TextBlock							MText;
//-----------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------
        public CColorListBoxItem()
        {
            StackPanel		Stack = new StackPanel();

            Stack.Orientation=Orientation.Horizontal;
            Content=Stack;

            MRect=new Rectangle();
            MRect.Width=16;
            MRect.Height=16;
            MRect.Margin=new Thickness(2);
            MRect.Stroke=SystemColors.WindowTextBrush;
            Stack.Children.Add(MRect);

            MText=new TextBlock();
            MText.VerticalAlignment=VerticalAlignment.Center;
            Stack.Children.Add(MText);
        }
//-----------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------
        public string								Text
        {
            get
			{
				return MStr;
			}
            set 
            { 
                MStr=value;

                string			StrSpaced=MStr[0].ToString();

                for (int i=1;i<MStr.Length;i++)
                    StrSpaced+=(char.IsUpper(MStr[i]) ? " " : "") + MStr[i].ToString();

                MText.Text=StrSpaced;
            }
        }
//-----------------------------------------------------------------------------------------------------------------
        public Color Color
        {
            get 
            { 
                SolidColorBrush			Brush=MRect.Fill as SolidColorBrush;

                return((Brush==null) ? Colors.Transparent : Brush.Color);
            }
            set
			{
				MRect.Fill=new SolidColorBrush(value);
			}
        }
//-----------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------
        protected override void OnSelected(RoutedEventArgs Args)
        {
            base.OnSelected(Args);

            MText.FontWeight=FontWeights.Bold;
        }
//-----------------------------------------------------------------------------------------------------------------
        protected override void OnUnselected(RoutedEventArgs Args)
        {
            base.OnUnselected(Args);

            MText.FontWeight=FontWeights.Regular;
        }
//-----------------------------------------------------------------------------------------------------------------
        public override string ToString()
        {
            return(MStr);
        }
//-----------------------------------------------------------------------------------------------------------------
	}
//-----------------------------------------------------------------------------------------------------------------
}
//-----------------------------------------------------------------------------------------------------------------