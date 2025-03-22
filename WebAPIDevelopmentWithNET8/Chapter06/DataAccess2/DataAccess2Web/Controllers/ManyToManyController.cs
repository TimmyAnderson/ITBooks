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
	public class ManyToManyController : ControllerBase
	{
//----------------------------------------------------------------------------------------------------------------------
		private readonly CDBContext								MContext;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public ManyToManyController(CDBContext Context)
		{
			MContext=Context;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		[HttpGet("GetEntities")]
		public async Task<ActionResult<CEntityManyToManyM[]>> GetEntities()
		{
			CEntityManyToManyM[]								Entities=await MContext.EntitiesManyToManyM.Include(P => P.EntitiesMN).ThenInclude(P => P.EntityN).ToArrayAsync();
			ActionResult<CEntityManyToManyM[]>					Response=Ok(Entities);

			return(Response);
		}
//----------------------------------------------------------------------------------------------------------------------
		[HttpGet("GetEntityM")]
		public async Task<ActionResult<CEntityManyToManyM>> GetEntityM(int ID)
		{
			CEntityManyToManyM									Entity=await MContext.EntitiesManyToManyM.Include(P => P.EntitiesMN).ThenInclude(P => P.EntityN).Where(P => P.EntityMID==ID).FirstOrDefaultAsync();

			if (Entity!=null)
			{
				ActionResult<CEntityManyToManyM>				Response=Ok(Entity);

				return(Response);
			}
			else
			{
				ActionResult<CEntityManyToManyM>				Response=NotFound();

				return(Response);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		[HttpGet("GetEntityN")]
		public async Task<ActionResult<CEntityManyToManyN>> GetEntityN(int ID)
		{
			CEntityManyToManyN									Entity=await MContext.EntitiesManyToManyN.Include(P => P.EntitiesMN).ThenInclude(P => P.EntityM).Where(P => P.EntityNID==ID).FirstOrDefaultAsync();

			if (Entity!=null)
			{
				ActionResult<CEntityManyToManyN>				Response=Ok(Entity);

				return(Response);
			}
			else
			{
				ActionResult<CEntityManyToManyN>				Response=NotFound();

				return(Response);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		[HttpGet("GetEntityMN")]
		public async Task<ActionResult<CEntityManyToManyMN>> GetEntityMN(int ID)
		{
			CEntityManyToManyMN									Entity=await MContext.EntitiesManyToManyMN.Include(P => P.EntityM).Include(P => P.EntityN).Where(P => P.EntityMNID==ID).FirstOrDefaultAsync();

			if (Entity!=null)
			{
				ActionResult<CEntityManyToManyMN>				Response=Ok(Entity);

				return(Response);
			}
			else
			{
				ActionResult<CEntityManyToManyMN>				Response=NotFound();

				return(Response);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		[HttpPost("InsertEntity")]
		public async Task<ActionResult<CEntityManyToManyMN>> InsertEntity(CEntityManyToManyMN Entity)
		{
			MContext.EntitiesManyToManyMN.Add(Entity);

			await MContext.SaveChangesAsync();

			ActionResult<CEntityManyToManyMN>					Result=CreatedAtAction(nameof(InsertEntity),Entity);

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		[HttpPut("UpdateEntity")]
		public async Task<ActionResult> UpdateEntity(CEntityManyToManyMN EntityMN)
		{
			CEntityManyToManyMN									EntityMNInDB=await MContext.EntitiesManyToManyMN.Include(P => P.EntityM).Include(P => P.EntityN).Where(P => P.EntityMNID==EntityMN.EntityMNID).FirstOrDefaultAsync();

			if (EntityMNInDB!=null)
			{
				EntityEntry<CEntityManyToManyMN>				EntryMN=MContext.Entry(EntityMNInDB);

				EntryMN.CurrentValues.SetValues(EntityMN);

				CEntityManyToManyM								EntityMInDB=EntityMNInDB.EntityM;

				if (EntityMInDB!=null)
				{
					if (EntityMN.EntityM!=null)
					{
						EntityEntry<CEntityManyToManyM>			EntryM=MContext.Entry(EntityMInDB);

						EntryM.CurrentValues.SetValues(EntityMN.EntityM);
					}
				}
				else
				{
					EntityMInDB=EntityMN.EntityM;
				}

				CEntityManyToManyN								EntityNInDB=EntityMNInDB.EntityN;

				if (EntityNInDB!=null)
				{
					if (EntityMN.EntityN!=null)
					{
						EntityEntry<CEntityManyToManyN>			EntryN=MContext.Entry(EntityNInDB);

						EntryN.CurrentValues.SetValues(EntityMN.EntityN);
					}
				}
				else
				{
					EntityMInDB=EntityMN.EntityM;
				}

				await MContext.SaveChangesAsync();

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
		[HttpDelete("DeleteEntityM")]
		public async Task<ActionResult> DeleteEntityM(int ID)
		{
			// !!!!! METHOD [Task<int> ExecuteDeleteAsync<TSource>(this IQueryable<TSource> Source, CancellationToken CancellationToken)] umoznuje vykonat DELETE ENTITY OBJECT BEZ nutnosti jeho nacitania do DB CONTEXT.
			int													NumberOfDeletedItems=await MContext.EntitiesManyToManyM.Where(P => P.EntityMID==ID).ExecuteDeleteAsync();

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
		[HttpDelete("DeleteEntityN")]
		public async Task<ActionResult> DeleteEntityN(int ID)
		{
			// !!!!! METHOD [Task<int> ExecuteDeleteAsync<TSource>(this IQueryable<TSource> Source, CancellationToken CancellationToken)] umoznuje vykonat DELETE ENTITY OBJECT BEZ nutnosti jeho nacitania do DB CONTEXT.
			int													NumberOfDeletedItems=await MContext.EntitiesManyToManyN.Where(P => P.EntityNID==ID).ExecuteDeleteAsync();

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
		[HttpDelete("DeleteEntityMN")]
		public async Task<ActionResult> DeleteEntityMN(int ID)
		{
			// !!!!! METHOD [Task<int> ExecuteDeleteAsync<TSource>(this IQueryable<TSource> Source, CancellationToken CancellationToken)] umoznuje vykonat DELETE ENTITY OBJECT BEZ nutnosti jeho nacitania do DB CONTEXT.
			int													NumberOfDeletedItems=await MContext.EntitiesManyToManyMN.Where(P => P.EntityMNID==ID).ExecuteDeleteAsync();

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