using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.RazorPages;
using UsingRazorPages.Model;
//----------------------------------------------------------------------------------------------------------------------
namespace UsingRazorPages.Pages
{
//----------------------------------------------------------------------------------------------------------------------
	// !!! CLASS implementuje RAZOR PAGE MODEL.
    public class ShowNameNameNotFound : PageModel
    {
//----------------------------------------------------------------------------------------------------------------------
        public IActionResult OnGet()
        {
			// !!! Zobrazi sa RAZOR PAGE VIEW.
			IActionResult										Result=Page();

			return(Result);
        }
//----------------------------------------------------------------------------------------------------------------------
    }
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------