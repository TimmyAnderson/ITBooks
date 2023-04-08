using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Input;
using System.Windows.Controls;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Controls.Primitives;
using System.Windows.Documents;
using System.IO;
using Microsoft.Win32;
//------------------------------------------------------------------------------
namespace Buttons
{
//------------------------------------------------------------------------------
	public class CEditSomeRichText : Window
	{
//------------------------------------------------------------------------------
        private RichTextBox							MTxtBox;
        private string								MStrFilter="Document Files(*.xaml)|*.xaml|All files (*.*)|*.*";
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		public CEditSomeRichText()
		{
            Title="Edit Some Rich Text";

            MTxtBox=new RichTextBox();
            MTxtBox.VerticalScrollBarVisibility=ScrollBarVisibility.Auto;
            Content=MTxtBox;

            MTxtBox.Focus();
		}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
        protected override void OnPreviewTextInput(TextCompositionEventArgs Args)
        {
            if (Args.ControlText.Length>0 && Args.ControlText[0]=='\x0F')
            {
                OpenFileDialog		Dlg=new OpenFileDialog();

                Dlg.CheckFileExists=true;
                Dlg.Filter=MStrFilter;

                if (((bool)Dlg.ShowDialog(this))==true)
                {
                    FlowDocument	Flow=MTxtBox.Document;
                    TextRange		Range=new TextRange(Flow.ContentStart, Flow.ContentEnd);
                    Stream			Strm=null;

                    try
                    {
                        Strm=new FileStream(Dlg.FileName, FileMode.Open);
                        Range.Load(Strm, DataFormats.Xaml);
                    }
                    catch (Exception Exc)
                    {
                        MessageBox.Show(Exc.Message, Title);
                    }
                    finally
                    {
                        if (Strm!=null)
                            Strm.Close();
                    }
                }

                Args.Handled=true;
            }

            if (Args.ControlText.Length>0 && Args.ControlText[0]=='\x13')
            {
                SaveFileDialog		Dlg=new SaveFileDialog();

                Dlg.Filter=MStrFilter;

                if (((bool)Dlg.ShowDialog(this))==true)
                {
                    FlowDocument	Flow=MTxtBox.Document;
                    TextRange		Range=new TextRange(Flow.ContentStart, Flow.ContentEnd);
                    Stream			Strm=null;

                    try
                    {
                        Strm=new FileStream(Dlg.FileName, FileMode.Create);
                        Range.Save(Strm, DataFormats.Xaml);
                    }
                    catch (Exception Exc)
                    {
                        MessageBox.Show(Exc.Message, Title);
                    }
                    finally
                    {
                        if (Strm!=null)
                            Strm.Close();
                    }
                }

                Args.Handled=true;
            }

            base.OnPreviewTextInput(Args);
        }
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------