using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.AspNetCore.Mvc.Rendering;
using Microsoft.AspNetCore.Mvc.ViewComponents;
using Microsoft.AspNetCore.Routing;
using Moq;
using Xunit;
using RealApplication3.Components;
using RealApplication3.Models;
//----------------------------------------------------------------------------------------------------------------------
namespace RealApplication3.Tests.Tests
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class CNavigationMenuViewComponentTests
	{
//----------------------------------------------------------------------------------------------------------------------
		[Fact]
		public void Can_Select_Categories()
		{
			Mock<IStoreRepository>								Mock=new Mock<IStoreRepository>();
			List<CProduct>										Products=new List<CProduct>();

			Products.Add(new CProduct(1,"P1","Apples"));
			Products.Add(new CProduct(2,"P2","Apples"));
			Products.Add(new CProduct(3,"P3","Plums"));
			Products.Add(new CProduct(4,"P4","Oranges"));

			Mock.Setup(P => P.Products).Returns(Products.AsQueryable<CProduct>());

			CNavigationMenuViewComponent						Target=new CNavigationMenuViewComponent(Mock.Object);
			string[]											Results=((string[])(Target.Invoke() as ViewViewComponentResult).ViewData.Model);

			Assert.True(Enumerable.SequenceEqual(new string[]{"Apples","Oranges","Plums"},Results));
		}
//----------------------------------------------------------------------------------------------------------------------
		[Fact]
		public void Indicates_Selected_Category()
		{
			string												CategoryToSelect="Apples";
			Mock<IStoreRepository>								Mock=new Mock<IStoreRepository>();
			List<CProduct>										Products=new List<CProduct>();

			Products.Add(new CProduct(1,"P1","Apples"));
			Products.Add(new CProduct(4,"P2","Oranges"));

			Mock.Setup(P => P.Products).Returns(Products.AsQueryable<CProduct>());

			CNavigationMenuViewComponent						Target=new CNavigationMenuViewComponent(Mock.Object);

			Target.ViewComponentContext=new ViewComponentContext();
			Target.ViewComponentContext.ViewContext=new ViewContext();
			Target.ViewComponentContext.ViewContext.RouteData=new RouteData();

			Target.RouteData.Values["Category"]=CategoryToSelect;

			string												Result=((string)(Target.Invoke() as ViewViewComponentResult).ViewData["SelectedCategory"]);

			Assert.Equal(CategoryToSelect,Result);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------