using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore.ChangeTracking;
//----------------------------------------------------------------------------------------------------------------------
namespace UsingAzureSqlDatabase
{
//----------------------------------------------------------------------------------------------------------------------
	[ApiController]
	[Route("[controller]")]
	public class NamesController : ControllerBase
	{
//----------------------------------------------------------------------------------------------------------------------
		private readonly CDBContext								MContext;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public NamesController(CDBContext Context)
		{
			MContext=Context;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		[HttpGet("GetNames")]
		public async Task<ActionResult<CEntityName[]>> GetNames()
		{
			CEntityName[]										Names=await MContext.EntitiesNames.ToArrayAsync();
			ActionResult<CEntityName[]>							Response=Ok(Names);

			return(Response);
		}
//----------------------------------------------------------------------------------------------------------------------
		[HttpGet("GetName")]
		public async Task<ActionResult<CEntityName>> GetName(int ID)
		{
			CEntityName											Name=await MContext.EntitiesNames.Where(P => P.ID==ID).FirstOrDefaultAsync();

			if (Name!=null)
			{
				ActionResult<CEntityName>						Response=Ok(Name);

				return(Response);
			}
			else
			{
				ActionResult<CEntityName>						Response=NotFound();

				return(Response);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		[HttpPost("InsertName")]
		public async Task<ActionResult<CEntityName>> InsertName(CEntityName Name)
		{
			MContext.EntitiesNames.Add(Name);

			await MContext.SaveChangesAsync();

			ActionResult<CEntityName>							Result=CreatedAtAction(nameof(GetName),Name);

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		[HttpPut("UpdateName")]
		public async Task<ActionResult> UpdateName(CEntityName Name)
		{
			MContext.Entry(Name).State=EntityState.Modified;

			await MContext.SaveChangesAsync();

			ActionResult										Result=NoContent();

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		[HttpDelete("DeleteName")]
		public async Task<ActionResult> DeleteName(int ID)
		{
			// !!!!! METHOD [Task<int> ExecuteDeleteAsync<TSource>(this IQueryable<TSource> Source, CancellationToken CancellationToken)] umoznuje vykonat DELETE ENTITY OBJECT BEZ nutnosti jeho nacitania do DB CONTEXT.
			int													NumberOfDeletedItems=await MContext.EntitiesNames.Where(P => P.ID==ID).ExecuteDeleteAsync();

			if (NumberOfDeletedItems==1)
			{
				ActionResult									Response=NoContent();

				return(Response);
			}
			else
			{
				ActionResult									Response=NotFound();

				return(Response);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------