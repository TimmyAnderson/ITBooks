﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Http;
using Microsoft.Extensions.DependencyInjection;
using Newtonsoft.Json;
using RealApplication5.Infrastructure;
//----------------------------------------------------------------------------------------------------------------------
namespace RealApplication5.Models
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class CSessionCart : CCart
	{
//----------------------------------------------------------------------------------------------------------------------
		[JsonIgnore]
		private ISession										MSession;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		[JsonIgnore]
		public ISession											Session
		{
			get
			{
				return(MSession);
			}
			set
			{
				MSession=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public static CCart GetCart(IServiceProvider Services)
		{
			ISession											Session=Services.GetRequiredService<IHttpContextAccessor>()?.HttpContext.Session;
			CSessionCart										Cart=Session?.GetJson<CSessionCart>("Cart") ?? new CSessionCart();

			Cart.Session=Session;

			return(Cart);
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public override void AddItem(CProduct Product, int Quantity)
		{
			base.AddItem(Product,Quantity);

			Session.SetJson("Cart",this);
		}
//----------------------------------------------------------------------------------------------------------------------
		public override void RemoveLine(CProduct Product)
		{
			base.RemoveLine(Product);

			Session.SetJson("Cart",this);
		}
//----------------------------------------------------------------------------------------------------------------------
		public override void Clear()
		{
			base.Clear();

			Session.Remove("Cart");
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------