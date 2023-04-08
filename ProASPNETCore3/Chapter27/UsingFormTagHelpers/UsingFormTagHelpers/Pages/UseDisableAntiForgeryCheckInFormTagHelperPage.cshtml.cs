using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.RazorPages;
using UsingFormTagHelpers.Model;
//----------------------------------------------------------------------------------------------------------------------
namespace UsingFormTagHelpers.Pages
{
//----------------------------------------------------------------------------------------------------------------------
	// !!!!! Vypne sa kontrola ANTIFORGERY TOKEN. Je to NUTNE, pretoze v HTML ELEMENT [<form>] bol nastaveny HTML ATTRIBUTE [asp-antiforgery] na VALUE 'false' co znamena, ze ANTIFORGERY TOKEN NEBOL VLOZENY do HTTP REQUEST. Bez aplikacie tohto ATTRIBUTE, by HTTP POST NEBOL SPRACOVANY.
	[IgnoreAntiforgeryToken]
    public class UseDisableAntiForgeryCheckInFormTagHelperPage : PageModel
    {
//----------------------------------------------------------------------------------------------------------------------
		private readonly IPageNameProvider						MPageNameProvider;
//----------------------------------------------------------------------------------------------------------------------
		// !!! FIELD sluzi na naplnenie FORM DATA pri HTTP GET.
		private CPageName										MPageName;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public UseDisableAntiForgeryCheckInFormTagHelperPage(IPageNameProvider PageNameProvider)
		{
			MPageNameProvider=PageNameProvider;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		// !!! FIELD sluzi na naplnenie FORM DATA pri HTTP GET.
		public CPageName										PageName
		{
			get
			{
				return(MPageName);
			}
			set
			{
				MPageName=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
        public void OnGet()
        {
			// !!! Kedze nechcem zobrazit ziadne data, kedze sa jedna o vkladanie noveho RECORD, tak je instancia CLASS PRAZDNA.
			MPageName=new CPageName();
        }
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		// !!!!! HANDLER METHOD ma ako parameter instanciu CLASS 'CPageName', ktora obsahuje PROPERTIES naplnene FORM DATA.
		// !!!!! POSTFIX 'MyHandler' je definovany pomocou HTML ATTRIBUTE [asp-page-handler].
		public IActionResult OnPostMyHandler(CPageName PageName)
		{
			MPageNameProvider.AddName(PageName);

			IActionResult										Result=RedirectToPage("ViewNamesPage");

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
    }
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------