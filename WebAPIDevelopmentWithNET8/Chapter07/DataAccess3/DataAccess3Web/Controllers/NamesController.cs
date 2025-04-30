using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore.ChangeTracking;
//----------------------------------------------------------------------------------------------------------------------
namespace DataAccess3Web
{
//----------------------------------------------------------------------------------------------------------------------
	[ApiController]
	[Route("[controller]")]
	public class NamesController : ControllerBase
	{
//----------------------------------------------------------------------------------------------------------------------
		private readonly CDBContext1							MContext1;
		private readonly CDBContext2							MContext2;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public NamesController(CDBContext1 Context1, CDBContext2 Context2)
		{
			MContext1=Context1;
			MContext2=Context2;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		[HttpGet("GetNames1")]
		public async Task<ActionResult<CEntityName[]>> GetNames1()
		{
			CEntityName[]										Names=await MContext1.EntitiesNames.ToArrayAsync();
			ActionResult<CEntityName[]>							Response=Ok(Names);

			return(Response);
		}
//----------------------------------------------------------------------------------------------------------------------
		[HttpGet("GetNames2")]
		public async Task<ActionResult<CEntityName[]>> GetNames2()
		{
			CEntityName[]										Names=await MContext2.EntitiesNames.ToArrayAsync();
			ActionResult<CEntityName[]>							Response=Ok(Names);

			return(Response);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------