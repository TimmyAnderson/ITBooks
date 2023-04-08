using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Collections.ObjectModel;
using System.Windows;
using System.Xml.Serialization;
using Microsoft.Win32;
//-------------------------------------------------------------------------------------------------------
namespace DataViews
{
//-------------------------------------------------------------------------------------------------------
	// Kolekcia zaznamov typu Person.
	// !!! Tym, ze ju dedim z ObservableCollection<>, tak ziskava AUTOMATICKU NOTIFIKACIU o ZMENE.
	public class People : ObservableCollection<Person>
	{
//-------------------------------------------------------------------------------------------------------
        private const string									MStrFilter="People XML files (*.PeopleXml)|*.PeopleXml|All files (*.*)|*.*";
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
        public static People Load(Window Win)
        {
            OpenFileDialog				Dlg=new OpenFileDialog();

            Dlg.Filter=MStrFilter;

            People				People=null;

            if (((bool)Dlg.ShowDialog(Win))==true)
            {
                try
                {
                    StreamReader		Reader=new StreamReader(Dlg.FileName);
                    XmlSerializer		XML=new XmlSerializer(typeof(People));

					// Deserializujem CELU KOLEKCIU.
                    People=(People) XML.Deserialize(Reader);

                    Reader.Close();
                }
                catch (Exception Exc)
                {
                    MessageBox.Show(string.Format("Could not load file: [{0}] !",Exc.Message),Win.Title, MessageBoxButton.OK, MessageBoxImage.Exclamation);
                    People=null;
                }
            }

            return(People);
        }
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
        public bool Save(Window Win)
        {
            SaveFileDialog				Dlg=new SaveFileDialog();

            Dlg.Filter=MStrFilter;

            if (((bool)Dlg.ShowDialog(Win))==true)
            {
                try
                {
                    StreamWriter		Writer=new StreamWriter(Dlg.FileName);
                    XmlSerializer		XML=new XmlSerializer(GetType());

                    XML.Serialize(Writer,this);
                    Writer.Close();
                }
                catch (Exception Exc)
                {
                    MessageBox.Show(string.Format("Could not save file: [{0}] !",Exc.Message),Win.Title, MessageBoxButton.OK, MessageBoxImage.Exclamation);
                    return(false);
                }
            }

            return(true);
        }
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------