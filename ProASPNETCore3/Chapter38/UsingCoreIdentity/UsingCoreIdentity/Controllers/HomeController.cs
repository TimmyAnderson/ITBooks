﻿using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Diagnostics;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
//----------------------------------------------------------------------------------------------------------------------
namespace UsingCoreIdentity.Controllers
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