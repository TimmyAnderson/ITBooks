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
using RealApplication2.Models;
using RealApplication2.Pages;
//----------------------------------------------------------------------------------------------------------------------
namespace RealApplication2.Tests.Tests
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class CCartPageTests
	{
//----------------------------------------------------------------------------------------------------------------------
		private CCart CreateCart(byte[] Value)
		{
			CCart												TestCart=JsonConvert.DeserializeObject<CCart>(Encoding.UTF8.GetString(Value));

			return(TestCart);
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
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

			Mock<ISession>										MockSession=new Mock<ISession>();
			byte[]												Data=Encoding.UTF8.GetBytes(JsonConvert.SerializeObject(TestCart));

			MockSession.Setup(P => P.TryGetValue(It.IsAny<string>(),out Data));

			Mock<HttpContext>									MockContext=new Mock<HttpContext>();

			MockContext.SetupGet(P => P.Session).Returns(MockSession.Object);

			CartModel											CartModel=new CartModel(Mock.Object);
			RouteData											RouteData=new RouteData();
			PageActionDescriptor								PageActionDescriptor=new PageActionDescriptor();
			ActionContext										ActionContext=new ActionContext(MockContext.Object,RouteData,PageActionDescriptor);

			CartModel.PageContext=new PageContext(ActionContext);

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
			Mock<ISession>										MockSession=new Mock<ISession>();

			MockSession.Setup(P => P.Set(It.IsAny<string>(),It.IsAny<byte[]>())).Callback<string,byte[]>((Key,Value) => {TestCart=CreateCart(Value);});

			Mock<HttpContext>									MockContext=new Mock<HttpContext>();

			MockContext.SetupGet(P => P.Session).Returns(MockSession.Object);

			CartModel											CartModel=new CartModel(Mock.Object);
			RouteData											RouteData=new RouteData();
			PageActionDescriptor								PageActionDescriptor=new PageActionDescriptor();
			ActionContext										ActionContext=new ActionContext(MockContext.Object,RouteData,PageActionDescriptor);

			CartModel.PageContext=new PageContext(ActionContext);

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