using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.AddIn.Contract;
using System.AddIn.Pipeline;
//------------------------------------------------------------------------
// 1. Callback interface.
// 2. Pomocou neho bude AddIn informovat aplikaciu o progrese pri transformacii obrazu.
//------------------------------------------------------------------------
namespace Contract
{
//------------------------------------------------------------------------
	public interface IHostObjectContract : IContract
	{
//------------------------------------------------------------------------
		void ReportProgress(int ProgressPercent);
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------