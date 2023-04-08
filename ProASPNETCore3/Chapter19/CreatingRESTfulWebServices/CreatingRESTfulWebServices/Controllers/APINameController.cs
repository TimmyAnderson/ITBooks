using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.JsonPatch;
using CreatingRESTfulWebServices.Database;
using CreatingRESTfulWebServices.Model;
//----------------------------------------------------------------------------------------------------------------------
namespace CreatingRESTfulWebServices.Controllers
{
//----------------------------------------------------------------------------------------------------------------------
	// !!! CONTROLLER implementuje API CONTROLLER.
	[Route("api/APIControllerName")]
	public class APINameController : Controller
	{
//----------------------------------------------------------------------------------------------------------------------
		private readonly INameProvider							MNameProvider;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public APINameController(INameProvider NameProvider)
		{
			MNameProvider=NameProvider;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		[HttpGet()]
		public IEnumerable<CName> Get()
		{
			IEnumerable<CName>									Names=MNameProvider.GetNames();

			return(Names);
		}
//----------------------------------------------------------------------------------------------------------------------
		// !!! ATTRIBUTE PARAMETER definuje ROUTE TEMPLATE.
		[HttpGet("{id}")]
		public CName Get(int ID)
		{
			CName												Name=MNameProvider.GetName(ID);

			return(Name);
		}
//----------------------------------------------------------------------------------------------------------------------
		// !!! Pri INSERT by sa NEMAL zadavat ID, pretoze ten generuje ENTITY FRAMEWORK. V pripade, ze by sa zadaval aj ID, mohlo by dost k OVER-BINDING.
		[HttpPost]
		public CName Post([FromBody] CNameNoID NameNoID)
		{
			CName												Name=new CName(0,NameNoID.FirstName,NameNoID.LastName,NameNoID.Age);
			CName												InsertedName=MNameProvider.AddName(Name);

			return(InsertedName);
		}
//----------------------------------------------------------------------------------------------------------------------
		[HttpPut]
		public CName Put([FromBody] CName Name)
		{
			CName												UpdatedName=MNameProvider.UpdateName(Name);

			return(UpdatedName);
		}
//----------------------------------------------------------------------------------------------------------------------
		// !!! ATTRIBUTE PARAMETER definuje ROUTE TEMPLATE.
		[HttpPatch("{id}")]
		public StatusCodeResult Patch(int ID, [FromBody] JsonPatchDocument<CName> Patch)
		{
			if (MNameProvider.PatchName(ID,Patch)==true)
			{
				// !!! V pripade, ze UPDATE BOL uspesny, vrati sa HTTP STATUS CODE 200.
				StatusCodeResult								Result=Ok();

				return(Result);
			}
			else
			{
				// !!! V pripade, ze UPDATE NEBOL uspesny, vrati sa HTTP STATUS CODE 404.
				StatusCodeResult								Result=NotFound();

				return(Result);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		// !!! ATTRIBUTE PARAMETER definuje ROUTE TEMPLATE.
		[HttpDelete("{id}")]
		public void Delete(int ID)
		{
			MNameProvider.RemoveName(ID);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------