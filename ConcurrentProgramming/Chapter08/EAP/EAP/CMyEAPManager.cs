using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
//------------------------------------------------------------------------
namespace EAP
{
//------------------------------------------------------------------------
	public class CMyEAPManager
	{
//------------------------------------------------------------------------
		private object						MSyn=new object();
		private Dictionary<object,CXXXData>	MD=new Dictionary<object,CXXXData>();
		private MainWindow					MW;
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		public CMyEAPManager(MainWindow W)
		{
			MW=W;
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		// !!!!! Tato funkcia je volana V THREADE GUI - cez SynchronizationContext.
		public void WindowCompletedCallback(object State)
		{
			CXXXCompletedEventArgs			CC=(CXXXCompletedEventArgs) State;

			// Vycistim Dictionary.
			MD.Remove(CC.UserState);

			// Zavolam WINDOW EVENT.
			MW.OnXXXCompleted(CC);
		}
//------------------------------------------------------------------------
		// !!!!! Tato funkcia je volana V THREADE GUI - cez SynchronizationContext.
		public void WindowProgressChangedCallback(object State)
		{
			CXXXProgressChangedEventArgs	PC=(CXXXProgressChangedEventArgs) State;

			// Zavolam WINDOW EVENT.
			MW.OnXXXProgressChanged(PC);
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		// !!!!! Tato funkcia je volana V THREADE GUI - volam ju z Window.
		public bool XXXAsync(string InputValue, object Object)
		{
			if (MD.ContainsKey(Object)==true)
				return(false);

			CXXXData						Data;
			
			Data=new CXXXData(Object,InputValue,SynchronizationContext.Current,this.WindowCompletedCallback,this.WindowProgressChangedCallback);
			MD.Add(Object,Data);

			Data.StartWork();
			return(true);
		}
//------------------------------------------------------------------------
		// !!!!! Tato funkcia je volana V THREADE GUI - volam ju z Window.
		public bool XXXCancelAsync(object Object)
		{
			if (MD.ContainsKey(Object)==false)
				return(false);

			CXXXData						Data=MD[Object];

			Data.Cancel();
			return(true);
		}
//------------------------------------------------------------------------
		// !!!!! Tato funkcia je volana V THREADE GUI - volam ju z Window.
		public bool SimulateException(object Object)
		{
			if (MD.ContainsKey(Object)==false)
				return(false);

			CXXXData						Data=MD[Object];

			Data.SimulateException();
			return(true);
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------