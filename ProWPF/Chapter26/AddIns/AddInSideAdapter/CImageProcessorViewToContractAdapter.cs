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
// 3. V projekte je nastavena referencia na AddInView.DLL a Contract.DLL pricom Copy Local MUSI BYT NASTAVENY NA FALSE.
//------------------------------------------------------------------------
namespace AddInSideAdapter
{
//------------------------------------------------------------------------
	[AddInAdapter]
	public class CImageProcessorViewToContractAdapter : ContractBase, IImageProcessorContract
	{
//------------------------------------------------------------------------
		private CImageProcessorAddInView			MView;
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		public CImageProcessorViewToContractAdapter(CImageProcessorAddInView View)
		{
			MView=View;
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		public byte[] ProcessImageBytes(byte[] Pixels)
		{
			// Robim forwarding z Contract na View.
			return(MView.ProcessImageBytes(Pixels));
		}
//------------------------------------------------------------------------
		public void Initialize(IHostObjectContract HostObj)
		{
			MView.Initialize(new CHostObjectContractToViewAddInAdapter(HostObj));
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------