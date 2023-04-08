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
	public sealed class InstanceLifetimeController : Controller
	{
//----------------------------------------------------------------------------------------------------------------------
		// !!! Aplikuju sa 3 instancie toho isteho FILTER.
		// !!!!! Pri PAGE RELOAD budu instancie REUSED, pretoze su pouzivane ako SINGLETONS.
		[CAsynchronousResultInstanceLifetime]
		[CAsynchronousResultInstanceLifetime]
		[CAsynchronousResultInstanceLifetime]
		public ViewResult MyActionMethod()
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