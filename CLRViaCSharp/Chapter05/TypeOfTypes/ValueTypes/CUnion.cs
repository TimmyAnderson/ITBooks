﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;
//-------------------------------------------------------------------------------------------------------
namespace ValueTypes
{
//-------------------------------------------------------------------------------------------------------
	// Trieda simuluje C++ UNION.
	[StructLayout(LayoutKind.Explicit)]
	public struct CUnion
	{
//-------------------------------------------------------------------------------------------------------
		// MInt je ulozeny na OFFSET 0.
		[FieldOffset(0)]
		private int												MInt;
		// MByte1 je ulozeny na OFFSET 0.
		[FieldOffset(0)]
		private byte											MByte1;
		// MByte1 je ulozeny na OFFSET 1.
		[FieldOffset(1)]
		private byte											MByte2;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CUnion(byte Byte1, byte Byte2)
		{
			MInt=0;
			MByte1=0;
			MByte2=0;

			MByte1=Byte1;
			MByte2=Byte2;
		}
//-------------------------------------------------------------------------------------------------------
		public CUnion(int Int)
		{
			MInt=0;
			MByte1=0;
			MByte2=0;

			MInt=Int;
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public int												Int
		{
			get
			{
				return(MInt);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public byte												Byte1
		{
			get
			{
				return(MByte1);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public byte												Byte2
		{
			get
			{
				return(MByte2);
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public override string ToString()
		{
			return(string.Format("Int: [{0}], Byte1: [{1}], Byte2: [{2}]",MInt,MByte1,MByte2));
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------