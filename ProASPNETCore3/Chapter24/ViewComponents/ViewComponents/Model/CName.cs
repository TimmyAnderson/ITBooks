﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
//----------------------------------------------------------------------------------------------------------------------
namespace ViewComponents.Model
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class CName
	{
//----------------------------------------------------------------------------------------------------------------------
		private int												MID;
		private string											MFirstName;
		private string											MLastName;
		private int												MAge;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CName()
		{
		}
//----------------------------------------------------------------------------------------------------------------------
		public CName(int ID, string FirstName, string LastName, int Age)
		{
			MID=ID;
			MFirstName=FirstName;
			MLastName=LastName;
			MAge=Age;
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
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public override string ToString()
		{
			return($"[{MFirstName}] [{MLastName}] [{MAge}]");
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------