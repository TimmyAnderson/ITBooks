﻿using System;
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
    public class PageViewSimpleChildrenViaTempModel : PageModel
    {
//----------------------------------------------------------------------------------------------------------------------
		private CSimpleChild[]									MChildren;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CSimpleChild[]									Children
		{
			get
			{
				return(MChildren);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
        public IActionResult OnGet()
        {
			MChildren=System.Text.Json.JsonSerializer.Deserialize<CSimpleChild[]>((string) TempData["Children"]);

			IActionResult										Result=Page();

			return(Result);
        }
//----------------------------------------------------------------------------------------------------------------------
    }
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------