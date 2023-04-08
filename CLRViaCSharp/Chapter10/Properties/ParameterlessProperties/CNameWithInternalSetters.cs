﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.CompilerServices;
//-------------------------------------------------------------------------------------------------------
namespace ParameterlessProperties
{
//-------------------------------------------------------------------------------------------------------
	public class CNameWithInternalSetters
	{
//-------------------------------------------------------------------------------------------------------
		private string											MFirstName;
		private string											MLastName;
		private int												MAge;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CNameWithInternalSetters()
		{
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public string											FirstName
		{
			get
			{
				return(MFirstName);
			}
			internal set
			{
				MFirstName=value;
			}
		}
//-------------------------------------------------------------------------------------------------------
		public string											LastName
		{
			get
			{
				return(MLastName);
			}
			internal set
			{
				MLastName=value;
			}
		}
//-------------------------------------------------------------------------------------------------------
		public int												Age
		{
			get
			{
				return(MAge);
			}
			internal set
			{
				if (value>0)
				{
					MAge=value;
				}
				else
				{
					throw(new Exception("Age must be POSITIVE value !"));
				}
			}
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------