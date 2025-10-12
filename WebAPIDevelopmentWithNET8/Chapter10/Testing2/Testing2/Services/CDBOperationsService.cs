using System.Linq;
using System.Threading.Tasks;
using Microsoft.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore.ChangeTracking;
//----------------------------------------------------------------------------------------------------------------------
namespace Testing2
{
//----------------------------------------------------------------------------------------------------------------------
	public class CDBOperationsService : IDBOperationsService
	{
//----------------------------------------------------------------------------------------------------------------------
		private readonly CDBContext								MContext;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CDBOperationsService(CDBContext Context)
		{
			MContext=Context;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public async Task<CEntityName[]> GetNames()
		{
			CEntityName[]										Names=await MContext.EntitiesNames.ToArrayAsync();

			return(Names);
		}
//----------------------------------------------------------------------------------------------------------------------
		public async Task<CEntityName> GetName(int ID)
		{
			CEntityName											Name=await MContext.EntitiesNames.Where(P => P.ID==ID).FirstOrDefaultAsync();

			return(Name);
		}
//----------------------------------------------------------------------------------------------------------------------
		public async Task<CEntityName> InsertName(CEntityName Name)
		{
			MContext.EntitiesNames.Add(Name);

			await MContext.SaveChangesAsync();

			return(Name);
		}
//----------------------------------------------------------------------------------------------------------------------
		public async Task<CEntityName> UpdateName(CNonEntityName Name)
		{
			CEntityName											NameFromDB=await MContext.EntitiesNames.Where(P => P.ID==Name.ID).FirstOrDefaultAsync();

			if (NameFromDB!=null)
			{
				EntityEntry<CEntityName>						Entry=MContext.Entry(NameFromDB);

				// !!!!! METHOD nastavi z NON-ENTITY CLASS [CNonEntityName] PROPERTIES v ENTITY CLASS [CEntityName] na zaklade zhodnosti NAME a TYPE jednotlovych PROPERTIES.
				Entry.CurrentValues.SetValues(Name);

				await MContext.SaveChangesAsync();
			}

			return(NameFromDB);
		}
//----------------------------------------------------------------------------------------------------------------------
		public async Task<bool> DeleteName(int ID)
		{
			// !!!!! METHOD [Task<int> ExecuteDeleteAsync<TSource>(this IQueryable<TSource> Source, CancellationToken CancellationToken)] umoznuje vykonat DELETE ENTITY OBJECT BEZ nutnosti jeho nacitania do DB CONTEXT.
			int													NumberOfDeletedItems=await MContext.EntitiesNames.Where(P => P.ID==ID).ExecuteDeleteAsync();

			if (NumberOfDeletedItems==1)
			{
				return(true);
			}
			else
			{
				return(false);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------