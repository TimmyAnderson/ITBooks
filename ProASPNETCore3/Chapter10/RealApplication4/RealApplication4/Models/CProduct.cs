using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;
using System.Linq;
using System.Threading.Tasks;
//----------------------------------------------------------------------------------------------------------------------
namespace RealApplication4.Models
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class CProduct
	{
//----------------------------------------------------------------------------------------------------------------------
		private long											MProductID;
		private string											MName;
		private string											MDescription;
		private string											MCategory;
		private decimal											MPrice;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CProduct()
		{
		}
//----------------------------------------------------------------------------------------------------------------------
		public CProduct(long ProductID, string Name)
		{
			MProductID=ProductID;
			MName=Name;
		}
//----------------------------------------------------------------------------------------------------------------------
		public CProduct(string Name, decimal Price)
		{
			MName=Name;
			MPrice=Price;
		}
//----------------------------------------------------------------------------------------------------------------------
		public CProduct(long ProductID, string Name, decimal Price)
		{
			MProductID=ProductID;
			MName=Name;
			MPrice=Price;
		}
//----------------------------------------------------------------------------------------------------------------------
		public CProduct(long ProductID, string Name, string Category)
		{
			MProductID=ProductID;
			MName=Name;
			MCategory=Category;
		}
//----------------------------------------------------------------------------------------------------------------------
		public CProduct(string Name, string Description, string Category, decimal Price)
		{
			MName=Name;
			MDescription=Description;
			MCategory=Category;
			MPrice=Price;
		}
//----------------------------------------------------------------------------------------------------------------------
		public CProduct(long ProductID, string Name, string Description, string Category, decimal Price)
		{
			MProductID=ProductID;
			MName=Name;
			MDescription=Description;
			MCategory=Category;
			MPrice=Price;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		[Key]
		public long												ProductID
		{
			get
			{
				return(MProductID);
			}
			set
			{
				MProductID=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		[Required(ErrorMessage="Please enter a product name.")]
		public string											Name
		{
			get
			{
				return(MName);
			}
			set
			{
				MName=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		[Required(ErrorMessage="Please enter a description.")]
		public string											Description
		{
			get
			{
				return(MDescription);
			}
			set
			{
				MDescription=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		[Required(ErrorMessage="Please specify a category.")]
		public string											Category
		{
			get
			{
				return(MCategory);
			}
			set
			{
				MCategory=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		[Column(TypeName="decimal(8,2)")]
		[Range(0.01,double.MaxValue,ErrorMessage="Please enter a positive price.")]
		public decimal											Price
		{
			get
			{
				return(MPrice);
			}
			set
			{
				MPrice=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------