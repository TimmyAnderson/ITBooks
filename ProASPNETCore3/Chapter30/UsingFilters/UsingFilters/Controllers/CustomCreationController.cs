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
	public sealed class CustomCreationController : Controller
	{
//----------------------------------------------------------------------------------------------------------------------
		// !!! Aplikuju sa 3 instancie toho isteho FILTER.
		// !!!!! Pri PAGE RELOAD budu vytvorene NOVE INSTANCIE FILTERS, pretoze CLASS [CAsynchronousResultCustomCreation] pomocou INTERFACE [IFilterFactory] vytvara VZDY NOVE INSTANCIE FILTERS.
		[CAsynchronousResultCustomCreation]
		[CAsynchronousResultCustomCreation]
		[CAsynchronousResultCustomCreation]
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