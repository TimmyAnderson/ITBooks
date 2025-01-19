using System;
using System.Collections.Generic;
using System.Linq;
using Microsoft.AspNetCore.Mvc;
//----------------------------------------------------------------------------------------------------------------------
namespace WebServiceWithControllers
{
//----------------------------------------------------------------------------------------------------------------------
    [ApiController]
    [Route("[controller]")]
    public class NameController : ControllerBase
    {
//----------------------------------------------------------------------------------------------------------------------
		private readonly INameService							MNameService;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
        public NameController(INameService NameService)
        {
			MNameService=NameService;
        }
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
        [HttpGet]
		// !!! RETURN VALUE TYPE je POCO.
        public CName[] GetNames()
        {
			return(MNameService.GetNames());
        }
//----------------------------------------------------------------------------------------------------------------------
        [HttpGet]
		[Route("{ID}")]
		// !!! RETURN VALUE TYPE je TYPE [ActionResult<CName>].
        public ActionResult<CName> GetName(int ID)
        {
			CName												Name=MNameService.GetName(ID);

			if (Name!=null)
			{
				ActionResult<CName>								Result=Ok(Name);

				return(Result);
			}
			else
			{
				ActionResult<CName>								Result=NotFound();

				return(Result);
			}
        }
//----------------------------------------------------------------------------------------------------------------------
        [HttpPost]
		// !!! RETURN VALUE TYPE je TYPE [ActionResult<CName>].
        public ActionResult<CName> AddName(CNameInput NameInput)
        {
			CName												Name=MNameService.AddName(NameInput.FirstName,NameInput.LastName,NameInput.Age);
			ActionResult<CName>									Result=Created("",Name);

			return(Result);
        }
//----------------------------------------------------------------------------------------------------------------------
        [HttpPut]
		// !!! RETURN VALUE TYPE je TYPE [ActionResult<CName>].
        public ActionResult<CName> UpdateName(CName ExistingName)
        {
			CName												Name=MNameService.UpdateName(ExistingName);

			if (Name!=null)
			{
				ActionResult<CName>								Result=Ok(Name);

				return(Result);
			}
			else
			{
				ActionResult<CName>								Result=NotFound();

				return(Result);
			}
        }
//----------------------------------------------------------------------------------------------------------------------
        [HttpDelete]
		[Route("{ID}")]
		// !!! RETURN VALUE TYPE je TYPE [ActionResult].
        public ActionResult DeleteName(int ID)
        {
			bool												Deleted=MNameService.DeleteName(ID);

			if (Deleted==true)
			{
				ActionResult									Result=NoContent();

				return(Result);
			}
			else
			{
				ActionResult									Result=NotFound();

				return(Result);
			}
        }
//----------------------------------------------------------------------------------------------------------------------
    }
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------