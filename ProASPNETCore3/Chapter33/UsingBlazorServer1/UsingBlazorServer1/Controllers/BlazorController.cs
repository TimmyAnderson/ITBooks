﻿using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
//----------------------------------------------------------------------------------------------------------------------
namespace UsingBlazorServer1.Controllers
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class BlazorController : Controller
	{
//----------------------------------------------------------------------------------------------------------------------
		public IActionResult ViewChildren()
		{
			IActionResult										Result=View("ViewChildren");

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------