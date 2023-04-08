using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;
//------------------------------------------------------------------------------------------------------
namespace CustomSafeHandle
{
//------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		[DllImport("kernel32.dll", CharSet=CharSet.Auto, CallingConvention=CallingConvention.StdCall,SetLastError=true)]
		public static extern IntPtr CreateFile(string FileName, uint DesiredAccess, uint ShareMode, IntPtr SecurityAttributes, uint CreationDisposition, uint FlagsAndAttributes, IntPtr TemplateFile);
//-------------------------------------------------------------------------------------------------------
		[DllImport("kernel32.dll",SetLastError=true)]
		static extern uint GetFileSize(IntPtr File, IntPtr FileSizeHigh);
//-------------------------------------------------------------------------------------------------------
		[DllImport("kernel32.dll", SetLastError=true)]
		static extern bool ReadFile(IntPtr File, [Out] byte[] Buffer, uint NumberOfBytesToRead, out uint NumberOfBytesRead, IntPtr Overlapped);
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
		private static void Test()
		{
			int													HR;
			string												FileName="MyFile.txt";
			IntPtr												Handle;
			CCustomSafeHandle									MySafeHandle;
			IntPtr												INVALID_HANDLE_VALUE=new IntPtr(-1);

			// !!! Priradim NATIVE HANDLE do CUSTOM SAFE HANDLE.
			MySafeHandle=new CCustomSafeHandle(Handle=CreateFile(FileName,0x80000000,0,IntPtr.Zero,0x03,0x80,IntPtr.Zero));

			if (Handle==INVALID_HANDLE_VALUE)
			{
				HR=Marshal.GetLastWin32Error();

				throw(new Exception(string.Format("Can't OPEN file [{0}], Error: [{1}] !",FileName,HR)));
			}

			uint												FileSize=GetFileSize(Handle,IntPtr.Zero);
			byte[]												FileContent=new byte[FileSize];
			uint												NumberOfReadBytes;

			if (ReadFile(Handle,FileContent,FileSize,out NumberOfReadBytes,IntPtr.Zero)==false)
			{
				HR=Marshal.GetLastWin32Error();

				throw(new Exception(string.Format("Can't READ file [{0}], Error: [{1}] !",FileName,HR)));
			}

			if (NumberOfReadBytes>0)
			{
				string											Text=UnicodeEncoding.ASCII.GetString(FileContent);

				Console.WriteLine(string.Format("BYTES READ from FILE [{0}] !",Text));
			}
			else
			{
				Console.WriteLine("BYTES was NOT READ !");
			}
		}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			try
			{
				Test();
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION [{0}] in APP DOMAIN [{1}] !",E.Message,AppDomain.CurrentDomain));
			}

			Console.WriteLine("Press any KEY to EXIT !");
			Console.ReadLine();
		}
//------------------------------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------------------------------