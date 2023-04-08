using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.AddIn.Pipeline;
using Contract;
using HostView;
//------------------------------------------------------------------------
// 1. HostAdapter sluzi na prepojenie ViewHost a Contract pre CALLBACK ROZHRANIE.
// 2. Trieda MUSI mat konstruktor, ktory ma ako parameter CUSTOM triedu AddInView.
//------------------------------------------------------------------------
namespace HostSideAdapter
{
//------------------------------------------------------------------------
	public class CHostObjectViewToContractHostAdapter : ContractBase, IHostObjectContract
	{
//------------------------------------------------------------------------
		private CHostObject						MView;
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		public CHostObjectViewToContractHostAdapter(CHostObject View)
		{
			MView=View;
		}
//------------------------------------------------------------------------
		public void ReportProgress(int ProgressPercent)
		{
			MView.ReportProgress(ProgressPercent);
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------