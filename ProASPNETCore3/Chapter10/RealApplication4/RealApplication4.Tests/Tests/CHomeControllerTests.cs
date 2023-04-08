using System;
using System.Collections.Generic;
using System.Text;
using System.Linq;
using Microsoft.AspNetCore.Mvc;
using Moq;
using Xunit;
using RealApplication4.Controllers;
using RealApplication4.Models;
using RealApplication4.Models.ViewModels;
//----------------------------------------------------------------------------------------------------------------------
namespace RealApplication4.Tests.Tests
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
			CProductsListViewModel								Result=((Controller.Index(null) as ViewResult).ViewData.Model as CProductsListViewModel);
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

			CProductsListViewModel								Result=((Controller.Index(null,2) as ViewResult).ViewData.Model as CProductsListViewModel);
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

			CProductsListViewModel								Result=((Controller.Index(null,2) as ViewResult).ViewData.Model as CProductsListViewModel);
			CPagingInfo											PageInfo=Result.PagingInfo;

			Assert.Equal(2,PageInfo.CurrentPage);
			Assert.Equal(3,PageInfo.ItemsPerPage);
			Assert.Equal(5,PageInfo.TotalItems);
			Assert.Equal(2,PageInfo.TotalPages);
		}
//----------------------------------------------------------------------------------------------------------------------
		[Fact]
		public void Can_Filter_Products()
		{
			Mock<IStoreRepository>								Mock=new Mock<IStoreRepository>();
			List<CProduct>										Products=new List<CProduct>();

			Products.Add(new CProduct(1,"P1","Cat1"));
			Products.Add(new CProduct(2,"P2","Cat2"));
			Products.Add(new CProduct(3,"P3","Cat1"));
			Products.Add(new CProduct(4,"P4","Cat2"));
			Products.Add(new CProduct(5,"P5","Cat3"));

			Mock.Setup(P => P.Products).Returns(Products.AsQueryable<CProduct>());

			HomeController										Controller=new HomeController(Mock.Object);

			Controller.PageSize=3;

			CProductsListViewModel								Result=((Controller.Index("Cat2",1) as ViewResult).ViewData.Model as CProductsListViewModel);
			CProduct[]											ResultProducts=Result.Products;

			Assert.Equal(2,ResultProducts.Length);

			Assert.True(ResultProducts[0].Name=="P2" && ResultProducts[0].Category=="Cat2");
			Assert.True(ResultProducts[1].Name=="P4" && ResultProducts[1].Category=="Cat2");
		}
//----------------------------------------------------------------------------------------------------------------------
		[Fact]
		public void Generate_Category_Specific_Product_Count()
		{
			Mock<IStoreRepository>								Mock=new Mock<IStoreRepository>();
			List<CProduct>										Products=new List<CProduct>();

			Products.Add(new CProduct(1,"P1","Cat1"));
			Products.Add(new CProduct(2,"P2","Cat2"));
			Products.Add(new CProduct(3,"P3","Cat1"));
			Products.Add(new CProduct(4,"P4","Cat2"));
			Products.Add(new CProduct(5,"P5","Cat3"));

			Mock.Setup(P => P.Products).Returns(Products.AsQueryable<CProduct>());

			HomeController										Target=new HomeController(Mock.Object);

			Target.PageSize=3;

			Func<IActionResult,CProductsListViewModel>			GetModel=P => ((ViewResult) P)?.ViewData?.Model as CProductsListViewModel;

			int?												Result1=GetModel(Target.Index("Cat1"))?.PagingInfo.TotalItems;
			int?												Result2=GetModel(Target.Index("Cat2"))?.PagingInfo.TotalItems;
			int?												Result3=GetModel(Target.Index("Cat3"))?.PagingInfo.TotalItems;
			int?												ResultAll=GetModel(Target.Index(null))?.PagingInfo.TotalItems;

			Assert.Equal(2,Result1);
			Assert.Equal(2,Result2);
			Assert.Equal(1,Result3);
			Assert.Equal(5,ResultAll);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------