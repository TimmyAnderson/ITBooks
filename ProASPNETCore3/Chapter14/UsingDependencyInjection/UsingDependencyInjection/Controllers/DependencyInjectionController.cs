using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using UsingDependencyInjection.Model;
//----------------------------------------------------------------------------------------------------------------------
namespace UsingDependencyInjection.Controllers
{
//----------------------------------------------------------------------------------------------------------------------
	public class DependencyInjectionController : Controller
	{
//----------------------------------------------------------------------------------------------------------------------
		// !!! INTERFACE je substituovany za CLASS, ktora INTERFACE implementuje.
		private readonly IInterfaceService						MInterfaceService;
		// !!! BASE CLASS je substituovana za DERIVED CLASS, ktora BASE CLASS dedi.
		private readonly CBaseClassService						MBaseClassService;
		// !!! CLASS je substituovana za insanciu CLASS, ktoru vytvara DEPENDENCY INJECTION FRAMEWORK.
		private readonly CConcreteClassService					MConcreteClassService;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		// !!! DEPENDENCY INJECTION FRAMEWORK vykona RESOLVING DEPENDENCY INJECTION.
		public DependencyInjectionController(IInterfaceService InterfaceService, CBaseClassService BaseClassService, CConcreteClassService ConcreteClassService)
		{
			MInterfaceService=InterfaceService;
			MBaseClassService=BaseClassService;
			MConcreteClassService=ConcreteClassService;

			InterfaceService.AddName(new CName(1,"Timmy","Anderson",12));
			InterfaceService.AddName(new CName(2,"Jenny","Thompson",13));
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public IActionResult MyActionMethod()
		{
			CName[]												DataFromInterfaceService=MInterfaceService.GetNames();
			string												DataFromBaseClassService=MBaseClassService.PrepareMessage("ACTION METHOD CALLED !");
			string												DataFromConcreteClassService=MConcreteClassService.PrepareMessage("ACTION METHOD CALLED !");
			CDependencyInjection								Model=new CDependencyInjection(DataFromInterfaceService,DataFromBaseClassService,DataFromConcreteClassService);
			ViewResult											Result=View("DependencyInjection",Model);

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------