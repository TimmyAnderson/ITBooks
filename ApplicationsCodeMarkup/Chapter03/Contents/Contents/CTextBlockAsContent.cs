using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Input;
using System.Windows.Controls;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Documents;
//------------------------------------------------------------------------------
namespace Contents
{
//------------------------------------------------------------------------------
	public class CTextBlockAsContent : Window
	{
//------------------------------------------------------------------------------
		public CTextBlockAsContent()
		{
            Title="Format the Text";

            TextBlock				Txt=new TextBlock();

            Txt.FontSize=32;
            Txt.Inlines.Add("This is some ");
            Txt.Inlines.Add(new Italic(new Run("italic")));
            Txt.Inlines.Add(" text, and this is some ");
            Txt.Inlines.Add(new Bold(new Run("bold")));
            Txt.Inlines.Add(" text, and let's cap it off with some ");
            Txt.Inlines.Add(new Bold(new Italic(new Run("bold italic"))));
            Txt.Inlines.Add(" text.");

            Txt.TextWrapping=TextWrapping.Wrap;

            Content=Txt;
		}
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------