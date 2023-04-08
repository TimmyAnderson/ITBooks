using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Diagnostics;
using System.Threading;
//-------------------------------------------------------------------------------------------------------
namespace ObjectDisposing
{
//-------------------------------------------------------------------------------------------------------
	public struct CDisposableStruct : IDisposable
	{
//-------------------------------------------------------------------------------------------------------
		private bool											MDisposed;
		private Mutex											MMutex;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CDisposableStruct(string Text)
		{
			Console.WriteLine(Text);

			MDisposed=false;
			MMutex=new Mutex();
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		/*
		// VALUE TYPES NEMOZU MAT Finalize() metody - co je logicke, pretoze nie su alokovane na HEAP.
		~CDisposableStruct()
		{
			Dispose(false);
		}
		*/
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		private void WriteLog(string Text)
		{
			Console.WriteLine(Text);
			Debug.WriteLine(Text);
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		private void Dispose(bool IsDisposing)
		{
			if (IsDisposing==true)
			{
				// !!! Kedze sa robi DISPOSING, tak JE MOZNE pristupovat k REFERENCNYM PREMENNYM.
				WriteLog("Object DISPOSING !");
			}
			else
			{
				// !!! Ked robim FINALIZING tak NESMIEM PRISTUPOVAT k FIELDS, ktore su REFERENCE TYPE, pretoze tieto uz MOHLI BYT FINALIZOVANE.
				WriteLog("Object FINALIZING !");
			}

			if (MMutex!=null)
			{
				MMutex.Close();
				WriteLog("Object CLOSED !");
			}

			// Objekt bol UVOLNENY (ci uz cez Dispose(), alebo Finalize()) a uz Finalize() NEMUSI byt viac volana.
			GC.SuppressFinalize(this);
			MDisposed=true;
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void WaitOne(int Timeout)
		{
			if (MDisposed==true)
			{
				throw(new ObjectDisposedException("Object was already DISPOSED !"));
			}

			MMutex.WaitOne(Timeout);
			Console.WriteLine("Mutex LOCKED !");
		}
//-------------------------------------------------------------------------------------------------------
		public void ReleaseMutex()
		{
			if (MDisposed==true)
			{
				throw(new ObjectDisposedException("Object was already DISPOSED !"));
			}

			MMutex.ReleaseMutex();
			Console.WriteLine("Mutex UNLOCKED !");
		}
//-------------------------------------------------------------------------------------------------------
		public void Dispose()
		{
			Dispose(true);
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------