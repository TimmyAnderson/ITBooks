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
	public class OwnedTypeOneToManyController : ControllerBase
	{
//----------------------------------------------------------------------------------------------------------------------
		private readonly CDBContext								MContext;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public OwnedTypeOneToManyController(CDBContext Context)
		{
			MContext=Context;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		[HttpGet("GetEntities")]
		public async Task<ActionResult<CEntityOwnedOneToManyPrincipal[]>> GetEntities()
		{
			CEntityOwnedOneToManyPrincipal[]					EntitiesPrincipal=await MContext.EntitiesOwnedOneToManyPrincipal.ToArrayAsync();
			ActionResult<CEntityOwnedOneToManyPrincipal[]>		Response=Ok(EntitiesPrincipal);

			return(Response);
		}
//----------------------------------------------------------------------------------------------------------------------
		[HttpGet("GetEntity")]
		public async Task<ActionResult<CEntityOwnedOneToManyPrincipal>> GetEntity(int ID)
		{
			CEntityOwnedOneToManyPrincipal						EntityPrincipal=await MContext.EntitiesOwnedOneToManyPrincipal.Where(P => P.EntityPrincipalID==ID).FirstOrDefaultAsync();

			if (EntityPrincipal!=null)
			{
				ActionResult<CEntityOwnedOneToManyPrincipal>	Response=Ok(EntityPrincipal);

				return(Response);
			}
			else
			{
				ActionResult<CEntityOwnedOneToManyPrincipal>	Response=NotFound();

				return(Response);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		[HttpPost("InsertEntity")]
		public async Task<ActionResult<CEntityOwnedOneToManyPrincipal>> InsertEntity(CEntityOwnedOneToManyPrincipal EntityPricipal)
		{
			MContext.EntitiesOwnedOneToManyPrincipal.Add(EntityPricipal);

			await MContext.SaveChangesAsync();

			ActionResult<CEntityOwnedOneToManyPrincipal>		Result=CreatedAtAction(nameof(InsertEntity),EntityPricipal);

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		[HttpPut("UpdateEntity")]
		public async Task<ActionResult> UpdateEntity(CEntityOwnedOneToManyPrincipal EntityPricipal)
		{
			MContext.Entry(EntityPricipal).State=EntityState.Modified;

			if (EntityPricipal.EntitiesDependent!=null)
			{
				foreach(CEntityOwnedOneToManyDependent EntityDependent in EntityPricipal.EntitiesDependent)
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
			int													NumberOfDeletedItems=await MContext.EntitiesOwnedOneToManyPrincipal.Where(P => P.EntityPrincipalID==ID).ExecuteDeleteAsync();

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