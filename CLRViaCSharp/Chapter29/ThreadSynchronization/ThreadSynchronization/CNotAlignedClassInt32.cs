﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;
//-------------------------------------------------------------------------------------------------------
namespace ThreadSynchronization
{
//-------------------------------------------------------------------------------------------------------
	[StructLayout(LayoutKind.Explicit)]
	public class CNotAlignedClassInt32
	{
//-------------------------------------------------------------------------------------------------------
		[FieldOffset(1)]
		public int												MValue1;
		[FieldOffset(13)]
		public int												MValue2;
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------