﻿using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.ModelBinding;
using Microsoft.AspNetCore.Mvc.ViewFeatures;
using ControllersAndViews.Models;
//----------------------------------------------------------------------------------------------------------------------
namespace ControllersAndViews.Controllers
{
//----------------------------------------------------------------------------------------------------------------------
	// !!! CONTROLLER je oznaceny ako NON CONTROLLER.
	[NonController]
	public sealed class NonController : Controller
	{
//----------------------------------------------------------------------------------------------------------------------
		private readonly INameRepository						MNameRepository;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public NonController(INameRepository NameRepository)
		{
			MNameRepository=NameRepository;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public IActionResult MyActionMethod()
		{
			// !!! MODEL obsahuje DATA, ktore ma VIEW zobrazit.
			CName[]												Names=MNameRepository.GetNames();

			// !!! Zobrazi sa VIEW.
			IActionResult										Result=View("ShowNames",Names);
			
			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------