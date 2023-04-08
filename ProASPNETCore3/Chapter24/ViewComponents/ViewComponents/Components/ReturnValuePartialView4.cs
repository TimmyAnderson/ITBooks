using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.ModelBinding;
using Microsoft.AspNetCore.Mvc.ViewComponents;
using Microsoft.AspNetCore.Mvc.ViewFeatures;
using ViewComponents.Model;
//----------------------------------------------------------------------------------------------------------------------
namespace ViewComponents.Components
{
//----------------------------------------------------------------------------------------------------------------------
	// !!! VIEW COMPONENT je DERIVED z CLASS [ViewComponent].
	public sealed class ReturnValuePartialView4 : ViewComponent
	{
//----------------------------------------------------------------------------------------------------------------------
		private readonly INameProvider							MNameProvider;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		// !!! NAME PROVIDER je naplneny DEPENDENCY INJECTION FRAMEWORK.
		public ReturnValuePartialView4(INameProvider NameProvider)
		{
			MNameProvider=NameProvider;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		// !!!!! METHOD [Invoke()] vracia TYPE [ViewViewComponentResult], ktory sluzi na zobrazenie PARTIAL VIEW.
		// !!!!! CLASS [ViewViewComponentResult] umoznuje spojenie VIEW COMPONENT s PARTIAL VIEW.
		public ViewViewComponentResult Invoke()
		{
			CName[]												Model=MNameProvider.GetNames();

			// !!! Pouzije sa HELPER METHOD [View()] na vratenie PARTIAL VIEW.
			// !!!!! PARTIAL VIEW sa nachadza v DIRECTORY [Views/Shared/Components/ReturnValuePartialView4], cim sa demonstruje, ze PARTIAL VIEWS mozu byt SHARED medzi VIEWS a RAZOR PAGES.
			ViewViewComponentResult								Result=View("ReturnValuePartialViewInViewsDirectory",Model);

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------