using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using CqrsCore;
using MediatR;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore.ChangeTracking;
//----------------------------------------------------------------------------------------------------------------------
namespace CqrsWeb
{
//----------------------------------------------------------------------------------------------------------------------
	[ApiController]
	[Route("[controller]")]
	public class NamesController : ControllerBase
	{
//----------------------------------------------------------------------------------------------------------------------
		private readonly ISender								MMediatorSender;
		private readonly IPublisher								MMediatorPublisher;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public NamesController(ISender MediatorSender, IPublisher MediatorPublisher)
		{
			MMediatorSender=MediatorSender;
			MMediatorPublisher=MediatorPublisher;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		[HttpGet("GetNames")]
		public async Task<ActionResult<CDtoFullName[]>> GetNames()
		{
			CRequestGetNames									Request=new CRequestGetNames();

			// !!! QUERY sa vykona cez MEDIATOR v 1 HANDLER.
			CDtoFullName[]										FullNames=await MMediatorSender.Send(Request);

			ActionResult<CDtoFullName[]>						Response=Ok(FullNames);

			return(Response);
		}
//----------------------------------------------------------------------------------------------------------------------
		[HttpGet("GetName")]
		public async Task<ActionResult<CDtoFullName>> GetName(int ID)
		{
			CRequestGetNameByID									Request=new CRequestGetNameByID(ID);

			// !!! QUERY sa vykona cez MEDIATOR v 1 HANDLER.
			CDtoFullName										FullName=await MMediatorSender.Send(Request);

			if (FullName!=null)
			{
				ActionResult<CDtoFullName>						Response=Ok(FullName);

				return(Response);
			}
			else
			{
				ActionResult<CDtoFullName>						Response=NotFound();

				return(Response);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		[HttpPost("InsertName")]
		public async Task<ActionResult<CDtoFullName>> InsertName(CDtoNameToInsert Name)
		{
			CRequestInsertName									Request=new CRequestInsertName(Name);

			// !!! COMMAND sa vykona cez MEDIATOR v 1 HANDLER.
			CDtoFullName										FullName=await MMediatorSender.Send(Request);

			CNotificationWriteToLog								Notification=new CNotificationWriteToLog("INSERT",FullName);

			// !!! NOTIFICATION sa vykona vo VIACERYCH HANDLERS.
			await MMediatorPublisher.Publish(Notification);

			ActionResult<CDtoFullName>							Result=CreatedAtAction(nameof(GetName),FullName);

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		[HttpPut("UpdateName")]
		public async Task<ActionResult> UpdateName(CDtoNameToUpdate Name)
		{
			CRequestUpdateName									Request=new CRequestUpdateName(Name);

			// !!! COMMAND sa vykona cez MEDIATOR v 1 HANDLER.
			CDtoFullName										FullName=await MMediatorSender.Send(Request);

			if (FullName!=null)
			{
				CNotificationWriteToLog							Notification=new CNotificationWriteToLog("UPDATE",FullName);

				// !!! NOTIFICATION sa vykona vo VIACERYCH HANDLERS.
				await MMediatorPublisher.Publish(Notification);

				ActionResult									Result=NoContent();

				return(Result);
			}
			else
			{
				ActionResult									Response=NotFound();

				return(Response);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		[HttpDelete("DeleteName")]
		public async Task<ActionResult> DeleteName(int ID)
		{
			CNotificationDeleteName								Request=new CNotificationDeleteName(ID);

			// !!! NOTIFICATION sa vykona cez MEDIATOR v 1 HANDLER.
			await MMediatorPublisher.Publish(Request);

			ActionResult										Response=NoContent();

			return(Response);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------