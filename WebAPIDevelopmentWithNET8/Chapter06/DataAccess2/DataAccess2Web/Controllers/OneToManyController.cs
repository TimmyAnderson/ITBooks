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
	public class OneToManyController : ControllerBase
	{
//----------------------------------------------------------------------------------------------------------------------
		private readonly CDBContext								MContext;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public OneToManyController(CDBContext Context)
		{
			MContext=Context;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		[HttpGet("GetEntities")]
		public async Task<ActionResult<CEntityOneToManyPrincipal[]>> GetEntities()
		{
			CEntityOneToManyPrincipal[]							EntitiesPrincipal=await MContext.EntitiesOneToManyPrincipal.Include(P => P.EntitiesDependent).ToArrayAsync();
			ActionResult<CEntityOneToManyPrincipal[]>			Response=Ok(EntitiesPrincipal);

			return(Response);
		}
//----------------------------------------------------------------------------------------------------------------------
		[HttpGet("GetEntity")]
		public async Task<ActionResult<CEntityOneToManyPrincipal>> GetEntity(int ID)
		{
			CEntityOneToManyPrincipal							EntityPrincipal=await MContext.EntitiesOneToManyPrincipal.Include(P => P.EntitiesDependent).Where(P => P.EntityPrincipalID==ID).FirstOrDefaultAsync();

			if (EntityPrincipal!=null)
			{
				ActionResult<CEntityOneToManyPrincipal>			Response=Ok(EntityPrincipal);

				return(Response);
			}
			else
			{
				ActionResult<CEntityOneToManyPrincipal>			Response=NotFound();

				return(Response);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		[HttpPost("InsertEntity")]
		public async Task<ActionResult<CEntityOneToManyPrincipal>> InsertEntity(CEntityOneToManyPrincipal EntityPricipal)
		{
			MContext.EntitiesOneToManyPrincipal.Add(EntityPricipal);

			await MContext.SaveChangesAsync();

			ActionResult<CEntityOneToManyPrincipal>				Result=CreatedAtAction(nameof(InsertEntity),EntityPricipal);

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		[HttpPut("UpdateEntity")]
		public async Task<ActionResult> UpdateEntity(CEntityOneToManyPrincipal EntityPricipal)
		{
			MContext.Entry(EntityPricipal).State=EntityState.Modified;

			if (EntityPricipal.EntitiesDependent!=null)
			{
				foreach(CEntityOneToManyDependent EntityDependent in EntityPricipal.EntitiesDependent)
				{
					MContext.Entry(EntityDependent).State=EntityState.Modified;
				}
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
			int													NumberOfDeletedItems=await MContext.EntitiesOneToManyPrincipal.Where(P => P.EntityPrincipalID==ID).ExecuteDeleteAsync();

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