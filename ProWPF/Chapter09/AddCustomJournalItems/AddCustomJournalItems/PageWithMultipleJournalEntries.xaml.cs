using System;
using System.Collections.Generic;
using System.Text;
using System.Diagnostics;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
//------------------------------------------------------------------------
namespace AddCustomJournalItems
{
//------------------------------------------------------------------------
	public partial class PageWithMultipleJournalEntries:System.Windows.Controls.Page, IProvideCustomContentState
	{
//------------------------------------------------------------------------
		private static int					ID_COUNTER=1;
//------------------------------------------------------------------------
		// !!!!! Povodne program MAL CHYBU. Viazal CListSelectionJournalEntry s Page CO JE CHYBA. Ak totizto vyskocim tlacitkom Back az uplne na zaciatok - MainPage - tak sa pri klepnuti na Forward Button VYTVORI NOVA PAGE. Vtip bol v tom, ze kedze CListSelectionJournalEntry bol asocionavny s Page tak pridaval Items do ListBoxes STAREHO OBJEKTU Page - ktory UZ NEBOL VIDITELNY a na AKTUALNEJ PAGE NEBOLO VIDIET ZMENY V ListBoxes.
		// !!! Existuju 2 riesenia.
		// 1. Zrusit asociaciu medzi Page a CListSelectionJournalEntry - to je to co som urobil tu.
		// 2. Alebo jednoducho nastavit property Page KeepAlive na TRUE a tym BUDE STALE AKTIVNA IBA JEDNA Page a NENASTAVA PROBLEM so zlou asociaciu, kedze mame iba jednu Page.
		internal static PageWithMultipleJournalEntries	ACTUAL_PAGE=null;
//------------------------------------------------------------------------
		private int							MID;
        private string						MRestoredStateName;
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		public PageWithMultipleJournalEntries()
		{
			MID=ID_COUNTER++;
			Debug.WriteLine(string.Format("\tPageWithMultipleJournalEntries CONSTRUCTOR CALLED - ID: {0} !",MID));

			InitializeComponent();
			ACTUAL_PAGE=this;
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
        private void Page_Loaded(object Sender, EventArgs E)
        {
			MLSTSource.Items.Clear();
            MLSTSource.Items.Add("Red");
            MLSTSource.Items.Add("Blue");
            MLSTSource.Items.Add("Green");
            MLSTSource.Items.Add("Yellow");
            MLSTSource.Items.Add("Orange");
            MLSTSource.Items.Add("Black");
            MLSTSource.Items.Add("Pink");
            MLSTSource.Items.Add("Purple");
        }
//------------------------------------------------------------------------
        private void CmdAdd_Click(object Sender, RoutedEventArgs E)
        {
            if (MLSTSource.SelectedIndex!=-1)
            {
                NavigationService			Nav=NavigationService.GetNavigationService(this);
                string						ItemText=MLSTSource.SelectedItem.ToString();
                string						JournalName="Added "+ItemText;
				CListSelectionJournalEntry	Entries=GetJournalEntry(JournalName);

                Nav.AddBackEntry(Entries);

                MLSTTarget.Items.Add(ItemText);
                MLSTSource.Items.Remove(ItemText);

				Debug.WriteLine(string.Format("\tCmdAdd_Click() CALLED - ID: {0}, Entries: {1} !",MID,Entries.ToString()));
            }
        }
//------------------------------------------------------------------------
        private void CmdRemove_Click(object Sender, RoutedEventArgs E)
        {
            if (MLSTTarget.SelectedIndex!=-1)
            {              
                NavigationService			Nav=NavigationService.GetNavigationService(this);
                string						ItemText=MLSTTarget.SelectedItem.ToString();
                string						JournalName="Removed "+ItemText;
				CListSelectionJournalEntry	Entries=GetJournalEntry(JournalName);

                Nav.AddBackEntry(Entries);
                
                MLSTSource.Items.Add(ItemText);
                MLSTTarget.Items.Remove(ItemText);

				Debug.WriteLine(string.Format("\tCmdRemove_Click() CALLED - ID: {0}, Entries: {1} !",MID,Entries.ToString()));
            }
        }
//------------------------------------------------------------------------
        private CListSelectionJournalEntry GetJournalEntry(string JournalName)
        {
            List<string>			Source=GetListState(MLSTSource);
            List<string>			Target=GetListState(MLSTTarget);

            return(new CListSelectionJournalEntry(Source, Target, JournalName));
        }
//------------------------------------------------------------------------
        private List<String> GetListState(ListBox List)
        {
            List<string>		Items=new List<string>();

            foreach(string Item in List.Items)
                Items.Add(Item);

            return(Items);
        }
//------------------------------------------------------------------------
		private void OnShowListBoxesItems(object Sender, RoutedEventArgs E)
		{
			Debug.WriteLine("\n");
			Debug.WriteLine(string.Format("\tID: {0} !",MID));
			Debug.WriteLine("\tSourceItems:");
			
			for(int i=0;i<MLSTSource.Items.Count;i++)
				Debug.WriteLine(string.Format("\t\t{0}. {1} !",i+1,MLSTSource.Items[i]));

			Debug.WriteLine("\tTargetItems:");
			
			for(int i=0;i<MLSTTarget.Items.Count;i++)
				Debug.WriteLine(string.Format("\t\t{0}. {1} !",i+1,MLSTTarget.Items[i]));
			Debug.WriteLine("\n");
		}
//------------------------------------------------------------------------
		private void OnClearJournal(object Sender, RoutedEventArgs E)
		{
			Debug.WriteLine(string.Format("\tOnClearJournal() CALLED - ID: {0} !",MID));

			NavigationService			NS=NavigationService.GetNavigationService(this);

			while(NS.RemoveBackEntry()!=null)
				;
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
        public void Replay(CListSelectionJournalEntry State)
        {
            MLSTSource.Items.Clear();

            foreach(string Item in State.SourceItems)
				MLSTSource.Items.Add(Item);
            
            MLSTTarget.Items.Clear();

            foreach(string Item in State.TargetItems)
				MLSTTarget.Items.Add(Item);

            MRestoredStateName=State.JournalEntryName;

			Debug.WriteLine(string.Format("\tReplay() CALLED - ID: {0}, Entries: {1} !",MID,State.ToString()));
        }
//------------------------------------------------------------------------
        public CustomContentState GetContentState()
        {
            string					JournalName;

            if (MRestoredStateName!="")
                JournalName=MRestoredStateName;
            else
                JournalName="PageWithMultipleJournalEntries";

			CListSelectionJournalEntry	Ret=GetJournalEntry(JournalName);

			Debug.WriteLine(string.Format("\tGetContentState() CALLED - ID: {0}, Entries: {1} !",MID,Ret.ToString()));
            return(Ret);
        }
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------