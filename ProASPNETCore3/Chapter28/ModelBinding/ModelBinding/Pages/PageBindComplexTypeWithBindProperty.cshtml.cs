using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.RazorPages;
using ModelBinding.Model;
//----------------------------------------------------------------------------------------------------------------------
namespace ModelBinding.Pages
{
//----------------------------------------------------------------------------------------------------------------------
    public class PageBindComplexTypeWithBindProperty : PageModel
    {
//----------------------------------------------------------------------------------------------------------------------
		private readonly ISimpleChildProvider					MSimpleChildProvider;
//----------------------------------------------------------------------------------------------------------------------
		// !!! FIELD sluzi na naplnenie FORM DATA pri HTTP GET aj na ULOZENIE FORM DATA pri HTTP POST.
		private CSimpleChild									MSimpleChild;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public PageBindComplexTypeWithBindProperty(ISimpleChildProvider SimpleChildProvider)
		{
			MSimpleChildProvider=SimpleChildProvider;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		// !!! Pretoze sa aplikoval ATTRIBUTE [BindPropertyAttribute], PROPERTY sluzi na naplnenie FORM DATA pri HTTP GET aj na ULOZENIE FORM DATA pri HTTP POST.
		[BindProperty(SupportsGet=true)]
		public CSimpleChild										SimpleChild
		{
			get
			{
				return(MSimpleChild);
			}
			set
			{
				MSimpleChild=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
        public void OnGet()
        {
			// !!! Umyselne sa naplnia nejake DATA, aby sa demonstrovalo, ze ASP.NET ich pouzije na naplnenie INPUT HTML ELEMENTS.
			MSimpleChild=new CSimpleChild(0,"XXX","YYY",0,ESex.Female);
        }
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		// !!!!! POSTFIX 'MyHandler' je definovany pomocou HTML ATTRIBUTE [asp-page-handler].
		public IActionResult OnPostMyHandler()
		{
			// !!!!! Kedze na PROPERTY 'SimpleChild' aplikovany ATTRIBUTE [BindPropertyAttribute], tak ASP.NET pouzije tuto PROPERTY aj na naplnenie VALUES z INPUT HTML ELEMENTS.
			MSimpleChildProvider.AddChild(SimpleChild);

			IActionResult										Result=RedirectToPage("PageViewSimpleChildren");

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
    }
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------