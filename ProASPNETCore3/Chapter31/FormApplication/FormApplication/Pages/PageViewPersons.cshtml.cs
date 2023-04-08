using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.RazorPages;
using FormApplication.Model;
using FormApplication.Services;
//----------------------------------------------------------------------------------------------------------------------
namespace FormApplication.Pages
{
//----------------------------------------------------------------------------------------------------------------------
    public class PageViewPersonsModel : PageModel
    {
//----------------------------------------------------------------------------------------------------------------------
		private readonly IDBOperations							MDBOperations;
//----------------------------------------------------------------------------------------------------------------------
		private CPerson[]										MPersons;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public PageViewPersonsModel(IDBOperations DBOperations)
		{
			MDBOperations=DBOperations;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CPerson[]										Persons
		{
			get
			{
				return(MPersons);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
        public IActionResult OnGet()
        {
			MPersons=MDBOperations.GetPersons();

			IActionResult										Result=Page();

			return(Result);
        }
//----------------------------------------------------------------------------------------------------------------------
    }
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------