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
	// Dedim zo SafeHandle, ktory umoznuje bezpecnym sposobom pracovat s WINAPI HANDLES.
	public class CFileAsSafeHandle : SafeHandle
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
		private string											MFileName;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CFileAsSafeHandle(string FileName)
			: base(IntPtr.Zero,true)
		{
			if (FileName==null)
			{
				throw(new Exception("FileName was NOT DEFINED !"));
			}

			MDisposed=false;
			MFileName=FileName;
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public override bool									IsInvalid
		{
			get
			{
				if (handle==IntPtr.Zero || handle==INVALID_HANDLE_VALUE)
				{
					return(true);
				}
				else
				{
					return(false);
				}
			}
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
		// !!! METHOD musi uvolnit UNMANAGED HANDLE.
		protected override bool ReleaseHandle()
		{
			if (IsInvalid==false)
			{
				CloseHandle(base.handle);

				WriteLog("HANDLE CLOSED !");

				// Aby bolo vidiet text na CONSOLE pri ukonceni programu.
				Thread.Sleep(1000);

				return(true);
			}
			else
			{
				WriteLog("HANDLE WAS ALREADY CLOSED !");

				// Aby bolo vidiet text na CONSOLE pri ukonceni programu.
				Thread.Sleep(1000);

				return(false);
			}
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

			if ((handle=CreateFile(MFileName,0x80000000,0,IntPtr.Zero,0x03,0x80,IntPtr.Zero))==INVALID_HANDLE_VALUE)
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
			uint												FileSize=GetFileSize(handle,IntPtr.Zero);
			byte[]												FileContent=new byte[FileSize];
			uint												NumberOfReadBytes;

			if (ReadFile(handle,FileContent,FileSize,out NumberOfReadBytes,IntPtr.Zero)==false)
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
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------