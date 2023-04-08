﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace MemberInfoTest
{
//-------------------------------------------------------------------------------------------------------
	public interface IBookRetailer : IDisposable
	{
//-------------------------------------------------------------------------------------------------------
		void Purchase();
		void ApplyDiscount();
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------