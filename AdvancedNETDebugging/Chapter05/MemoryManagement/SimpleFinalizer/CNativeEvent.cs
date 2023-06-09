﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;
//-------------------------------------------------------------------------------------------------------
namespace SimpleFinalizer
{
//-------------------------------------------------------------------------------------------------------
	public class CNativeEvent
	{
//-------------------------------------------------------------------------------------------------------
        [DllImport("kernel32.dll")]
        static extern IntPtr CreateEvent(IntPtr EventAttributes, bool ManualReset, bool InitialState, string Name); 
        [DllImport("kernel32.dll")]
        static extern IntPtr CloseHandle(IntPtr Handle); 
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		private IntPtr											MNativeHandle;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CNativeEvent(string Name)
		{
			MNativeHandle=CreateEvent(IntPtr.Zero,false,true,Name);
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		// Finalizer.
		~CNativeEvent()
		{
			if (MNativeHandle!=IntPtr.Zero)
			{
				CloseHandle(MNativeHandle);
				MNativeHandle=IntPtr.Zero;
			}
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------