using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Diagnostics;
using System.Linq;
using System.Threading.Tasks;
using ControllersAndViews.Models;
using Microsoft.AspNetCore.Mvc;
//----------------------------------------------------------------------------------------------------------------------
namespace ControllersAndViews.Controllers
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class RazorKeywordsController : Controller
	{
//----------------------------------------------------------------------------------------------------------------------
		private readonly INameRepository						MNameRepository;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public RazorKeywordsController(INameRepository NameRepository)
		{
			MNameRepository=NameRepository;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public IActionResult Expressions()
		{
			// !!! MODEL obsahuje DATA, ktore ma VIEW zobrazit.
			CName[]												Names=MNameRepository.GetNames();

			// !!! Zobrazi sa VIEW.
			IActionResult										Result=View("Expressions",Names);
			
			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		public IActionResult SetAttributes()
		{
			// !!! MODEL obsahuje DATA, ktore ma VIEW zobrazit.
			CName[]												Names=MNameRepository.GetNames();

			ViewBag.TableClass="table table-bordered table-striped";

			// !!! Zobrazi sa VIEW.
			IActionResult										Result=View("SetAttributes",Names);
			
			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		public IActionResult If()
		{
			// !!! MODEL obsahuje DATA, ktore ma VIEW zobrazit.
			CName[]												Names=MNameRepository.GetNames();

			// !!! Zobrazi sa VIEW.
			IActionResult										Result=View("If",Names);
			
			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		public IActionResult Switch1()
		{
			// !!! MODEL obsahuje DATA, ktore ma VIEW zobrazit.
			CName[]												Names=MNameRepository.GetNames();

			// !!! Zobrazi sa VIEW.
			IActionResult										Result=View("Switch1",Names);
			
			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		public IActionResult Switch2()
		{
			// !!! MODEL obsahuje DATA, ktore ma VIEW zobrazit.
			CName[]												Names=MNameRepository.GetNames();

			// !!! Zobrazi sa VIEW.
			IActionResult										Result=View("Switch2",Names);
			
			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		public IActionResult Enumeration()
		{
			// !!! MODEL obsahuje DATA, ktore ma VIEW zobrazit.
			CName[]												Names=MNameRepository.GetNames();

			// !!! Zobrazi sa VIEW.
			IActionResult										Result=View("Enumeration",Names);
			
			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		public IActionResult CodeBlocks()
		{
			// !!! MODEL obsahuje DATA, ktore ma VIEW zobrazit.
			CName[]												Names=MNameRepository.GetNames();

			// !!! Zobrazi sa VIEW.
			IActionResult										Result=View("CodeBlocks",Names);
			
			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------