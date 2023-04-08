using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;
using System.Linq;
using System.Threading.Tasks;
//-----------------------------------------------------------------------------
namespace RealApplication1.Models
{
//-----------------------------------------------------------------------------
	public sealed class CProduct
	{
//-----------------------------------------------------------------------------
		private long											MProductID;
		private string											MName;
		private string											MDescription;
		private string											MCategory;
		private decimal											MPrice;
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
		public CProduct()
		{
		}
//-----------------------------------------------------------------------------
		public CProduct(long ProductID, string Name)
		{
			MProductID=ProductID;
			MName=Name;
		}
//-----------------------------------------------------------------------------
		public CProduct(string Name, decimal Price)
		{
			MName=Name;
			MPrice=Price;
		}
//-----------------------------------------------------------------------------
		public CProduct(string Name, string Description, string Category, decimal Price)
		{
			MName=Name;
			MDescription=Description;
			MCategory=Category;
			MPrice=Price;
		}
//-----------------------------------------------------------------------------
		public CProduct(long ProductID, string Name, string Description, string Category, decimal Price)
		{
			MProductID=ProductID;
			MName=Name;
			MDescription=Description;
			MCategory=Category;
			MPrice=Price;
		}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
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
//-----------------------------------------------------------------------------
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
//-----------------------------------------------------------------------------
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
//-----------------------------------------------------------------------------
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
//-----------------------------------------------------------------------------
		[Column(TypeName="decimal(8,2)")]
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
//-----------------------------------------------------------------------------
	}
//-----------------------------------------------------------------------------
}
//-----------------------------------------------------------------------------