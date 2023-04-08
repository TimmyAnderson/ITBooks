using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Diagnostics;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using AdvancedControllersAndViews.Models;
//----------------------------------------------------------------------------------------------------------------------
namespace AdvancedControllersAndViews.Controllers
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class LayoutsController : Controller
	{
//----------------------------------------------------------------------------------------------------------------------
		private readonly INameRepository						MNameRepository;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public LayoutsController(INameRepository NameRepository)
		{
			MNameRepository=NameRepository;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public IActionResult ShowSimpleLayoutView()
		{
			// !!! MODEL obsahuje DATA, ktore ma VIEW zobrazit.
			CName[]												Names=MNameRepository.GetNames();

			// !!! Pomocou [ViewBag] je mozne prenasat do VIEWS lubovolne data.
			ViewBag.Title="LAYOUT VIEW";

			// !!! Zobrazi sa VIEW.
			IActionResult										Result=View("SimpleLayoutView",Names);
			
			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		public IActionResult ShowUsingDefaultLayoutView()
		{
			// !!! MODEL obsahuje DATA, ktore ma VIEW zobrazit.
			CName[]												Names=MNameRepository.GetNames();

			// !!! Pomocou [ViewBag] je mozne prenasat do VIEWS lubovolne data.
			ViewBag.Title="Using DEFAULT LAYOUT VIEW";

			// !!! Zobrazi sa VIEW.
			IActionResult										Result=View("UsingDefaultLayoutView",Names);
			
			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		public IActionResult ShowOverrideDefaultLayoutView()
		{
			// !!! MODEL obsahuje DATA, ktore ma VIEW zobrazit.
			CName[]												Names=MNameRepository.GetNames();

			// !!! Pomocou [ViewBag] je mozne prenasat do VIEWS lubovolne data.
			ViewBag.Title="Using OVERRIDDEN LAYOUT VIEW";

			// !!! Zobrazi sa VIEW.
			IActionResult										Result=View("OverrideDefaultLayoutView",Names);
			
			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		public IActionResult ShowUsingSections1LayoutView()
		{
			// !!! MODEL obsahuje DATA, ktore ma VIEW zobrazit.
			CName[]												Names=MNameRepository.GetNames();

			// !!! Pomocou [ViewBag] je mozne prenasat do VIEWS lubovolne data.
			ViewBag.Title="Using LAYOUT with SECTIONS 1";

			// !!! Zobrazi sa VIEW.
			IActionResult										Result=View("UsingSections1",Names);
			
			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		public IActionResult ShowUsingSections2LayoutView()
		{
			// !!! MODEL obsahuje DATA, ktore ma VIEW zobrazit.
			CName[]												Names=MNameRepository.GetNames();

			// !!! Pomocou [ViewBag] je mozne prenasat do VIEWS lubovolne data.
			ViewBag.Title="Using LAYOUT with SECTIONS 2";

			// !!! Zobrazi sa VIEW.
			IActionResult										Result=View("UsingSections2",Names);
			
			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------