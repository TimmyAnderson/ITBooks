using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Diagnostics;
using System.Runtime.InteropServices;
using System.Runtime.ConstrainedExecution;
//-------------------------------------------------------------------------------------------------------
namespace FinalizerTest
{
//-------------------------------------------------------------------------------------------------------
	// Zdedenie z CriticalFinalizerObject zabezpecuje, ze sa robi DOPREDNA JIT kompilacia objektov implementujucich tuto CLASS, ako aj spustenie METHOD Finalize() AZ KED sa vyvolaju Finalize() METHODS tych OBJECTS, ktore NEDEDIA z CLASS CriticalFinalizerObject.
	public class CFileAsCriticalFinalizerObject : CriticalFinalizerObject, IDisposable
	{
//-------------------------------------------------------------------------------------------------------
		[DllImport("kernel32.dll", CharSet=CharSet.Auto, CallingConvention=CallingConvention.StdCall,SetLastError=true)]
		public static extern IntPtr CreateFile(string lpFileName, uint dwDesiredAccess, uint dwShareMode, IntPtr SecurityAttributes, uint dwCreationDisposition, uint dwFlagsAndAttributes, IntPtr hTemplateFile);
//-------------------------------------------------------------------------------------------------------
		[DllImport("kernel32.dll",SetLastError=true)]
		static extern uint GetFileSize(IntPtr hFile, IntPtr lpFileSizeHigh);
//-------------------------------------------------------------------------------------------------------
		[DllImport("kernel32.dll", SetLastError=true)]
		static extern bool ReadFile(IntPtr hFile, [Out] byte[] lpBuffer, uint nNumberOfBytesToRead, out uint lpNumberOfBytesRead, IntPtr lpOverlapped);
//-------------------------------------------------------------------------------------------------------
		[DllImport("kernel32.dll", SetLastError=true)]
		[return: MarshalAs(UnmanagedType.Bool)]
		static extern bool CloseHandle(IntPtr hObject);
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		private static IntPtr									INVALID_HANDLE_VALUE=new IntPtr(-1);
//-------------------------------------------------------------------------------------------------------
		private bool											MDisposed;
		private IntPtr											MFileHandle;
		private string											MFileName;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CFileAsCriticalFinalizerObject(string FileName)
		{
			if (FileName==null)
			{
				throw(new Exception("FileName was NOT DEFINED !"));
			}

			MDisposed=false;
			MFileHandle=INVALID_HANDLE_VALUE;
			MFileName=FileName;
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		// FINALIZER.
		~CFileAsCriticalFinalizerObject()
		{
			Dispose(false);

			// Iba aby bolo vidiet, ze sa volal FINALIZER.
			Thread.Sleep(1000);
		}
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
		protected virtual void Dispose(bool IsDisposing)
		{
			if (IsDisposing==true)
			{
				// !!! Kedze sa robi DISPOSING, tak JE MOZNE pristupovat k REFERENCNYM PREMENNYM.
				MFileName=null;
				WriteLog("Object DISPOSING !");
			}
			else
			{
				// !!! Ked robim FINALIZING tak NESMIEM PRISTUPOVAT k FIELDS, ktore su REFERENCE TYPE, pretoze tieto uz MOHLI BYT FINALIZOVANE.
				WriteLog("Object FINALIZING !");
			}

			// !!! Musim pridat podmienku i na IntPtr.Zero, pretoze ak by v KONSTRUKTORE bola hodena EXCEPTION, tak by MFileHandle bola nastavena na IntPtr.Zero.
			if (MFileHandle!=INVALID_HANDLE_VALUE && MFileHandle!=IntPtr.Zero)
			{
				CloseHandle(MFileHandle);
				MFileHandle=INVALID_HANDLE_VALUE;
				WriteLog("Object CLOSED !");
			}

			// Objekt bol UVOLNENY (ci uz cez Dispose(), alebo Finalize()) a uz Finalize() NEMUSI byt viac volana.
			GC.SuppressFinalize(this);
			MDisposed=true;
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void OpenFile()
		{
			if (MDisposed==true)
			{
				throw(new ObjectDisposedException("Object was already DISPOSED !"));
			}

			int													HR;

			if ((MFileHandle=CreateFile(MFileName,0x80000000,0,IntPtr.Zero,0x03,0x80,IntPtr.Zero))==INVALID_HANDLE_VALUE)
			{
				HR=Marshal.GetLastWin32Error();
				throw(new Exception(string.Format("Can't OPEN file [{0}], Error: [{1}] !",MFileName,HR)));
			}
		}
//-------------------------------------------------------------------------------------------------------
		public string ReadAllContent()
		{
			if (MDisposed==true)
			{
				throw(new ObjectDisposedException("Object was already DISPOSED !"));
			}

			int													HR;
			uint												FileSize=GetFileSize(MFileHandle,IntPtr.Zero);
			byte[]												FileContent=new byte[FileSize];
			uint												NumberOfReadBytes;

			if (ReadFile(MFileHandle,FileContent,FileSize,out NumberOfReadBytes,IntPtr.Zero)==false)
			{
				HR=Marshal.GetLastWin32Error();
				throw(new Exception(string.Format("Can't READ file [{0}], Error: [{1}] !",MFileName,HR)));
			}

			if (NumberOfReadBytes>0)
			{
				string											ReturnValue=UnicodeEncoding.ASCII.GetString(FileContent);

				return(ReturnValue);
			}
			else
			{
				return(null);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public void Close()
		{
			Dispose(true);
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