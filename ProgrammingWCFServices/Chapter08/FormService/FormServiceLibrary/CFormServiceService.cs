using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;
using System.Windows.Forms;
using System.Runtime.Serialization;
using System.ServiceModel;
//--------------------------------------------------------------------------------------------------------------------------------
namespace FormServiceLibrary
{
//--------------------------------------------------------------------------------------------------------------------------------
	[ServiceBehavior(InstanceContextMode=InstanceContextMode.Single, UseSynchronizationContext=true)]
	public class CFormServiceService : IFormServiceContract, IDisposable
	{
//--------------------------------------------------------------------------------------------------------------------------------
		public CFormServiceService()
		{
			Console.WriteLine(CDebugHelper.GetConstructorCallString());
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
        public void IncrementLabel()
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString(1));

			Console.WriteLine(string.Format("TID - IncrementLabel(): {0} !",Thread.CurrentThread.ManagedThreadId));

			CMyForm					Form=Application.OpenForms[0] as CMyForm;

			// !!! Priame pouzitie controlu.
			Form.Counter++;

			// Tu Sleep() nemozem pouzit, pretoze TELO BEZI V THREADE GUI.
			//Thread.Sleep(3*1000);

			Console.WriteLine(CDebugHelper.GetMethodCallString(2));
		}
//--------------------------------------------------------------------------------------------------------------------------------
        public void DecrementLabel()
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString(1));

			Console.WriteLine(string.Format("TID - DecrementLabel(): {0} !",Thread.CurrentThread.ManagedThreadId));

			CMyForm					Form=Application.OpenForms[0] as CMyForm;

			// !!! Priame pouzitie controlu.
			Form.Counter--;

			// Tu Sleep() nemozem pouzit, pretoze TELO BEZI V THREADE GUI.
			//Thread.Sleep(3*1000);

			Console.WriteLine(CDebugHelper.GetMethodCallString(2));
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		public void Dispose()
		{
			Console.WriteLine(CDebugHelper.GetDestructorCallString());
		}
//--------------------------------------------------------------------------------------------------------------------------------
	}
//--------------------------------------------------------------------------------------------------------------------------------
}
//--------------------------------------------------------------------------------------------------------------------------------