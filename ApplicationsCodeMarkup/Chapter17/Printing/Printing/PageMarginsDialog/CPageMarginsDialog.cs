using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Controls.Primitives;
//------------------------------------------------------------------------------
namespace Printing
{
//------------------------------------------------------------------------------
	public class CPageMarginsDialog : Window
	{
//------------------------------------------------------------------------------
        enum Side
        {
            Left, Right, Top, Bottom
        }
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
        private TextBox[]									MTxtBox=new TextBox[4];
        private Button										MBtnOK;
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
        public CPageMarginsDialog()
        {
            Title = "Page Setup";
            ShowInTaskbar=false;

			// Kedze vytvaram dialogove okno, tak podla toho prisposobim i properties.
            WindowStyle=WindowStyle.ToolWindow;
            WindowStartupLocation=WindowStartupLocation.CenterOwner;
            SizeToContent=SizeToContent.WidthAndHeight;
            ResizeMode=ResizeMode.NoResize;

            StackPanel				LStack=new StackPanel();

            Content=LStack;

            GroupBox				LGroupBox=new GroupBox();

            LGroupBox.Header="Margins (inches)";
            LGroupBox.Margin=new Thickness(12);
            LStack.Children.Add(LGroupBox);

            Grid					LGrid=new Grid();

            LGrid.Margin=new Thickness(6);
            LGroupBox.Content=LGrid;

            for (int i=0;i<2;i++)
            {
                RowDefinition		RowDef=new RowDefinition();

                RowDef.Height=GridLength.Auto;
                LGrid.RowDefinitions.Add(RowDef);
            }

            for (int i=0;i<4;i++)
            {
                ColumnDefinition	ColDef=new ColumnDefinition();

                ColDef.Width=GridLength.Auto;
                LGrid.ColumnDefinitions.Add(ColDef);
            }

            for (int i=0;i<4;i++)
            {
                Label				LLabel=new Label();

                LLabel.Content="_"+Enum.GetName(typeof(Side), i)+":";
                LLabel.Margin=new Thickness(6);
                LLabel.VerticalAlignment=VerticalAlignment.Center;
                LGrid.Children.Add(LLabel);
                Grid.SetRow(LLabel, i/2);
                Grid.SetColumn(LLabel, 2*(i%2));

                MTxtBox[i]=new TextBox();
                MTxtBox[i].TextChanged+=TextBoxOnTextChanged;
                MTxtBox[i].MinWidth=48;
                MTxtBox[i].Margin=new Thickness(6);
                LGrid.Children.Add(MTxtBox[i]);
                Grid.SetRow(MTxtBox[i], i / 2);
                Grid.SetColumn(MTxtBox[i], 2 * (i % 2) + 1);
            }

            UniformGrid				LUniGrid=new UniformGrid();

            LUniGrid.Rows=1;
            LUniGrid.Columns=2;
            LStack.Children.Add(LUniGrid);

            MBtnOK=new Button();
            MBtnOK.Content="OK";
            MBtnOK.IsDefault=true;
            MBtnOK.IsEnabled=false;
            MBtnOK.MinWidth=60;
            MBtnOK.Margin=new Thickness(12);
            MBtnOK.HorizontalAlignment=HorizontalAlignment.Center;
            MBtnOK.Click+=OkButtonOnClick;
            LUniGrid.Children.Add(MBtnOK);

            Button					LBtnCancel=new Button();

            LBtnCancel.Content="Cancel";
            LBtnCancel.IsCancel=true;
            LBtnCancel.MinWidth=60;
            LBtnCancel.Margin=new Thickness(12);
            LBtnCancel.HorizontalAlignment=HorizontalAlignment.Center;
            LUniGrid.Children.Add(LBtnCancel);
        }
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
        public Thickness										PageMargins
        {
            get
            {
                return(new Thickness(double.Parse(MTxtBox[(int)Side.Left].Text)*96,double.Parse(MTxtBox[(int)Side.Top].Text)*96,double.Parse(MTxtBox[(int)Side.Right].Text)*96,double.Parse(MTxtBox[(int)Side.Bottom].Text)*96));
            }
            set
            {
                MTxtBox[(int)Side.Left].Text=(value.Left/96).ToString("F3");
                MTxtBox[(int)Side.Right].Text=(value.Right/96).ToString("F3");
                MTxtBox[(int)Side.Top].Text=(value.Top/96).ToString("F3");
                MTxtBox[(int)Side.Bottom].Text=(value.Bottom/96).ToString("F3");
            }
        }
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
        private void TextBoxOnTextChanged(object Sender, TextChangedEventArgs Args)
        {
            double		Result;

            MBtnOK.IsEnabled=(double.TryParse(MTxtBox[(int)Side.Left].Text, out Result)==true && double.TryParse(MTxtBox[(int)Side.Right].Text, out Result)==true && double.TryParse(MTxtBox[(int)Side.Top].Text, out Result)==true && double.TryParse(MTxtBox[(int)Side.Bottom].Text, out Result)==true);
        }
//------------------------------------------------------------------------------
        private void OkButtonOnClick(object Sender, RoutedEventArgs Args)
        {
            DialogResult=true;
        }
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------