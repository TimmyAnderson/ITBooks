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
    public class PageBindComplexType : PageModel
    {
//----------------------------------------------------------------------------------------------------------------------
		private readonly ISimpleChildProvider					MSimpleChildProvider;
//----------------------------------------------------------------------------------------------------------------------
		// !!! FIELD sluzi na naplnenie FORM DATA pri HTTP GET.
		private CSimpleChild									MSimpleChild;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public PageBindComplexType(ISimpleChildProvider SimpleChildProvider)
		{
			MSimpleChildProvider=SimpleChildProvider;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		// !!! PROPERTY sluzi na naplnenie FORM DATA pri HTTP GET.
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
		// !!!!! HANDLER METHOD ma ako PARAMETER instanciu CLASS 'CSimpleChild', ktora obsahuje PROPERTIES naplnene FORM DATA.
		// !!!!! PARAMETER HANDLER METHOD je NEZAVISLY na VALUE PROPERTY 'SimpleChild'.
		// !!!!! POSTFIX 'MyHandler' je definovany pomocou HTML ATTRIBUTE [asp-page-handler].
		public IActionResult OnPostMyHandler(CSimpleChild SimpleChild)
		{
			MSimpleChildProvider.AddChild(SimpleChild);

			IActionResult										Result=RedirectToPage("PageViewSimpleChildren");

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
    }
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------