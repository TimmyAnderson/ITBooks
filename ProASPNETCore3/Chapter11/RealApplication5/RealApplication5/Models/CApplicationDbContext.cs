﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.EntityFrameworkCore;
//----------------------------------------------------------------------------------------------------------------------
namespace RealApplication5.Models
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class CApplicationDbContext : DbContext
	{
//----------------------------------------------------------------------------------------------------------------------
		private DbSet<CProduct>									MProducts;
		private DbSet<COrder>									MOrders;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CApplicationDbContext()
		{
		}
//----------------------------------------------------------------------------------------------------------------------
		public CApplicationDbContext(DbContextOptions<CApplicationDbContext> Options)
			: base(Options)
		{
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CProduct>									Products
		{
			get
			{
				return(MProducts);
			}
			set
			{
				MProducts=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<COrder>									Orders
		{
			get
			{
				return(MOrders);
			}
			set
			{
				MOrders=value;
			}
		}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		protected override void OnConfiguring(DbContextOptionsBuilder OptionsBuilder)
		{
			base.OnConfiguring(OptionsBuilder);

			OptionsBuilder.UseSqlite("Data Source=MyDatabase.db");
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------