﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
//-------------------------------------------------------------------------------------------------------
namespace PEVerifierSafe
{
//-------------------------------------------------------------------------------------------------------
	public interface IMyGenericInterface<TGenericType>
	{
//-------------------------------------------------------------------------------------------------------
		TGenericType											SomeProperty
		{
			get;
			set;
		}
//-------------------------------------------------------------------------------------------------------
		void SomeMethod(TGenericType Param);
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------