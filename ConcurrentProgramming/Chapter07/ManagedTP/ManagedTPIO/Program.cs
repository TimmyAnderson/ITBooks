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
	class Program
	{
//------------------------------------------------------------------------------
		private static IntPtr							MIOBuffer;
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		private static void Alloc()
		{
			MIOBuffer=Marshal.AllocHGlobal(1024);
		}
//------------------------------------------------------------------------------
		private static void Free()
		{
			Marshal.FreeHGlobal(MIOBuffer);
		}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		private static unsafe void IOCallback(uint ErrorCode, uint NumBytes, NativeOverlapped* OP)
		{
			try
			{
				Console.WriteLine(string.Format("BEGIN - ErrorCode: [{0}], NumBytes: [{1}] !",ErrorCode,NumBytes));

				Thread.Sleep(1*1000);

				Console.WriteLine(string.Format("END - ErrorCode: [{0}], NumBytes: [{1}] !",ErrorCode,NumBytes));

				if (ErrorCode==0)
				{
					// Konvertujem smernik na byte*.
					byte*			Ptr=(byte*) MIOBuffer.ToPointer();

					// Na KONIEC streamu dat svihem '\0', kedze PtrToStringAnsi() cita z pamete AZ KYM NENAJDE '\0'.
					Ptr[NumBytes]=0;

					string			ReadData=Marshal.PtrToStringAnsi(MIOBuffer);

					Console.WriteLine(string.Format("Data read from file: [{0}] !",ReadData));
				}
			}
			finally
			{
				// Dealokujem UNSAFE pamet.
				Free();

				// Spravim UNPINNING.
				Overlapped.Unpack(OP);
				// Uvolnim strukturu NativeOverlapped.
				Overlapped.Free(OP);
			}
		}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		static unsafe void Test()
		{
			// Alokujem UNSAFE PAMET.
			Alloc();

			// Otvorim subor na citanie, pricom NASTAVIM FILE_FLAG_OVERLAPPED FLAG.
			SafeFileHandle			DeviceHandle=PInvoke.CreateFile(@"..\\..\\TEST.txt",(uint)(PInvoke.AccessRights.GENERIC_READ), (uint)(PInvoke.ShareModes.FILE_SHARE_READ), IntPtr.Zero, (uint)(PInvoke.CreationDispositions.OPEN_EXISTING), PInvoke.Overlapped, IntPtr.Zero);

			// Urobim BINDING IO s TP.
			ThreadPool.BindHandle(DeviceHandle);  

			Overlapped				OP=new Overlapped();   

			// !!! Vytvorim PINNED POINTER a ZAROVEN ASOCIUJEM CALLBACK.
			// !!! Takisto mu zaslem DATA - buffer, kde sa maju data ukladat.
			NativeOverlapped*		NO=OP.Pack(IOCallback,null);

			PInvoke.ReadFile(DeviceHandle,MIOBuffer,1024,IntPtr.Zero,NO);
		}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			Test();

			Console.WriteLine("Press any key to EXIT !");
			Console.ReadLine();
		}
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------