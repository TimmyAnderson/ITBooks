﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
//----------------------------------------------------------------------------------------------------------------------
namespace RealApplication5.Models
{
//----------------------------------------------------------------------------------------------------------------------
	public interface IStoreRepository
	{
//----------------------------------------------------------------------------------------------------------------------
		IQueryable<CProduct>									Products
		{
			get;
		}
//----------------------------------------------------------------------------------------------------------------------
		void CreateProduct(CProduct Product);
		void DeleteProduct(CProduct Product);
		void SaveProduct(CProduct Product);
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------