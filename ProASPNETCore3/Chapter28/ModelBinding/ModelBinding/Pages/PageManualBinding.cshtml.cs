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
    public class PageManualBindingModel : PageModel
    {
//----------------------------------------------------------------------------------------------------------------------
		private readonly ISimpleChildProvider					MSimpleChildProvider;
//----------------------------------------------------------------------------------------------------------------------
		// !!! FIELD sluzi na naplnenie FORM DATA pri HTTP GET.
		private CSimpleChild									MSimpleChild;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public PageManualBindingModel(ISimpleChildProvider SimpleChildProvider)
		{
			MSimpleChildProvider=SimpleChildProvider;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
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
			// !!! Kedze nechcem zobrazit ziadne data, kedze sa jedna o vkladanie noveho RECORD, tak je instancia CLASS PRAZDNA.
			MSimpleChild=new CSimpleChild();
        }
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		// !!!!! POSTFIX 'MyHandler' je definovany pomocou HTML ATTRIBUTE [asp-page-handler].
		public async Task<IActionResult> OnPostMyHandlerAsync()
		{
			// !!! Pri MANUAL BINDING sa MUSI vytvorit instancia OBJECT.
			MSimpleChild=new CSimpleChild();

			// !!! Vykona sa MANUAL BINDING.
			// !!! 1. PARAMETER je OBJECT do ktoreho sa ma MODEL BINDING vykonat.
			// !!! 2. PARAMETER je PREFIX, ktory sa pouzil v RAZOR PAGE VIEW.
			// !!! Dalsie PARAMETERS vykonavaju BINDING jednotlivych PROPERTIES.
			await TryUpdateModelAsync<CSimpleChild>(SimpleChild,"SimpleChild",P => P.FirstName,P => P.LastName,P => P.Age,P => P.Sex);

			MSimpleChildProvider.AddChild(SimpleChild);

			IActionResult										Result=RedirectToPage("PageViewSimpleChildren");

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
    }
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------