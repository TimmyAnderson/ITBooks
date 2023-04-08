using System;
using System.Collections.Generic;
using System.Text;
using Moq;
using Xunit;
using Microsoft.AspNetCore.Mvc;
using RealApplication3.Controllers;
using RealApplication3.Models;
//----------------------------------------------------------------------------------------------------------------------
namespace RealApplication3.Tests.Tests
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class COrderControllerTests
	{
//----------------------------------------------------------------------------------------------------------------------
		[Fact]
		public void Cannot_Checkout_Empty_Cart()
		{
			Mock<IOrderRepository>								Mock=new Mock<IOrderRepository>();
			CCart												Cart=new CCart();
			COrder												Order=new COrder();
			OrderController										Target=new OrderController(Mock.Object,Cart);
			ViewResult											Result=(Target.Checkout(Order) as ViewResult);

			Mock.Verify(P => P.SaveOrder(It.IsAny<COrder>()),Times.Never);

			Assert.True(string.IsNullOrEmpty(Result.ViewName));
			Assert.False(Result.ViewData.ModelState.IsValid);
		}
//----------------------------------------------------------------------------------------------------------------------
		[Fact]
		public void Cannot_Checkout_Invalid_ShippingDetails()
		{
			Mock<IOrderRepository>								Mock=new Mock<IOrderRepository>();
			CCart												Cart=new CCart();

			Cart.AddItem(new CProduct(),1);

			OrderController										Target=new OrderController(Mock.Object,Cart);

			Target.ModelState.AddModelError("error","There is an ERROR !");

			ViewResult											Result=(Target.Checkout(new COrder()) as ViewResult);

			Mock.Verify(P => P.SaveOrder(It.IsAny<COrder>()),Times.Never);

			Assert.True(string.IsNullOrEmpty(Result.ViewName));
			Assert.False(Result.ViewData.ModelState.IsValid);
		}
//----------------------------------------------------------------------------------------------------------------------
		[Fact]
		public void Can_Checkout_And_Submit_Order()
		{
			Mock<IOrderRepository>								Mock=new Mock<IOrderRepository>();
			CCart												Cart=new CCart();

			Cart.AddItem(new CProduct(),1);

			OrderController										Target=new OrderController(Mock.Object,Cart);
			RedirectToPageResult								Result=(Target.Checkout(new COrder()) as RedirectToPageResult);

			Mock.Verify(P => P.SaveOrder(It.IsAny<COrder>()),Times.Once);

			Assert.Equal("/Completed",Result.PageName);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------