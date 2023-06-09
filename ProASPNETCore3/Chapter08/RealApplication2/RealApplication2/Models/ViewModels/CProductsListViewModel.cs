﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
//----------------------------------------------------------------------------------------------------------------------
namespace RealApplication2.Models.ViewModels
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class CProductsListViewModel
	{
//----------------------------------------------------------------------------------------------------------------------
		private CProduct[]										MProducts;
		private CPagingInfo										MPagingInfo;
		private string											MCurrentCategory;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CProductsListViewModel(CProduct[] Products, CPagingInfo PagingInfo, string CurrentCategory)
		{
			MProducts=Products;
			MPagingInfo=PagingInfo;
			MCurrentCategory=CurrentCategory;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CProduct[]										Products
		{
			get
			{
				return(MProducts);
			}
			set
			{
				MProducts=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public CPagingInfo										PagingInfo
		{
			get
			{
				return(MPagingInfo);
			}
			set
			{
				MPagingInfo=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public string											CurrentCategory
		{
			get
			{
				return(MCurrentCategory);
			}
			set
			{
				MCurrentCategory=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------