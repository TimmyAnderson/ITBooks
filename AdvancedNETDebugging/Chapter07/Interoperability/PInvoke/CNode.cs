﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;
//-------------------------------------------------------------------------------------------------------
namespace PInvoke
{
//-------------------------------------------------------------------------------------------------------
	[StructLayout(LayoutKind.Sequential, CharSet=CharSet.Ansi)]
	public class CNode
	{
//-------------------------------------------------------------------------------------------------------
            public string										First;
            public string										Last;
            public string										Social;
            public uint											Age;
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------