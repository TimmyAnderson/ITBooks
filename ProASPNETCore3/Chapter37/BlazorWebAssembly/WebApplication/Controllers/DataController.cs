using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using SharedClasses.Classes;
using WebApplication.Services;
//----------------------------------------------------------------------------------------------------------------------
namespace WebApplication.Controllers
{
//----------------------------------------------------------------------------------------------------------------------
	[ApiController]
	[Route("/api/persons")]
	public class DataController : ControllerBase
	{
//----------------------------------------------------------------------------------------------------------------------
		private readonly IDBOperations							MDBOperations;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public DataController(IDBOperations DBOperations)
		{
			MDBOperations=DBOperations;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		[HttpPost]
		[Route("AddPerson")]
		public CPerson AddPerson(CPerson Person)
		{
			CPerson												AddedPerson=MDBOperations.AddPerson(Person);

			return(AddedPerson);
		}
//----------------------------------------------------------------------------------------------------------------------
		[HttpPut]
		[Route("UpdatePerson")]
		public CPerson UpdatePerson(CPerson Person)
		{
			CPerson												UpdatedPerson=MDBOperations.UpdatePerson(Person);

			return(UpdatedPerson);
		}
//----------------------------------------------------------------------------------------------------------------------
		[HttpDelete]
		[Route("RemovePerson/{ID:int}")]
		public void RemovePerson(int ID)
		{
			MDBOperations.RemovePerson(ID);
		}
//----------------------------------------------------------------------------------------------------------------------
		[HttpGet]
		[Route("GetPerson/{ID:int}")]
		public CPerson GetPerson(int ID)
		{
			CPerson												Person=MDBOperations.GetPerson(ID);

			return(Person);
		}
//----------------------------------------------------------------------------------------------------------------------
		[HttpGet]
		[Route("GetPersons")]
		public CPerson[] GetPersons()
		{
			CPerson[]											Persons=MDBOperations.GetPersons();

			return(Persons);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------