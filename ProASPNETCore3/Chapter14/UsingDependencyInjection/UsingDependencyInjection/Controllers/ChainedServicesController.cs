using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using UsingDependencyInjection.Model;
using UsingDependencyInjection.Service;
//----------------------------------------------------------------------------------------------------------------------
namespace UsingDependencyInjection.Controllers
{
//----------------------------------------------------------------------------------------------------------------------
	public class ChainedServicesController : Controller
	{
//----------------------------------------------------------------------------------------------------------------------
		private readonly IChainedService						MChainedService;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		// !!! SERVICE 'IChainedService' je zavisly na INYCH SERVICES.
		public ChainedServicesController(IChainedService ChainedService)
		{
			MChainedService=ChainedService;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public IActionResult ShowStrings()
		{
			string												FromService1=MChainedService.GetTextFromService1();
			string												FromService2=MChainedService.GetTextFromService2();
			string												FromService3=MChainedService.GetTextFromService3();
			string												FromService4=MChainedService.GetTextFromService4();
			CString4											Model=new CString4(FromService1,FromService2,FromService3,FromService4);
			ViewResult											Result=View("ShowStrings4",Model);

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------