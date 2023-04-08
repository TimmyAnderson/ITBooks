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
	public sealed class ReturnValueNotEncodedHtmlString : ViewComponent
	{
//----------------------------------------------------------------------------------------------------------------------
		private readonly INameProvider							MNameProvider;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		// !!! NAME PROVIDER je naplneny DEPENDENCY INJECTION FRAMEWORK.
		public ReturnValueNotEncodedHtmlString(INameProvider NameProvider)
		{
			MNameProvider=NameProvider;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public IViewComponentResult Invoke()
		{
			CName[]												Names=MNameProvider.GetNames();
			HtmlString											NotEncodedString=new HtmlString($"<b>[{Names[0]}] [{Names[1]}] [{Names[2]}]</b> !!!");

			// !!!!! CLASS [HtmlContentViewComponentResult] NEVYKONAVA HTML ENCODING, to znaci, ze NENAHRADZUJE CHARACTERS ako '<' ci '>' za "&lt;" ci "&gt;". To znaci, ze ak TEXT obsahuje HTML ELEMENTS, tak tieto budu vo VIEW interpretovane ako HTML ELEMENTS a NIE ako PLAIN TEXT.
			// !!!!! V tomto pripade, teda TEXT bude zobrazeny v BOLD FORMAT.
			HtmlContentViewComponentResult						Result=new HtmlContentViewComponentResult(NotEncodedString);

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------