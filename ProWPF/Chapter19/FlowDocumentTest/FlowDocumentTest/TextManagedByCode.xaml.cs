using System;
using System.Collections.Generic;
using System.Diagnostics;
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
namespace FlowDocumentTest
{
//------------------------------------------------------------------------
	public partial class TextManagedByCode:Window
	{
//------------------------------------------------------------------------
		public TextManagedByCode()
		{
			InitializeComponent();
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		private void OnClick(object Sender, RoutedEventArgs E)
		{
			int								Counter=0;
			IEnumerator<Block>				E1=MDocument.Blocks.GetEnumerator();

			E1.Reset();

			while(E1.MoveNext()==true)
			{
				if (E1.Current.GetType()==typeof(Paragraph))
				{
					Paragraph				P=(Paragraph) E1.Current;
					IEnumerator<Inline>		E2=P.Inlines.GetEnumerator();

					E2.Reset();

					while (E2.MoveNext()==true)
					{
						if (E2.Current.GetType()==typeof(Run))
						{
							Run					R=(Run) E2.Current;

							Debug.WriteLine(string.Format("{0}. {1} !",++Counter,R.Text));
						}
					}
				}

			}
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------