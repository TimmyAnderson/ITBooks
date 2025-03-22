using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore.ChangeTracking;
//----------------------------------------------------------------------------------------------------------------------
namespace DataAccess2Web
{
//----------------------------------------------------------------------------------------------------------------------
	[ApiController]
	[Route("[controller]")]
	public class OneToOneController : ControllerBase
	{
//----------------------------------------------------------------------------------------------------------------------
		private readonly CDBContext								MContext;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public OneToOneController(CDBContext Context)
		{
			MContext=Context;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		[HttpGet("GetEntities")]
		public async Task<ActionResult<CEntityOneToOnePrincipal[]>> GetEntities()
		{
			CEntityOneToOnePrincipal[]							EntitiesPrincipal=await MContext.EntitiesOneToOnePrincipal.Include(P => P.EntityDependent).ToArrayAsync();
			ActionResult<CEntityOneToOnePrincipal[]>			Response=Ok(EntitiesPrincipal);

			return(Response);
		}
//----------------------------------------------------------------------------------------------------------------------
		[HttpGet("GetEntity")]
		public async Task<ActionResult<CEntityOneToOnePrincipal>> GetEntity(int ID)
		{
			CEntityOneToOnePrincipal							EntityPrincipal=await MContext.EntitiesOneToOnePrincipal.Include(P => P.EntityDependent).Where(P => P.EntityPrincipalID==ID).FirstOrDefaultAsync();

			if (EntityPrincipal!=null)
			{
				ActionResult<CEntityOneToOnePrincipal>			Response=Ok(EntityPrincipal);

				return(Response);
			}
			else
			{
				ActionResult<CEntityOneToOnePrincipal>			Response=NotFound();

				return(Response);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		[HttpPost("InsertEntity")]
		public async Task<ActionResult<CEntityOneToOnePrincipal>> InsertEntity(CEntityOneToOnePrincipal EntityPricipal)
		{
			MContext.EntitiesOneToOnePrincipal.Add(EntityPricipal);

			await MContext.SaveChangesAsync();

			ActionResult<CEntityOneToOnePrincipal>				Result=CreatedAtAction(nameof(InsertEntity),EntityPricipal);

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		[HttpPut("UpdateEntity")]
		public async Task<ActionResult> UpdateEntity(CEntityOneToOnePrincipal EntityPricipal)
		{
			MContext.Entry(EntityPricipal).State=EntityState.Modified;

			if (EntityPricipal.EntityDependent!=null)
			{
				MContext.Entry(EntityPricipal.EntityDependent).State=EntityState.Modified;
			}

			await MContext.SaveChangesAsync();

			ActionResult										Result=NoContent();

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		[HttpDelete("DeleteEntity")]
		public async Task<ActionResult> DeleteEntity(int ID)
		{
			// !!!!! METHOD [Task<int> ExecuteDeleteAsync<TSource>(this IQueryable<TSource> Source, CancellationToken CancellationToken)] umoznuje vykonat DELETE ENTITY OBJECT BEZ nutnosti jeho nacitania do DB CONTEXT.
			int													NumberOfDeletedItems=await MContext.EntitiesOneToOnePrincipal.Where(P => P.EntityPrincipalID==ID).ExecuteDeleteAsync();

			if (NumberOfDeletedItems>0)
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