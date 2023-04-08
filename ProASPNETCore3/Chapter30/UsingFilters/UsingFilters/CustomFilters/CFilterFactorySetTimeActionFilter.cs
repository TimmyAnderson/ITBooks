using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc.Filters;
using UsingFilters.Services;
//----------------------------------------------------------------------------------------------------------------------
namespace UsingFilters.CustomFilters
{
//----------------------------------------------------------------------------------------------------------------------
	// !!! FILTER meria cas vykonania ACTION METHOD.
	// !!!!! Kedze FILTER vyuziva DEPENDENCY INJECTION, tak NIE JE implementovany ako ATTRIBUTE.
	public sealed class CFilterFactorySetTimeActionFilter : IActionFilter
	{
//----------------------------------------------------------------------------------------------------------------------
		private readonly ITimeService							MTimeService;
		private readonly Stopwatch								MStopwatch;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		// !!! PARAMETER naplni DEPENDENCY INJECTION FRAMEWORK.
		// !!!!! Kedze instancia CLASS [CSetTimeActionFilter] ma TRANSIENT LIFESCOPE (pretoze je aplikovana pomocou ATTRIBUTE [TypeFilterAttribute]), tak instanciu CLASS [Stopwatch] je mozne vytvorit uz priamo v CONSTRUCTOR.
		// !!!!! SERVICE [ITimeService] ma SCOPED LIFESCOPE a teda je SHARED medzi vsetkymi instanciami FILTER CLASSES pouzitymi pri spracovani jedneho HTTP REQUEST.
		public CFilterFactorySetTimeActionFilter(ITimeService TimeService)
		{
			MTimeService=TimeService;
			MStopwatch=new Stopwatch();
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public void OnActionExecuting(ActionExecutingContext Context)
		{
			MStopwatch.Start();
		}
//----------------------------------------------------------------------------------------------------------------------
		public void OnActionExecuted(ActionExecutedContext Context)
		{
			MStopwatch.Stop();

			// !!! Kedze SERVICE [ITimeService] ma SCOPED LIFESCOPE, jeho zivotnost trva pocas celeho spracovania HTTP REQUEST.
			MTimeService.ElapsedTimeInTicks=MStopwatch.ElapsedTicks;
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------