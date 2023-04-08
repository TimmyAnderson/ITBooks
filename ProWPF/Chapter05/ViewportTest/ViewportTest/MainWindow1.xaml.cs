using System;
using System.Collections.Generic;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
//------------------------------------------------------------------------
// 1. Program demonstruje pouzitie Viewport.
// 2. Zvlastnostou Viewport je, ze pri zoomingu a vobec zmene velkosti za jeho Content meni spolu so zoomingom, teda zmensuje sa, alebo zvecsuje sa.
// !!! 3. Ak NEPOUZIJEM Viewport tak obrazec sa NEBUDE proporcne ZVECSOVAT - ako je to vidiet na MainWindow1.xaml.
// !!! 4. Ak POUZIJEM Viewport tak obrazec sa BUDE proporcne ZVECSOVAT - ako je to vidiet na MainWindow2.xaml.
// !!! 5. Viewport sa pouziva na zobrazenie grafiky.
// !!! 6. Pomocou properties Stretch a StretchDirection mozem ovladat proces zoomingu a toho ako sa bure respektovat ratio.
//------------------------------------------------------------------------
namespace ViewportTest
{
//------------------------------------------------------------------------
	public partial class MainWindow1:System.Windows.Window
	{
//------------------------------------------------------------------------
		public MainWindow1()
		{
			InitializeComponent();
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------