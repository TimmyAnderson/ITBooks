﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
//-------------------------------------------------------------------------------------------------------
namespace MembersDemo
{
//-------------------------------------------------------------------------------------------------------
	public sealed class COuterClass
	{
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public sealed class CInnerClass
		{
//-------------------------------------------------------------------------------------------------------
			private COuterClass									MOuterClass;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
			public CInnerClass(COuterClass OuterClass)
			{
				MOuterClass=OuterClass;
			}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
			public void ChangeValue(string NewValue)
			{
				// !!!!! NESTED CLASSES mozu pristupovat k PRIVATE MEMBERS OUTER CLASSES.
				MOuterClass.MValue=NewValue;
			}
//-------------------------------------------------------------------------------------------------------
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		private string											MValue;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public COuterClass(string Value)
		{
			MValue=Value;
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public string											Value
		{
			get
			{
				return(MValue);
			}
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------