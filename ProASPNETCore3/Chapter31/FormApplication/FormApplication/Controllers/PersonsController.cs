using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using FormApplication.Services;
using FormApplication.Model;
//----------------------------------------------------------------------------------------------------------------------
namespace FormApplication.Database
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class PersonsController : Controller
	{
//----------------------------------------------------------------------------------------------------------------------
		private readonly IDBOperations							MDBOperations;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public PersonsController(IDBOperations DBOperations)
		{
			MDBOperations=DBOperations;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public IActionResult ViewPersons()
		{
			CPerson[]											Model=MDBOperations.GetPersons();
			IActionResult										Result=View("ViewPersons",Model);

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		public IActionResult AddPerson()
		{
			CPerson												Model=new CPerson();
			IActionResult										Result=View("AddPerson",Model);

			return(Result);
		}		
//----------------------------------------------------------------------------------------------------------------------
		[HttpPost]
		public IActionResult AddPerson(CPerson Person)
		{
			if (ModelState.IsValid==true)
			{
				MDBOperations.AddPerson(Person);

				IActionResult									Result=RedirectToAction("ViewPersons");

				return(Result);
			}
			else
			{
				IActionResult									Result=View("AddPerson");

				return(Result);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public IActionResult EditPerson(int ID)
		{
			CPerson												Model=MDBOperations.GetPerson(ID);
			IActionResult										Result=View("EditPerson",Model);

			return(Result);
		}		
//----------------------------------------------------------------------------------------------------------------------
		[HttpPost]
		public IActionResult EditPerson(CPerson Person)
		{
			if (ModelState.IsValid==true)
			{
				MDBOperations.UpdatePerson(Person);

				IActionResult									Result=RedirectToAction("ViewPersons");

				return(Result);
			}
			else
			{
				IActionResult									Result=View("EditPerson");

				return(Result);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public IActionResult DeletePerson(int ID)
		{
			CPerson												Model=MDBOperations.GetPerson(ID);
			IActionResult										Result=View("DeletePerson",Model);

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		public IActionResult DeletePersonConfirmed(int ID)
		{
			MDBOperations.RemovePerson(ID);

			IActionResult										Result=RedirectToAction("ViewPersons");

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		public IActionResult ViewPersonDetails(int ID)
		{
			CPerson												Model=MDBOperations.GetPerson(ID);
			IActionResult										Result=View("ViewPersonDetails",Model);

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------