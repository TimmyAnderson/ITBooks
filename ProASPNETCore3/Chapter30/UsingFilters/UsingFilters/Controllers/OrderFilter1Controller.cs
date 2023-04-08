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
	// !!! FILTERS su vykonavane v poradi v akom su definovane, pricom najprv su vykonane vsetky CONTROLLER FILTERS a nasledne vsetky ACTION METHOD FILTERS.
	[COrderFilter1("CONTROLLER 1")]
	[COrderFilter1("CONTROLLER 2")]
	public sealed class OrderFilter1Controller : Controller
	{
//----------------------------------------------------------------------------------------------------------------------
		[COrderFilter1("ACTION METHOD 1")]
		[COrderFilter1("ACTION METHOD 2")]
		public ViewResult ActionMethodNoOrder()
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