﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
//----------------------------------------------------------------------------------------------------------------------
namespace ViewComponents.Controllers
{
//----------------------------------------------------------------------------------------------------------------------
	public class ContextViewComponentsController : Controller
	{
//----------------------------------------------------------------------------------------------------------------------
		public IActionResult MyActionMethod()
		{
			ViewResult											Result=View("UsingViewComponentContext");

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------