using System;
using System.Collections.Generic;
using System.Text;
using System.Linq;
using Microsoft.AspNetCore.Mvc;
using Moq;
using Xunit;
using RealApplication1.Controllers;
using RealApplication1.Models;
using RealApplication1.Models.ViewModels;
//----------------------------------------------------------------------------------------------------------------------
namespace RealApplication1.Tests.Tests
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class CHomeControllerTests
	{
//----------------------------------------------------------------------------------------------------------------------
		[Fact]
		public void Can_Use_Repository()
		{
			Mock<IStoreRepository>								Mock=new Mock<IStoreRepository>();
			List<CProduct>										Products=new List<CProduct>();

			Products.Add(new CProduct(1,"P1"));
			Products.Add(new CProduct(2,"P2"));

			Mock.Setup(P => P.Products).Returns(Products.AsQueryable<CProduct>());

			HomeController										Controller=new HomeController(Mock.Object);
			CProductsListViewModel								Result=((Controller.Index() as ViewResult).ViewData.Model as CProductsListViewModel);
			CProduct[]											ProductArray=Result.Products.ToArray();

			Assert.True(ProductArray.Length==2);

			Assert.Equal("P1",ProductArray[0].Name);
			Assert.Equal("P2",ProductArray[1].Name);
		}
//----------------------------------------------------------------------------------------------------------------------
		[Fact]
		public void Can_Paginate()
		{
			Mock<IStoreRepository>								Mock=new Mock<IStoreRepository>();
			List<CProduct>										Products=new List<CProduct>();

			Products.Add(new CProduct(1,"P1"));
			Products.Add(new CProduct(2,"P2"));
			Products.Add(new CProduct(3,"P3"));
			Products.Add(new CProduct(4,"P4"));
			Products.Add(new CProduct(5,"P5"));

			Mock.Setup(P => P.Products).Returns(Products.AsQueryable<CProduct>());

			HomeController										Controller=new HomeController(Mock.Object);

			Controller.PageSize=3;

			CProductsListViewModel								Result=((Controller.Index(2) as ViewResult).ViewData.Model as CProductsListViewModel);
			CProduct[]											ProductArray=Result.Products.ToArray();

			Assert.True(ProductArray.Length==2);

			Assert.Equal("P4",ProductArray[0].Name);
			Assert.Equal("P5",ProductArray[1].Name);
		}
//----------------------------------------------------------------------------------------------------------------------
		[Fact]
		public void Can_Send_Pagination_View_Model()
		{
			Mock<IStoreRepository>								Mock=new Mock<IStoreRepository>();
			List<CProduct>										Products=new List<CProduct>();

			Products.Add(new CProduct(1,"P1"));
			Products.Add(new CProduct(2,"P2"));
			Products.Add(new CProduct(3,"P3"));
			Products.Add(new CProduct(4,"P4"));
			Products.Add(new CProduct(5,"P5"));

			Mock.Setup(P => P.Products).Returns(Products.AsQueryable<CProduct>());

			HomeController										Controller=new HomeController(Mock.Object);

			Controller.PageSize=3;

			CProductsListViewModel								Result=((Controller.Index(2) as ViewResult).ViewData.Model as CProductsListViewModel);
			CPagingInfo											PageInfo=Result.PagingInfo;

			Assert.Equal(2,PageInfo.CurrentPage);
			Assert.Equal(3,PageInfo.ItemsPerPage);
			Assert.Equal(5,PageInfo.TotalItems);
			Assert.Equal(2,PageInfo.TotalPages);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------