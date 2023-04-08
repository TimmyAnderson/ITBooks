﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.Serialization;
//-------------------------------------------------------------------------------------------------------
namespace DifferentAssembly
{
//-------------------------------------------------------------------------------------------------------
	[DataContract]
	public sealed class CDataContractDerived : CDataContractBase
	{
//-------------------------------------------------------------------------------------------------------
		private string											MLastName;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CDataContractDerived(string FirstName, string LastName)
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
			return(string.Format("First name: [{0}], Last name: [{1}]",FirstName,MLastName));
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------