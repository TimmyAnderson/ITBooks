using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using RealApplication4.Models;
using RealApplication4.Models.ViewModels;
//----------------------------------------------------------------------------------------------------------------------
namespace RealApplication4.Controllers
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class OrderController : Controller
	{
//----------------------------------------------------------------------------------------------------------------------
		private readonly IOrderRepository						MRepository;
		private readonly CCart									MCart;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public OrderController(IOrderRepository Repository, CCart Cart)
		{
			MRepository=Repository;
			MCart=Cart;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public IActionResult Checkout()
		{
			COrder												Model=new COrder();
			IActionResult										Result=View("Checkout",Model);

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		[HttpPost]
		public IActionResult Checkout(COrder Order)
		{
			if (MCart.Lines.Count()==0)
			{
				ModelState.AddModelError("","Sorry, your cart is empty!");
			}

			if (ModelState.IsValid==true)
			{
				Order.Lines=MCart.Lines.ToArray();

				MRepository.SaveOrder(Order);

				MCart.Clear();

				IActionResult									Result=RedirectToPage("/Completed",new {OrderID=Order.OrderID});

				return(Result);
			}
			else
			{
				IActionResult									Result=View();

				return(Result);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------