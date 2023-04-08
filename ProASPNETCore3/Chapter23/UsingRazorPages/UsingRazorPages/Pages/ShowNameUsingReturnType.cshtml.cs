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
    public class ShowNameUsingReturnType : PageModel
    {
//----------------------------------------------------------------------------------------------------------------------
		private CName											MName;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CName											Name
		{
			get
			{
				return(MName);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		// !!! METHOD ma PARAMETER, ktory je mapovany na PARAMETER QUERY STRING.
		// !!!!! METHOD vracia RETURN TYPE [IActionResult], ktory okrem RAZOR PAGE VIEW umoznuje vracat aj HTTP STATUS CODES, alebo spravit REDIRECT na inu RAZOR PAGE.
        public IActionResult OnGet(int ID)
        {
			if (ID<=0)
			{
				// !!! Vrati HTTP STATUS CODE 404.
				IActionResult									Result=NotFound();

				return(Result);
			}
			else if (ID==1)
			{
				MName=new CName(ID,"Timmy","Anderson",12);

				// !!! Vrati RAZOR PAGE VIEW.
				IActionResult									Result=Page();

				return(Result);
			}
			else if (ID==2)
			{
				MName=new CName(ID,"Jenny","Thompson",13);

				// !!! Vrati RAZOR PAGE VIEW.
				IActionResult									Result=Page();

				return(Result);
			}
			else
			{
				// !!! Spravi REDIRECT na RAZOR PAGE 'ShowNameNameNotFound'.
				IActionResult									Result=RedirectToPage("ShowNameNameNotFound");

				return(Result);
			}
        }
//----------------------------------------------------------------------------------------------------------------------
    }
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------