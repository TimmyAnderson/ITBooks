using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.RazorPages;
//----------------------------------------------------------------------------------------------------------------------
namespace AdvancedBlazorFeatures.Pages
{
//----------------------------------------------------------------------------------------------------------------------
    public class PageCallCSharpStaticMethodFromJavaScriptCodeModel : PageModel
    {
//----------------------------------------------------------------------------------------------------------------------
		public IActionResult OnGet()
		{
			IActionResult										Result=Page();

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
    }
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------