﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.Serialization;
using SharedLibrary1;
//-------------------------------------------------------------------------------------------------------
namespace SharedLibrary2
{
//-------------------------------------------------------------------------------------------------------
	[DataContract]
	public class CName : CNameBase
	{
//-------------------------------------------------------------------------------------------------------
		private string											MLastName;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CName(string FirstName, string LastName)
			: base(FirstName)
		{
			MLastName=LastName;
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
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
			return(string.Format("FirstName: [{0}], LastName: [{1}]",FirstName,LastName));
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------