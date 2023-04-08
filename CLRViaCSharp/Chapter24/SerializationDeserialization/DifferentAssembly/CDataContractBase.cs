﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.Serialization;
//-------------------------------------------------------------------------------------------------------
namespace DifferentAssembly
{
//-------------------------------------------------------------------------------------------------------
	[KnownType(typeof(CDataContractDerived))]
	[DataContract]
	public class CDataContractBase
	{
//-------------------------------------------------------------------------------------------------------
		private string											MFirstName;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CDataContractBase(string FirstName)
		{
			MFirstName=FirstName;
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
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------