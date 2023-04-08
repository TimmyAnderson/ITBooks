﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
//-----------------------------------------------------------------------------
namespace RealApplication1.Models.ViewModels
{
//-----------------------------------------------------------------------------
	public sealed class CPagingInfo
	{
//-----------------------------------------------------------------------------
		private int												MTotalItems;
		private int												MItemsPerPage;
		private int												MCurrentPage;
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
		public CPagingInfo()
		{
		}
//-----------------------------------------------------------------------------
		public CPagingInfo(int TotalItems, int ItemsPerPage, int CurrentPage)
		{
			MTotalItems=TotalItems;
			MItemsPerPage=ItemsPerPage;
			MCurrentPage=CurrentPage;
		}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
		public int												TotalItems
		{
			get
			{
				return(MTotalItems);
			}
			set
			{
				MTotalItems=value;
			}
		}
//-----------------------------------------------------------------------------
		public int												ItemsPerPage
		{
			get
			{
				return(MItemsPerPage);
			}
			set
			{
				MItemsPerPage=value;
			}
		}
//-----------------------------------------------------------------------------
		public int												CurrentPage
		{
			get
			{
				return(MCurrentPage);
			}
			set
			{
				MCurrentPage=value;
			}
		}
//-----------------------------------------------------------------------------
		public int												TotalPages
		{
			get
			{
				return((int) Math.Ceiling((((decimal) TotalItems)/((decimal) ItemsPerPage))));
			}
		}
//-----------------------------------------------------------------------------
	}
//-----------------------------------------------------------------------------
}
//-----------------------------------------------------------------------------