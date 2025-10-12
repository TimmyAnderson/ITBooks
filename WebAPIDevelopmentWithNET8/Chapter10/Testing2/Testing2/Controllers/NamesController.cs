using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore.ChangeTracking;
using Microsoft.Extensions.Logging;
//----------------------------------------------------------------------------------------------------------------------
namespace Testing2
{
//----------------------------------------------------------------------------------------------------------------------
	[ApiController]
	[Route("[controller]")]
	public class NamesController : ControllerBase
	{
//----------------------------------------------------------------------------------------------------------------------
		private readonly ILogger<NamesController>				MLogger;
		private readonly IDBOperationsService					MDBOperationsService;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public NamesController(ILogger<NamesController> Logger, IDBOperationsService DBOperationsService)
		{
			MLogger=Logger;
			MDBOperationsService=DBOperationsService;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		[HttpGet("GetNames")]
		public async Task<ActionResult> GetNames()
		{
			try
			{
				CEntityName[]									Names=await MDBOperationsService.GetNames();

				ActionResult									Response=Ok(Names);

				return(Response);
			}
			catch(Exception E)
			{
				MLogger.LogError(E,"OPERATION FAILED.");
				throw;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		[HttpGet("GetName")]
		public async Task<ActionResult<CEntityName>> GetName(int ID)
		{
			try
			{
				CEntityName										Name=await MDBOperationsService.GetName(ID);

				if (Name!=null)
				{
					ActionResult								Response=Ok(Name);

					return(Response);
				}
				else
				{
					ActionResult								Response=NotFound();

					return(Response);
				}
			}
			catch(Exception E)
			{
				MLogger.LogError(E,"OPERATION FAILED.");
				throw;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		[HttpPost("InsertName")]
		public async Task<ActionResult> InsertName(CEntityName Name)
		{
			try
			{
				CEntityName										InsertedName=await MDBOperationsService.InsertName(Name);

				ActionResult									Result=CreatedAtAction(nameof(GetName),InsertedName);

				return(Result);
			}
			catch(Exception E)
			{
				MLogger.LogError(E,"OPERATION FAILED.");
				throw;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		[HttpPut("UpdateName")]
		public async Task<ActionResult> UpdateName(CNonEntityName Name)
		{
			try
			{
				CEntityName										NameFromDB=await MDBOperationsService.UpdateName(Name);

				if (NameFromDB!=null)
				{
					ActionResult								Result=NoContent();

					return(Result);
				}
				else
				{
					ActionResult								Response=NotFound();

					return(Response);
				}
			}
			catch(Exception E)
			{
				MLogger.LogError(E,"OPERATION FAILED.");
				throw;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		[HttpDelete("DeleteName")]
		public async Task<ActionResult> DeleteName(int ID)
		{
			try
			{
				bool											IsDeleted=await MDBOperationsService.DeleteName(ID);

				if (IsDeleted==true)
				{
					ActionResult								Response=NoContent();

					return(Response);
				}
				else
				{
					ActionResult								Response=NotFound();

					return(Response);
				}
			}
			catch(Exception E)
			{
				MLogger.LogError(E,"OPERATION FAILED.");
				throw;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------