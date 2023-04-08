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
	// CUSTOM SAFE HANDLE MUSI dedit z SafeHandle.
	// !!! Kedze SafeHandle dedi z CriticalFinalizerObject, tak	jeho FINALIZER je realizovany ako CRITICAL FINALIZER.
	public sealed class CCustomSafeHandle : SafeHandle
	{
//------------------------------------------------------------------------------------------------------
		[DllImport("kernel32.dll")]
		private static extern bool CloseHandle(IntPtr Handle);
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
		public CCustomSafeHandle(IntPtr NativeHandle)
			: base(NativeHandle,true)
		{
		}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
		// !!!!! PROPERTY je volana v CONSTRAINED EXECUTION REGION a preto NESMIE jej kod ALOKOVAT ZIADNU MEMORY.
		public override bool									IsInvalid
		{
			get
			{
				if (base.handle==new IntPtr(-1))
				{
					return(true);
				}
				else if (base.handle==IntPtr.Zero)
				{
					return(true);
				}
				else
				{
					return(false);
				}
			}
		}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
		// !!!!! METHOD je volana v CONSTRAINED EXECUTION REGION a preto NESMIE jej kod ALOKOVAT ZIADNU MEMORY.
		protected override bool ReleaseHandle()
		{
			// !!! Uvolni HANDLE volanim FUNCTION CloseHandle().	
			bool												ReturnValue=CloseHandle(base.handle);

			// ????? NEVIEM ci nahodou Console.WriteLine() NEALOKUJE MEMORY a tym padom sa NESMIE VOLAT v ReleaseHandle(), kedze ten je vykonavany v CONSTRAINED EXECUTION REGION.
			Console.WriteLine("HANDLE was RELEASED !");

			return(ReturnValue);
		}
//------------------------------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------------------------------