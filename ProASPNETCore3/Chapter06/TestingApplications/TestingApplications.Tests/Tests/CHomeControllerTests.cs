using System;
using System.Collections.Generic;
using System.Text;
using Microsoft.AspNetCore.Mvc;
using Moq;
using Xunit;
using TestingApplications.Controllers;
using TestingApplications.Models;
using TestingApplications.Tests.DataStore;
using TestingApplications.Tests.Helpers;
//----------------------------------------------------------------------------------------------------------------------
namespace TestingApplications.Tests.Tests
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class CHomeControllerTests
	{
//----------------------------------------------------------------------------------------------------------------------
		[Fact]
		public void IndexActionModelIsComplete1()
		{
			HomeController										Controller=new HomeController();
			CProduct											Product1=new CProduct("Kayak",275M);
			CProduct											Product2=new CProduct("Lifejacket",48.95M);
			CProduct[]											Products=new CProduct[]{Product1,Product2};
			IEnumerable<CProduct>								Model=((Controller.Index() as ViewResult)?.ViewData.Model as IEnumerable<CProduct>);
			CComparer<CProduct>									Comparer=CComparer.Get<CProduct>((P1, P2) => P1.Name==P2.Name && P1.Price==P2.Price);

			Assert.Equal(Products,Model,Comparer);
		}
//----------------------------------------------------------------------------------------------------------------------
		[Fact]
		public void IndexActionModelIsComplete2()
		{
			CProduct											Product1=new CProduct("P1",75.10M);
			CProduct											Product2=new CProduct("P2",120M);
			CProduct											Product3=new CProduct("P3",110M);
			CProduct[]											Products=new CProduct[]{Product1,Product2,Product3};
			IDataSource											Data=new CFakeDataSource(Products);
			HomeController										Controller=new HomeController();

			Controller.DataSource=Data;

			IEnumerable<CProduct>								Model=((Controller.Index() as ViewResult)?.ViewData.Model as IEnumerable<CProduct>);
			CComparer<CProduct>									Comparer=CComparer.Get<CProduct>((P1, P2) => P1.Name==P2.Name && P1.Price==P2.Price);

			Assert.Equal(Products,Model,Comparer);
		}
//----------------------------------------------------------------------------------------------------------------------
		[Fact]
		public void IndexActionModelIsComplete3()
		{
			CProduct											Product1=new CProduct("P1",75.10M);
			CProduct											Product2=new CProduct("P2",120M);
			CProduct											Product3=new CProduct("P3",110M);
			CProduct[]											Products=new CProduct[]{Product1,Product2,Product3};

			Mock<IDataSource>									Mock=new Mock<IDataSource>();

			Mock.SetupGet(P => P.Products).Returns(Products);

			HomeController										Controller=new HomeController();

			Controller.DataSource=Mock.Object;

			IEnumerable<CProduct>								Model=((Controller.Index() as ViewResult)?.ViewData.Model as IEnumerable<CProduct>);
			CComparer<CProduct>									Comparer=CComparer.Get<CProduct>((P1, P2) => P1.Name==P2.Name && P1.Price==P2.Price);

			Assert.Equal(Products,Model,Comparer);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------