using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Html;
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
	public sealed class ReturnValueEncodedHtmlString : ViewComponent
	{
//----------------------------------------------------------------------------------------------------------------------
		private readonly INameProvider							MNameProvider;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		// !!! NAME PROVIDER je naplneny DEPENDENCY INJECTION FRAMEWORK.
		public ReturnValueEncodedHtmlString(INameProvider NameProvider)
		{
			MNameProvider=NameProvider;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public IViewComponentResult Invoke()
		{
			CName[]												Names=MNameProvider.GetNames();

			// !!!!! CLASS [ContentViewComponentResult] VYKONAVA HTML ENCODING, to znaci, ze NAHRADZUJE CHARACTERS ako '<' ci '>' za "&lt;" ci "&gt;". To znaci, ze ak TEXT obsahuje HTML ELEMENTS, tak tieto budu zobrazene ako PLAIN TEXT.
			// !!!!! V tomto pripade, teda TEXT NEBUDE zobrazeny v BOLD FORMAT, ale bude obsahovat HTML ELEMENT '<b>' a HTML ELEMENT '</b>'.
			ContentViewComponentResult							Result=Content($"<b>[{Names[0]}] [{Names[1]}] [{Names[2]}]</b> !!!");

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------