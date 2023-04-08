using System;
using System.Reflection;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Shapes;
using System.Windows.Media.Imaging;
//------------------------------------------------------------------------------
namespace Menus
{
//------------------------------------------------------------------------------
	public class CAcceleratorByKeyDown : CDisableMenuItem
	{
//------------------------------------------------------------------------------
        private KeyGesture										MGestCut=new KeyGesture(Key.X, ModifierKeys.Control);
        private KeyGesture										MGestCopy=new KeyGesture(Key.C, ModifierKeys.Control);
        private KeyGesture										MGestPaste=new KeyGesture(Key.V, ModifierKeys.Control);
        private KeyGesture										MGestDelete=new KeyGesture(Key.Delete);
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
        public CAcceleratorByKeyDown()
        {
            Title="Control X, C, and V";

            MItemCut.InputGestureText="Ctrl+X";
            MItemCopy.InputGestureText="Ctrl+C";
            MItemPaste.InputGestureText="Ctrl+V";
            MItemDelete.InputGestureText="Delete";
		}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
        protected override void OnPreviewKeyDown(KeyEventArgs Args)
        {
            base.OnKeyDown(Args);
            Args.Handled=true;

            if (MGestCut.Matches(null, Args)==true)
                CutOnClick(this, Args);
            else if (MGestCopy.Matches(null, Args)==true)
                CopyOnClick(this, Args);
            else if (MGestPaste.Matches(null, Args)==true)
                PasteOnClick(this, Args);
            else if (MGestDelete.Matches(null, Args)==true)
                DeleteOnClick(this, Args);
            else
                Args.Handled=false;
        }
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------