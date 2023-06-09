﻿using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using TestingApplications.Models;
//----------------------------------------------------------------------------------------------------------------------
namespace TestingApplications.Controllers
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class HomeController : Controller
	{
//----------------------------------------------------------------------------------------------------------------------
		private IDataSource										MDataSource;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public HomeController()
		{
			MDataSource=new CProductDataSource();
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public IDataSource										DataSource
		{
			get
			{
				return(MDataSource);
			}
			set
			{
				MDataSource=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public IActionResult Index()
		{
			IEnumerable<CProduct>								Model=MDataSource.Products;
			IActionResult										Result=View("Index",Model);

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------