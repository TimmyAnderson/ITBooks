using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Moq;
using Xunit;
using RealApplication2.Models;
//----------------------------------------------------------------------------------------------------------------------
namespace RealApplication2.Tests.Tests
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class CCartTests
	{
//----------------------------------------------------------------------------------------------------------------------
		[Fact]
		public void Can_Add_New_Lines()
		{
			CProduct											Product1=new CProduct(1,"P1");
			CProduct											Product2=new CProduct(2,"P2");
			CCart												Target=new CCart();

			Target.AddItem(Product1,1);
			Target.AddItem(Product2,1);

			CCartLine[]											Results=Target.Lines.ToArray();

			Assert.Equal(2,Results.Length);
			Assert.Equal(Product1,Results[0].Product);
			Assert.Equal(Product2,Results[1].Product);
		}
//----------------------------------------------------------------------------------------------------------------------
		[Fact]
		public void Can_Add_Quantity_For_Existing_Lines()
		{
			CProduct											Product1=new CProduct(1,"P1");
			CProduct											Product2=new CProduct(2,"P2");
			CCart												Target=new CCart();

			Target.AddItem(Product1,1);
			Target.AddItem(Product2,1);
			Target.AddItem(Product1,10);

			CCartLine[]											Results=Target.Lines.OrderBy(P => P.Product.ProductID).ToArray();

			Assert.Equal(2,Results.Length);
			Assert.Equal(11,Results[0].Quantity);
			Assert.Equal(1,Results[1].Quantity);
		}
//----------------------------------------------------------------------------------------------------------------------
		[Fact]
		public void Can_Remove_Line()
		{
			CProduct											Product1=new CProduct(1,"P1");
			CProduct											Product2=new CProduct(2,"P2");
			CProduct											Product3=new CProduct(3,"P3");
			CCart												Target=new CCart();

			Target.AddItem(Product1,1);
			Target.AddItem(Product2,3);
			Target.AddItem(Product3,5);
			Target.AddItem(Product2,1);

			Target.RemoveLine(Product2);

			Assert.Empty(Target.Lines.Where(P => P.Product==Product2));
			Assert.Equal(2, Target.Lines.Count());
		}
//----------------------------------------------------------------------------------------------------------------------
		[Fact]
		public void Calculate_Cart_Total()
		{
			CProduct											Product1=new CProduct(1,"P1",100M);
			CProduct											Product2=new CProduct(2,"P2",50M);
			CCart												Target=new CCart();

			Target.AddItem(Product1,1);
			Target.AddItem(Product2,1);
			Target.AddItem(Product1,3);

			decimal												Result=Target.ComputeTotalValue();

			Assert.Equal(450M,Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		[Fact]
		public void Can_Clear_Contents()
		{
			CProduct											Product1=new CProduct(1,"P1",100M);
			CProduct											Product2=new CProduct(2,"P2",50M);
			CCart												Target=new CCart();

			Target.AddItem(Product1,1);
			Target.AddItem(Product2,1);

			Target.Clear();

			Assert.Empty(Target.Lines);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------