using System;
using System.Collections.Generic;
using System.Text;
using System.Runtime.Serialization;
//-------------------------------------------------------------------------------------------------------
namespace DCInterfaceLibrary
{
//-------------------------------------------------------------------------------------------------------
	public interface IName
	{
//-------------------------------------------------------------------------------------------------------
		[DataMember]
		string						FirstName
		{
			get;
			set;
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------