using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using Microsoft.Extensions.DependencyInjection;
using UsingDependencyInjection.Model;
using UsingDependencyInjection.Service;
//----------------------------------------------------------------------------------------------------------------------
namespace UsingDependencyInjection.Controllers
{
//----------------------------------------------------------------------------------------------------------------------
	public class MultiImplementationServiceController : Controller
	{
//----------------------------------------------------------------------------------------------------------------------
		private readonly IMultiImplementationService			MDefaultService;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		// !!! Ak SERVICE ma VIACERO CLASSES, ktore implementuju SERVICE INTERFACE (BASE CLASS), DEPENDENCY INJECTION RESOLVING vrati POSLEDNY ZAREGISTROVANY SERVICE.
		public MultiImplementationServiceController(IMultiImplementationService DefaultService)
		{
			MDefaultService=DefaultService;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public IActionResult ShowServicesResults()
		{
			CMultiImplementationServiceData						DefaultService=new CMultiImplementationServiceData(MDefaultService.GetServiceName(),MDefaultService.GetText());

			// !!!!! METHOD vracia VSETKY CLASSES, ktore implementuju dany SERVICE INTERFACE (BASE CLASS).
			IMultiImplementationService[]						Services=ControllerContext.HttpContext.RequestServices.GetServices<IMultiImplementationService>().ToArray();
			List<CMultiImplementationServiceData>				ServicesData=new List<CMultiImplementationServiceData>();

			foreach(IMultiImplementationService Service in Services)
			{
				ServicesData.Add(new CMultiImplementationServiceData(Service.GetServiceName(),Service.GetText()));
			}

			CMultiImplementationServiceModel					Model=new CMultiImplementationServiceModel(DefaultService,ServicesData.ToArray());
			ViewResult											Result=View("MultiImplementationService",Model);

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------