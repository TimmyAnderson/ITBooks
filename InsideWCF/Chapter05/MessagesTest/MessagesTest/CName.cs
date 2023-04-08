﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.Serialization;
//-------------------------------------------------------------------------------------------------------
namespace MessagesTest
{
//-------------------------------------------------------------------------------------------------------
	[DataContract]
	public class CName
	{
//-------------------------------------------------------------------------------------------------------
		private string											MFirstName;
		private string											MLastName;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CName(string FirstName, string LastName)
		{
			MFirstName=FirstName;
			MLastName=LastName;
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		[DataMember]
		public string											FirstName
		{
			get
			{
				return(MFirstName);
			}
			private set
			{
				MFirstName=value;
			}
		}
//-------------------------------------------------------------------------------------------------------
		[DataMember]
		public string											LastName
		{
			get
			{
				return(MLastName);
			}
			private set
			{
				MLastName=value;
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public override string ToString()
		{
			return(string.Format("{0} {1}",MFirstName,MLastName));
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------