using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using RealApplication5.Models;
using RealApplication5.Models.ViewModels;
//----------------------------------------------------------------------------------------------------------------------
namespace RealApplication5.Controllers
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class HomeController : Controller
	{
//----------------------------------------------------------------------------------------------------------------------
		private readonly IStoreRepository						MRepository;
//----------------------------------------------------------------------------------------------------------------------
		private int												MPageSize;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public HomeController(IStoreRepository Repository)
		{
			MRepository=Repository;
			MPageSize=4;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public int												PageSize
		{
			get
			{
				return(MPageSize);
			}
			set
			{
				MPageSize=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public IActionResult Index(string Category, int ProductPage=1)
		{
			CProduct[]											Products=MRepository.Products.Where(P => Category==null || P.Category==Category).OrderBy(P => P.ProductID).Skip((ProductPage-1)*MPageSize).Take(MPageSize).ToArray();
			int													TotalItems=((Category==null) ? MRepository.Products.Count() : MRepository.Products.Where(P => P.Category==Category).Count());
			CPagingInfo											PagingInfo=new CPagingInfo(TotalItems,MPageSize,ProductPage);
			CProductsListViewModel								Model=new CProductsListViewModel(Products,PagingInfo,Category);
			IActionResult										Result=View("Index",Model);

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------