using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Xml.Serialization;
using Microsoft.Win32;
//-------------------------------------------------------------------------------------------------------
namespace DataViews
{
//-------------------------------------------------------------------------------------------------------
	public partial class SingleRecordDataEntry : Window
	{
//-------------------------------------------------------------------------------------------------------
        private const string									MStrFilter="Person XML files (*.PersonXml)|*.PersonXml|All files (*.*)|*.*";
//-------------------------------------------------------------------------------------------------------
        private XmlSerializer									MXML=new XmlSerializer(typeof(Person));
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
        public SingleRecordDataEntry()
        {
            InitializeComponent();

            ApplicationCommands.New.Execute(null, this);
            MPnlPerson.Children[1].Focus();
        }
//-------------------------------------------------------------------------------------------------------
        private void NewOnExecuted(object Sender, ExecutedRoutedEventArgs Args)
        {
            MPnlPerson.DataContext = new Person();
        }
//-------------------------------------------------------------------------------------------------------
        private void OpenOnExecuted(object Sender, ExecutedRoutedEventArgs Args)
        {
            OpenFileDialog				Dlg=new OpenFileDialog();

            Dlg.Filter=MStrFilter;

            Person						Pers;

            if ((bool)Dlg.ShowDialog(this))
            {
                try
                {
                    StreamReader		Reader=new StreamReader(Dlg.FileName);

                    Pers=(Person) MXML.Deserialize(Reader);
                    Reader.Close();
                }
                catch (Exception Exc)
                {
                    MessageBox.Show(string.Format("Could not load file: [{0}] !",Exc.Message),Title, MessageBoxButton.OK, MessageBoxImage.Exclamation);
                    return;
                }

                MPnlPerson.DataContext=Pers;
            }
        }
//-------------------------------------------------------------------------------------------------------
        private void SaveOnExecuted(object Sender, ExecutedRoutedEventArgs Args)
        {
            SaveFileDialog			Dlg=new SaveFileDialog();

            Dlg.Filter=MStrFilter;

            if (((bool)Dlg.ShowDialog(this))==true)
            {
                try
                {
                    StreamWriter		Writer = new StreamWriter(Dlg.FileName);

                    MXML.Serialize(Writer, MPnlPerson.DataContext);
                    Writer.Close();
                }
                catch (Exception Exc)
                {
                    MessageBox.Show(string.Format("Could not save file: [{0}] !",Exc.Message),Title, MessageBoxButton.OK, MessageBoxImage.Exclamation);
                    return;
                }
            }
        }
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------