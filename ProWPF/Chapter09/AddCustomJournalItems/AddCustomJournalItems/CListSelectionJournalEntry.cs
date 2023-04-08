using System;
using System.Collections.Generic;
using System.Text;
using System.Diagnostics;
using System.Windows.Navigation;
using System.Windows.Controls;
//------------------------------------------------------------------------
namespace AddCustomJournalItems
{
//------------------------------------------------------------------------
    //public delegate void DReplayListChange(CListSelectionJournalEntry state);
//------------------------------------------------------------------------
	[Serializable]
	public class CListSelectionJournalEntry : CustomContentState
	{
//------------------------------------------------------------------------
        private List<string>					MSourceItems;
        private List<string>					MTargetItems;
        private string							MJournalName;
        //private DReplayListChange				MReplayListChange;
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
        public CListSelectionJournalEntry(List<string> SourceItems, List<string> TargetItems, string JournalName)
        {
            MSourceItems=SourceItems;
            MTargetItems=TargetItems;
            MJournalName=JournalName;
            //MReplayListChange=ReplayListChange;
        }
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
        public override string					JournalEntryName
        {
            get
            {
                return(MJournalName);
            }
        }
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
        public List<string>						SourceItems
        {
            get
			{
				return(MSourceItems);
			}
        }
//------------------------------------------------------------------------
        public List<string>						TargetItems
        {
            get
			{
				return(MTargetItems);
			}
        }
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
        public override void Replay(NavigationService NavigationService, NavigationMode Mode)
        {  
            //MReplayListChange(this);
			PageWithMultipleJournalEntries.ACTUAL_PAGE.Replay(this);
        }
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		public override string ToString()
		{
			StringBuilder		SB=new StringBuilder();

			SB.Append("SourceItems: (");
			
			for(int i=0;i<MSourceItems.Count;i++)
			{
				if (i!=0)
					SB.Append(",");

				SB.Append(MSourceItems[i]);
			}

			SB.Append(") TargetItems: (");

			for(int i=0;i<MTargetItems.Count;i++)
			{
				if (i!=0)
					SB.Append(",");

				SB.Append(MTargetItems[i]);
			}

			SB.Append(")");

			return(SB.ToString());
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------