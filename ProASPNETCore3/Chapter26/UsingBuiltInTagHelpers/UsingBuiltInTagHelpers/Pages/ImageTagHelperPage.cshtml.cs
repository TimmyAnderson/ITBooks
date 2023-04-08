using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.RazorPages;
//----------------------------------------------------------------------------------------------------------------------
namespace UsingBuiltInTagHelpers.Pages
{
//----------------------------------------------------------------------------------------------------------------------
    public class ImageTagHelperPage : PageModel
    {
//----------------------------------------------------------------------------------------------------------------------
        public IActionResult OnGet()
        {
			IActionResult										Result=Page();

			return(Result);
        }
//----------------------------------------------------------------------------------------------------------------------
		// !!! HTTP GET HANDLER 'MyHandler', ktory sa pouziva z RAZOR PAGE 'AnchorTagHelperPage'.
        public IActionResult OnGetMyHandler()
        {
			IActionResult										Result=Page();

			return(Result);
        }
//----------------------------------------------------------------------------------------------------------------------
    }
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------