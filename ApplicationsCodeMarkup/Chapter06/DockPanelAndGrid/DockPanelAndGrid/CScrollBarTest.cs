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
using System.Windows.Controls.Primitives;
//------------------------------------------------------------------------------
namespace DockPanelAndGrid
{
//------------------------------------------------------------------------------
	public class CScrollBarTest : Window
	{
//------------------------------------------------------------------------------
		private ScrollBar[]							MScrolls=new ScrollBar[3];
		private TextBlock[]							MTxtValue=new TextBlock[3];
		private Panel								MPnlColor;
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		public CScrollBarTest()
		{
			Title="Color Scroll";
			Width=500;
			Height=300;

			Grid				GridMain=new Grid();

			Content=GridMain;

			ColumnDefinition	ColDef = new ColumnDefinition();

			ColDef.Width=new GridLength(200, GridUnitType.Pixel);
			GridMain.ColumnDefinitions.Add(ColDef);

			ColDef=new ColumnDefinition();
			ColDef.Width=GridLength.Auto;
			GridMain.ColumnDefinitions.Add(ColDef);

			ColDef=new ColumnDefinition();
			ColDef.Width=new GridLength(100, GridUnitType.Star);
			GridMain.ColumnDefinitions.Add(ColDef);

			GridSplitter		Split=new GridSplitter();

			Split.HorizontalAlignment=HorizontalAlignment.Center;
			Split.VerticalAlignment=VerticalAlignment.Stretch;
			Split.Width=6;
			GridMain.Children.Add(Split);
			Grid.SetRow(Split, 0);
			Grid.SetColumn(Split, 1);

			MPnlColor=new StackPanel();
			MPnlColor.Background=new SolidColorBrush(SystemColors.WindowColor);
			GridMain.Children.Add(MPnlColor);
			Grid.SetRow(MPnlColor, 0);
			Grid.SetColumn(MPnlColor, 2);

			Grid				LGrid=new Grid();

			GridMain.Children.Add(LGrid);
			Grid.SetRow(LGrid, 0);
			Grid.SetColumn(LGrid, 0);

			RowDefinition		RowDef=new RowDefinition();

			RowDef.Height = GridLength.Auto;
			LGrid.RowDefinitions.Add(RowDef);

			RowDef=new RowDefinition();
			RowDef.Height=new GridLength(100, GridUnitType.Star);
			LGrid.RowDefinitions.Add(RowDef);

			RowDef=new RowDefinition();
			RowDef.Height=GridLength.Auto;
			LGrid.RowDefinitions.Add(RowDef);

			for (int i=0;i<3;i++)
			{
				ColDef=new ColumnDefinition();
				ColDef.Width=new GridLength(33, GridUnitType.Star);
				LGrid.ColumnDefinitions.Add(ColDef);
			}

			for (int i=0;i<3;i++)
			{
				Label			Lbl=new Label();

				Lbl.Content=new string[] { "Red", "Green", "Blue" }[i];
				Lbl.HorizontalAlignment=HorizontalAlignment.Center;
				LGrid.Children.Add(Lbl);
				Grid.SetRow(Lbl, 0);
				Grid.SetColumn(Lbl, i);

				MScrolls[i]=new ScrollBar();
				MScrolls[i].Focusable=true;
				MScrolls[i].Orientation=Orientation.Vertical;
				MScrolls[i].Minimum=0;
				MScrolls[i].Maximum=255;
				MScrolls[i].SmallChange=1;
				MScrolls[i].LargeChange=16;
				MScrolls[i].ValueChanged+=ScrollOnValueChanged;

				// Zavesim HANDLER na Scroll event.
				MScrolls[i].Scroll+=new ScrollEventHandler(CScrollBarTest_Scroll);

				LGrid.Children.Add(MScrolls[i]);
				Grid.SetRow(MScrolls[i], 1);
				Grid.SetColumn(MScrolls[i], i);

				MTxtValue[i]=new TextBlock();
				MTxtValue[i].TextAlignment=TextAlignment.Center;
				MTxtValue[i].HorizontalAlignment=HorizontalAlignment.Center;
				MTxtValue[i].Margin=new Thickness(5);
				LGrid.Children.Add(MTxtValue[i]);

				Grid.SetRow(MTxtValue[i], 2);
				Grid.SetColumn(MTxtValue[i], i);
			}

			Color				Clr=(MPnlColor.Background as SolidColorBrush).Color;

			MScrolls[0].Value=Clr.R;
			MScrolls[1].Value=Clr.G;
			MScrolls[2].Value=Clr.B;

			MScrolls[0].Focus();
		}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		private void ScrollOnValueChanged(object Sender, RoutedEventArgs Args)
		{
			ScrollBar		Scroll=Sender as ScrollBar;
			Panel			Pnl=Scroll.Parent as Panel;
			TextBlock		Txt=Pnl.Children[1+Pnl.Children.IndexOf(Scroll)] as TextBlock;

			Txt.Text=string.Format("{0}\n0x{0:X2}", (int)Scroll.Value);
			MPnlColor.Background=new SolidColorBrush(Color.FromRgb((byte) MScrolls[0].Value, (byte) MScrolls[1].Value,(byte) MScrolls[2].Value));
		}
//------------------------------------------------------------------------------
		private void CScrollBarTest_Scroll(object Sender, ScrollEventArgs E)
		{
			Console.WriteLine(string.Format("Value: [{0}], ScrollEventType: [{1}] !",E.NewValue,E.ScrollEventType));
		}
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------