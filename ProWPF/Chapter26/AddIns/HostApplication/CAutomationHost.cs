using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
using System.Windows.Threading;
using System.Threading;
using System.AddIn.Hosting;
using HostView;
//------------------------------------------------------------------------
// 1. Tato trieda IMPLEMENTUJE ADDIN CALLBACK.
// 2. Prekresluje ProgressBar podla toho ako postupuje transformacia obrazku v AddIn.
//------------------------------------------------------------------------
namespace HostApplication
{
//------------------------------------------------------------------------
	public class CAutomationHost : CHostObject
	{
//------------------------------------------------------------------------
		private delegate void DDoProgress(int ProgressPercent);
//------------------------------------------------------------------------
		private ProgressBar				MProgressBar;
		private Dispatcher				MDispatcher;
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		public CAutomationHost(ProgressBar ProgressBar, Dispatcher Dispatcher)
		{
			MProgressBar=ProgressBar;
			MDispatcher=Dispatcher;
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		private void ThreadMethod(int ProgressPercent)
		{
			DDoProgress		D=delegate(int Value)
			{
				MProgressBar.Value=Value;
			};

			MDispatcher.BeginInvoke(DispatcherPriority.Send,D,ProgressPercent);
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		public override void ReportProgress(int ProgressPercent)
		{
			DDoProgress		Delegate=this.ThreadMethod;

			Delegate.BeginInvoke(ProgressPercent,null,null);
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------