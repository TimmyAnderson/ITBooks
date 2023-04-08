﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
//----------------------------------------------------------------------------------------------------------------------
namespace RealApplication4.Models
{
//----------------------------------------------------------------------------------------------------------------------
	public interface IOrderRepository
	{
//----------------------------------------------------------------------------------------------------------------------
        IQueryable<COrder>										Orders
		{
			get;
		}
//----------------------------------------------------------------------------------------------------------------------
        void SaveOrder(COrder Order);
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------