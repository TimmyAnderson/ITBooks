using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.RazorPages;
using Microsoft.AspNetCore.Routing;
using Newtonsoft.Json;
using Moq;
using Xunit;
using RealApplication4.Models;
using RealApplication4.Pages;
//----------------------------------------------------------------------------------------------------------------------
namespace RealApplication4.Tests.Tests
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class CCartPageTests
	{
//----------------------------------------------------------------------------------------------------------------------
		[Fact]
		public void Can_Load_Cart()
		{
			Mock<IStoreRepository>								Mock=new Mock<IStoreRepository>();
			List<CProduct>										Products=new List<CProduct>();
			CProduct											Product1=new CProduct(1,"P1");
			CProduct											Product2=new CProduct(2,"P2");

			Products.Add(Product1);
			Products.Add(Product2);

			Mock.Setup(P => P.Products).Returns(Products.AsQueryable<CProduct>());

			CCart												TestCart=new CCart();

			TestCart.AddItem(Product1,2);
			TestCart.AddItem(Product2,1);

			CartModel											CartModel=new CartModel(Mock.Object,TestCart);

			CartModel.OnGet("MyUrl");

			Assert.Equal(2,CartModel.Cart.Lines.Count());
			Assert.Equal("MyUrl",CartModel.ReturnUrl);
		}
//----------------------------------------------------------------------------------------------------------------------
		[Fact]
		public void Can_Update_Cart()
		{
			Mock<IStoreRepository>								Mock=new Mock<IStoreRepository>();
			List<CProduct>										Products=new List<CProduct>();

			Products.Add(new CProduct(1,"P1"));

			Mock.Setup(P => P.Products).Returns(Products.AsQueryable<CProduct>());

			CCart												TestCart=new CCart();
			CartModel											CartModel=new CartModel(Mock.Object,TestCart);

			CartModel.OnPost(1,"MyUrl");

			Assert.Single(TestCart.Lines);
			Assert.Equal("P1",TestCart.Lines.First().Product.Name);
			Assert.Equal(1,TestCart.Lines.First().Quantity);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------