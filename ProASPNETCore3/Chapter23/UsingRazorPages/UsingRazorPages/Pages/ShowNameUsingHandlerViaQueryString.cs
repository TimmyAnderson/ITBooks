﻿using System;
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
	// !!! CLASS implementuje RAZOR PAGE MODEL v SEPARATNOM FILE.
    public class ShowNameUsingHandlerViaQueryString : PageModel
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
		// !!! METHOD sa vola ako reakcia na HTTP GET VERB.
		// !!!!! Je to DEFAULT METHOD, ktora sa vola ak QUERY STRING NEOBSAHUJE PARAMETER [Handler].
        public void OnGet()
        {
			MName=new CName(0,"Timmy","Anderson",12);
        }
//----------------------------------------------------------------------------------------------------------------------
		// !!! METHOD sa vola ako reakcia na HTTP GET VERB.
		// !!!!! Je to DEFAULT METHOD, ktora sa vola ak QUERY STRING OBSAHUJE PARAMETER [Handler] s VALUE 'JennyThompson'.
        public void OnGetJennyThompson()
        {
			MName=new CName(0,"Jenny","Thompson",13);
        }
//----------------------------------------------------------------------------------------------------------------------
    }
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------