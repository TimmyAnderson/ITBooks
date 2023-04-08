using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
//-----------------------------------------------------------------------------------------------------------------
namespace WindowsApplication
{
//-----------------------------------------------------------------------------------------------------------------
	public partial class YellowPadWindow : Window
	{
//-----------------------------------------------------------------------------------------------------------------
        private void StylusModeOnOpened(object Sender, RoutedEventArgs Args)
        {
            MenuItem			Item=Sender as MenuItem;

            foreach (MenuItem Child in Item.Items)
                Child.IsChecked=(MInkCanvas.EditingMode==(InkCanvasEditingMode)Child.Tag);
        }
//-----------------------------------------------------------------------------------------------------------------
        private void StylusModeOnClick(object Sender, RoutedEventArgs Args)
        {
            MenuItem			Item=Sender as MenuItem;

            MInkCanvas.EditingMode=(InkCanvasEditingMode) Item.Tag;
        }
//-----------------------------------------------------------------------------------------------------------------
        private void EraserModeOnOpened(object Sender, RoutedEventArgs Args)
        {
            MenuItem			Item=Sender as MenuItem;

            foreach (MenuItem Child in Item.Items)
                Child.IsChecked=(MInkCanvas.EditingModeInverted==(InkCanvasEditingMode)Child.Tag);
        }
//-----------------------------------------------------------------------------------------------------------------
        private void EraserModeOnClick(object Sender, RoutedEventArgs Args)
        {
            MenuItem			Item=Sender as MenuItem;

            MInkCanvas.EditingModeInverted=(InkCanvasEditingMode) Item.Tag;
        }
//-----------------------------------------------------------------------------------------------------------------
	}
//-----------------------------------------------------------------------------------------------------------------
}
//-----------------------------------------------------------------------------------------------------------------