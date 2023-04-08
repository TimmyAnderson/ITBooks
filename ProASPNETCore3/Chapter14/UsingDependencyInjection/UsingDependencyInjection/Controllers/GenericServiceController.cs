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
	public class GenericServiceController : Controller
	{
//----------------------------------------------------------------------------------------------------------------------
		private readonly IGenericService<string>				MServiceString;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		// !!! SERVICE 'IGenericService<TType>' je GENERIC SERVICE.
		public GenericServiceController(IGenericService<string> ServiceString)
		{
			MServiceString=ServiceString;

			MServiceString.SetValue("TIMMY");
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public IActionResult ShowValues()
		{
			// !!! Ziskaju sa instancie GENERIC SERVICE pre rozne TYPES.
			IGenericService<int>								ServiceInt=HttpContext.RequestServices.GetRequiredService<IGenericService<int>>();
			IGenericService<double>								ServiceDouble=HttpContext.RequestServices.GetRequiredService<IGenericService<double>>();

			ServiceInt.SetValue(100);
			ServiceDouble.SetValue(123.456);

			CGenericValues										Model=new CGenericValues(MServiceString.GetValue(),ServiceInt.GetValue(),ServiceDouble.GetValue());
			ViewResult											Result=View("GenericService",Model);

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------