﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using RealApplication3.Models;
//----------------------------------------------------------------------------------------------------------------------
namespace RealApplication3.Components
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class CCartSummaryViewComponent : ViewComponent
	{
//----------------------------------------------------------------------------------------------------------------------
		private readonly CCart									MCart;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CCartSummaryViewComponent(CCart Cart)
		{
			MCart=Cart;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public IViewComponentResult Invoke()
		{
			IViewComponentResult								Result=View("CartSummary",MCart);

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------