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
	// !!! FILTERS su vykonavane na zaklade hodnoty PROPERTY [IOrderedFilter.Order].
	[COrderFilter2("CONTROLLER 1",100)]
	[COrderFilter2("CONTROLLER 2",-100)]
	public sealed class OrderFilter2Controller : Controller
	{
//----------------------------------------------------------------------------------------------------------------------
		[COrderFilter2("ACTION METHOD 1",10)]
		[COrderFilter2("ACTION METHOD 2",-10)]
		public ViewResult ActionMethodWithOrder()
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