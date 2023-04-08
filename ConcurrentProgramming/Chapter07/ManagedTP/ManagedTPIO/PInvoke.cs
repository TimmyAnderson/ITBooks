using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Runtime.InteropServices;
using Microsoft.Win32.SafeHandles;
//------------------------------------------------------------------------------
namespace ManagedTPIO
{
//------------------------------------------------------------------------------
	static public class PInvoke
	{
//------------------------------------------------------------------------------
		public const uint				Overlapped=0x40000000;
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		[ Flags ]
		public enum AccessRights : uint
		{
			GENERIC_READ = (0x80000000),
			GENERIC_WRITE = (0x40000000),
			GENERIC_EXECUTE = (0x20000000),
			GENERIC_ALL = (0x10000000)
		}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		[ Flags ]
		public enum ShareModes : uint
		{
			FILE_SHARE_READ = 0x00000001,
			FILE_SHARE_WRITE = 0x00000002,
			FILE_SHARE_DELETE = 0x00000004 
		}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		public enum CreationDispositions
		{
			CREATE_NEW = 1,
			CREATE_ALWAYS = 2,
			OPEN_EXISTING = 3,
			OPEN_ALWAYS = 4,
			TRUNCATE_EXISTING = 5
		}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		[DllImport("kernel32.dll", CharSet=CharSet.Unicode, SetLastError=true)]
		public static extern SafeFileHandle CreateFile(string FileName, uint DesiredAccess, uint ShareMode, IntPtr SecurityAttributes, uint CreationDisposition, uint FlagsAndAttributes, IntPtr TemplateFile);
//------------------------------------------------------------------------------
		[DllImport("kernel32.dll", CharSet=CharSet.Unicode, SetLastError=true)]
		public static extern void CloseHandle(SafeHandle Handle);
//------------------------------------------------------------------------------
		[DllImport("kernel32.dll", CharSet=CharSet.Unicode, SetLastError=true)]
		public static unsafe extern bool ReadFile(SafeFileHandle File, IntPtr Buffer, int NumberOfBytesToRead, IntPtr NumberOfBytesRead, NativeOverlapped *Overlapped);
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------