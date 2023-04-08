﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace Optimizations
{
//-------------------------------------------------------------------------------------------------------
	public enum ERegister
	{
//-------------------------------------------------------------------------------------------------------
		E_R_EAX=1,
		E_R_EBX=2,
		E_R_ECX=3,
		E_R_EDX=4,
		E_R_EBP=5,
		E_R_ESP=6,
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
	public static class CRegisterExtensions
	{
//-------------------------------------------------------------------------------------------------------
		public static string EXT_GetRegisterName(this ERegister Value)
		{
			if (Value==ERegister.E_R_EAX)
			{
				return("EAX");
			}
			else if (Value==ERegister.E_R_EBX)
			{
				return("EBX");
			}
			else if (Value==ERegister.E_R_ECX)
			{
				return("ECX");
			}
			else if (Value==ERegister.E_R_EDX)
			{
				return("EDX");
			}
			else if (Value==ERegister.E_R_EBP)
			{
				return("EBP");
			}
			else if (Value==ERegister.E_R_ESP)
			{
				return("ESP");
			}
			else
			{
				throw(new CCompilerException(string.Format("INVALID VALUE of REGISTER !")));
			}
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------