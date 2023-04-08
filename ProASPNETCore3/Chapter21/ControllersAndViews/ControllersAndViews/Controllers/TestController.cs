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
	public sealed class TestController : Controller
	{
//----------------------------------------------------------------------------------------------------------------------
		private readonly INameRepository						MNameRepository;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public TestController(INameRepository NameRepository)
		{
			MNameRepository=NameRepository;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public IActionResult ShowNames()
		{
			// !!! MODEL obsahuje DATA, ktore ma VIEW zobrazit.
			CName[]												Names=MNameRepository.GetNames();

			// !!! Zobrazi sa VIEW.
			IActionResult										Result=View("ShowNames",Names);
			
			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		public IActionResult MySharedView()
		{
			// !!! MODEL obsahuje DATA, ktore ma VIEW zobrazit.
			CName[]												Names=MNameRepository.GetNames();

			// !!! Zobrazi sa VIEW z DIRECTORY [Shared], pretoze v DIRECTORY [Test] sa VIEW [MySharedView.cshtml] NENACHADZA.
			IActionResult										Result=View("MySharedView",Names);
			
			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		// !!! METHOD je oznacena ako NON ACTION METHOD.
		[NonAction]
		public IActionResult ShowNamesNonAction()
		{
			// !!! MODEL obsahuje DATA, ktore ma VIEW zobrazit.
			CName[]												Names=MNameRepository.GetNames();

			// !!! Zobrazi sa VIEW.
			IActionResult										Result=View("ShowNames",Names);
			
			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		public IActionResult ShowViewOnSpecificPath()
		{
			// !!! MODEL obsahuje DATA, ktore ma VIEW zobrazit.
			CName[]												Names=MNameRepository.GetNames();

			// !!! Zobrazi sa VIEW z DIRECTORY [MyViews], pretoze je definovana EXPLICITNA PATH k VIEW.
			// !!!!! PATH MUSI zacinat CHARACTER '/' a MUSI mat EXTENSION '.cshtml'.
			IActionResult										Result=View("/MyViews/MyViewOnSpecificPath.cshtml",Names);

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		public IActionResult UseNonTypedView()
		{
			// !!! MODEL obsahuje DATA, ktore ma VIEW zobrazit.
			CName[]												Names=MNameRepository.GetNames();

			// !!! Zobrazi sa VIEW.
			IActionResult										Result=View("UntypedViewShowNames",Names);
			
			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		public IActionResult UseTypedView()
		{
			// !!! MODEL obsahuje DATA, ktore ma VIEW zobrazit.
			CName[]												Names=MNameRepository.GetNames();

			// !!! Zobrazi sa VIEW.
			IActionResult										Result=View("TypedViewShowNames",Names);
			
			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------