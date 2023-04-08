using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.AddIn.Pipeline;
using Contract;
using HostView;
//------------------------------------------------------------------------
// 1. V projekte je nastavena referencia na HostView.DLL a Contract.DLL pricom Copy Local MUSI BYT NASTAVENY NA FALSE.
// 2. HostAdapter sluzi na prepojenie ViewHost a Contract.
// 3. Trieda MUSI mat konstruktor, ktory ma ako parameter Contract interface.
// 3. ContractHandle sluzi na uchovanie instancie Contractu, INAK BY HNED PO SKONCENI KONSTRUKTROA BOL OBJEKT CONTRACTU ZLIKVIDOVANY.
//------------------------------------------------------------------------
namespace HostSideAdapter
{
//------------------------------------------------------------------------
	[HostAdapter]
	public class CImageProcessorContractToViewHostAdapter : CImageProcessorHostView
	{
//------------------------------------------------------------------------
		private IImageProcessorContract			MContract;
		// Sluzi na uchovanie instancie Contractu.
		private ContractHandle					MContractHandle;
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		public CImageProcessorContractToViewHostAdapter(IImageProcessorContract Contract)
		{
			MContract=Contract;
			MContractHandle=new ContractHandle(Contract);
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		public override byte[] ProcessImageBytes(byte[] Pixels)
		{
			// Robim forwarding z View na Contract.
			return(MContract.ProcessImageBytes(Pixels));
		}
//------------------------------------------------------------------------
		public override void Initialize(CHostObject Host)
		{
			CHostObjectViewToContractHostAdapter	HostAdapter=new CHostObjectViewToContractHostAdapter(Host);

			MContract.Initialize(HostAdapter);
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------