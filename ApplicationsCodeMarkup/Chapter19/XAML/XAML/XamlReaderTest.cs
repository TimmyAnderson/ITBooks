using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Markup;
using System.Xml;
//-----------------------------------------------------------------------------------------------------------------
namespace XAML
{
//-----------------------------------------------------------------------------------------------------------------
	public class XamlReaderTest : Window
	{
//-----------------------------------------------------------------------------------------------------------------
        public XamlReaderTest()
        {
            Title="Load Embedded Xaml";

            string			StrXaml=
										"<Button xmlns='http://schemas.microsoft.com/" +
															  "winfx/2006/xaml/presentation'" +
										"        Foreground='LightSeaGreen' FontSize='24pt'>" +
										"    Click me!" +
										"</Button>";

            StringReader	StrReader=new StringReader(StrXaml);
            XmlTextReader	XmlReader=new XmlTextReader(StrReader);

			// Vytvori zo Stream hierarchiu WPF elements.
            object			Obj=XamlReader.Load(XmlReader);  

			// Tieto WPF elements nastavim ako CONTENT Window.
            Content=Obj;
        }
//-----------------------------------------------------------------------------------------------------------------
	}
//-----------------------------------------------------------------------------------------------------------------
}
//-----------------------------------------------------------------------------------------------------------------