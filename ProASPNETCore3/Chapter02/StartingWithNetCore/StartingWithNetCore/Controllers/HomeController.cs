﻿using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
//----------------------------------------------------------------------------------------------------------------------
namespace StartingWithNetCore.Controllers
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class HomeController : Controller
	{
//----------------------------------------------------------------------------------------------------------------------
		public ViewResult Index()
		{
			return(View());
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------