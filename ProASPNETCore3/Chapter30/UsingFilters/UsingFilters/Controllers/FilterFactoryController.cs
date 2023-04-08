using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using UsingFilters.CustomFilters;
using UsingFilters.Model;
//----------------------------------------------------------------------------------------------------------------------
namespace UsingFilters.Controllers
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class FilterFactoryController : Controller
	{
//----------------------------------------------------------------------------------------------------------------------
		// !!! FILTERS, ktore vyuzivaju DEPENDENCY INJECTION su aplikovane pomocou ATTRIBUTE [TypeFilterAttribute].
		// !!!!! PARAMETER [IsReusable] urcuje, ze LIFESCOPE FILTER CLASSES bude TRANSIENT.
		[TypeFilter(typeof(CFilterFactorySetTimeActionFilter),IsReusable=false)]
		[TypeFilter(typeof(CFilterFactoryGetTimeResultFilter),IsReusable=false)]
		public ViewResult ActionMethodTypeFilterAttribute()
		{
			CResultMessage										Model=new CResultMessage("ACTION METHOD is EXECUTED !");
			ViewResult											Result=View("ResultMessage",Model);

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		// !!! FILTERS, ktore vyuzivaju DEPENDENCY INJECTION su aplikovane pomocou ATTRIBUTE [ServiceFilterAttribute].
		[ServiceFilter(typeof(CFilterFactoryCounterFilter))]
		public ViewResult ActionMethodServiceFilterAttribute()
		{
			CResultMessage										Model=new CResultMessage("ACTION METHOD is EXECUTED !");
			ViewResult											Result=View("ResultMessage",Model);

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------