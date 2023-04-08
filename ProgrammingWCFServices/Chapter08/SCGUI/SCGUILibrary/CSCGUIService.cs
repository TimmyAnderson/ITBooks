using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;
using System.Windows.Forms;
using System.Runtime.Serialization;
using System.ServiceModel;
//-------------------------------------------------------------------------------------------------------
namespace SCGUILibrary
{
//-------------------------------------------------------------------------------------------------------
	[ServiceBehavior(InstanceContextMode=InstanceContextMode.PerCall)]
	public class CSCGUIService : ISCGUIContract, IDisposable
	{
//-------------------------------------------------------------------------------------------------------
		public CSCGUIService()
		{
			Console.WriteLine(CDebugHelper.GetConstructorCallString());
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
        public void IncrementLabel()
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString(1));

			Console.WriteLine(string.Format("TID - IncrementLabel(): {0} !",Thread.CurrentThread.ManagedThreadId));

			CMyForm					Form=Application.OpenForms[0] as CMyForm;

			SendOrPostCallback		Callback=delegate
                                    {
										Console.WriteLine(string.Format("TID - Callback(): {0} !",Thread.CurrentThread.ManagedThreadId));
										Form.Counter++;
                                    };

			Form.MySynchronizationContext.Send(Callback,null);

			Console.WriteLine(CDebugHelper.GetMethodCallString(2));
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void Dispose()
		{
			Console.WriteLine(CDebugHelper.GetDestructorCallString());
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------