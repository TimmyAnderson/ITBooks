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
    public class PageBindSimpleTypeModel : PageModel
    {
//----------------------------------------------------------------------------------------------------------------------
		private readonly ISimpleChildProvider					MSimpleChildProvider;
//----------------------------------------------------------------------------------------------------------------------
		// !!! FIELD sluzi na naplnenie FORM DATA pri HTTP GET.
		private CSimpleChild									MSimpleChild;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public PageBindSimpleTypeModel(ISimpleChildProvider SimpleChildProvider)
		{
			MSimpleChildProvider=SimpleChildProvider;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		// !!! FIELD sluzi na naplnenie FORM DATA pri HTTP GET.
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
		// !!!!! Nato, aby bol BINDING USPESNE VYKONANY, je NUTNE na INPUT HTML ELEMENTS aplikovat HTML ATTRIBUTE [name], ktoreho VALUE je ROVNAKA ako NAME PARAMETER RAZOR PAGE HANDLER.
		// !!!!! POSTFIX 'MyHandler' je definovany pomocou HTML ATTRIBUTE [asp-page-handler].
		public IActionResult OnPostMyHandler(string FirstName, string LastName, int Age, ESex Sex)
		{
			CSimpleChild										SimpleChild=new CSimpleChild(0,FirstName,LastName,Age,Sex);

			MSimpleChildProvider.AddChild(SimpleChild);

			IActionResult										Result=RedirectToPage("PageViewSimpleChildren");

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
    }
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------