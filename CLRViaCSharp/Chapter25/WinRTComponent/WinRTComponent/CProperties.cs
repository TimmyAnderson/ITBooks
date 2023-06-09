﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
//-------------------------------------------------------------------------------------------------------
namespace WinRTComponent
{
//-------------------------------------------------------------------------------------------------------
	public sealed class CProperties
	{
//-------------------------------------------------------------------------------------------------------
		private int												MField1=100;
		private Stream											MField2=null;
		private string											MField3=null;
		private object											MField4=null;
		private int												MField5=100;
		private int												MField6=100;
		private int[]											MField7=new int[100];
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public int												Property1
		{
			get
			{
				return(MField1);
			}
			set
			{
				MField1=value;
			}
		}
//-------------------------------------------------------------------------------------------------------
		/*
		// WinRT COMPONENTS mozu pouzivat iba WinRT COMPATIBLE TYPES.
		public Stream											Property2
		{
			get
			{
				return(MField2);
			}
			set
			{
				MField2=value;
			}
		}
		*/
//-------------------------------------------------------------------------------------------------------
		public string											Property3
		{
			get
			{
				return(MField3);
			}
			set
			{
				MField3=value;
			}
		}
//-------------------------------------------------------------------------------------------------------
		public object											Property4
		{
			get
			{
				return(MField4);
			}
			set
			{
				MField4=value;
			}
		}
//-------------------------------------------------------------------------------------------------------
		/*
		// WinRT COMPONENTS NESMU definovat WRITE-ONLY PROPERTIES.
		public int												Property5
		{
			set
			{
				MField5=value;
			}
		}
		*/
//-------------------------------------------------------------------------------------------------------
		public int												Property6
		{
			get
			{
				return(MField6);
			}
		}
//-------------------------------------------------------------------------------------------------------
		/*
		// WinRT COMPONENTS NESMU definovat PARAMETRICKE PROPERTIES (INDEXERS).
		public int												this[int Index]
		{
			get
			{
				return(MField7[Index]);
			}
			set
			{
				MField7[Index]=value;
			}
		}
		*/
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public override string ToString()
		{
			string												Text=string.Format("FIELD 1 [{0}], FIELD 2 [{1}], FIELD 3 [{2}], FIELD 4 [{3}], FIELD 5 [{4}], FIELD 6 [{5}], FIELD 7 [{6}] !",MField1,MField2,MField3,MField4,MField5,MField6,MField7);

			return(Text);
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------