﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
//----------------------------------------------------------------------------------------------------------------------
namespace ModelBinding.Model
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class CSimpleChild
	{
//----------------------------------------------------------------------------------------------------------------------
		private int												MID;
		private string											MFirstName;
		private string											MLastName;
		private int												MAge;
		private ESex											MSex;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CSimpleChild()
		{
		}
//----------------------------------------------------------------------------------------------------------------------
		public CSimpleChild(int ID, string FirstName, string LastName, int Age, ESex Sex)
		{
			MID=ID;
			MFirstName=FirstName;
			MLastName=LastName;
			MAge=Age;
			MSex=Sex;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public int												ID
		{
			get
			{
				return(MID);
			}
			set
			{
				MID=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public string											FirstName
		{
			get
			{
				return(MFirstName);
			}
			set
			{
				MFirstName=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public string											LastName
		{
			get
			{
				return(MLastName);
			}
			set
			{
				MLastName=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public int												Age
		{
			get
			{
				return(MAge);
			}
			set
			{
				MAge=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public ESex												Sex
		{
			get
			{
				return(MSex);
			}
			set
			{
				MSex=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public override string ToString()
		{
			return($"[{MFirstName}] [{MLastName}] [{MAge}] [{MSex}]");
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------