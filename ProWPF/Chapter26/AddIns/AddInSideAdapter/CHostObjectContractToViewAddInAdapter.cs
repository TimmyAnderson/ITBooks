using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.AddIn.Pipeline;
using AddInView;
using Contract;
//------------------------------------------------------------------------
// 1. AddInSideAdapter sluzi na prepojenie AddInView a Contract.
// 2. Trieda MUSI mat konstruktor, ktory ma ako parameter CUSTOM triedu AddInView.
//------------------------------------------------------------------------
namespace AddInSideAdapter
{
//------------------------------------------------------------------------
	public class CHostObjectContractToViewAddInAdapter : CHostObject
	{
//------------------------------------------------------------------------
		private IHostObjectContract				MContract;
		private ContractHandle					MHandle;
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		public CHostObjectContractToViewAddInAdapter(IHostObjectContract Contract)
		{
			MContract=Contract;
			MHandle=new ContractHandle(Contract);
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		public override void ReportProgress(int ProgressPercent)
		{
			MContract.ReportProgress(ProgressPercent);
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------