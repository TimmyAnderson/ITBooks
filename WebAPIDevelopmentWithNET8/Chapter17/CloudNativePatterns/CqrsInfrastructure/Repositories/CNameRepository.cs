using System.Linq;
using System.Threading.Tasks;
using CqrsCore;
using Microsoft.EntityFrameworkCore;
//----------------------------------------------------------------------------------------------------------------------
namespace CqrsInfrastructure
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class CNameRepository : INameRepository
	{
//----------------------------------------------------------------------------------------------------------------------
		private readonly CDBContext								MContext;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CNameRepository(CDBContext Context)
		{
			MContext=Context;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public async Task<CDtoFullName[]> GetNames()
		{
			CEntityName[]										Names=await MContext.EntitiesNames.ToArrayAsync();
			CDtoFullName[]										FullNames=Names.Select(P => new CDtoFullName(P.ID,P.FirstName,P.LastName,P.Age,(EDtoSex)P.Sex)).ToArray();

			return(FullNames);
		}
//----------------------------------------------------------------------------------------------------------------------
		public async Task<CDtoFullName> GetName(int ID)
		{
			CEntityName											NameFromDB=await MContext.EntitiesNames.Where(P => P.ID==ID).FirstOrDefaultAsync();

			if (NameFromDB!=null)
			{
				CDtoFullName									FullName=new CDtoFullName(NameFromDB.ID,NameFromDB.FirstName,NameFromDB.LastName,NameFromDB.Age,(EDtoSex)NameFromDB.Sex);

				return(FullName);
			}
			else
			{
				return(null);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public async Task<CDtoFullName> InsertName(CDtoNameToInsert Name)
		{
			CEntityName											EntityName=new CEntityName(Name.FirstName,Name.LastName,Name.Age,(EEntitySex)Name.Sex);

			MContext.EntitiesNames.Add(EntityName);

			await MContext.SaveChangesAsync();

			CDtoFullName										FullName=new CDtoFullName(EntityName.ID,EntityName.FirstName,EntityName.LastName,EntityName.Age,(EDtoSex)EntityName.Sex);

			return(FullName);
		}
//----------------------------------------------------------------------------------------------------------------------
		public async Task<CDtoFullName> UpdateName(CDtoNameToUpdate Name)
		{
			CEntityName											NameFromDB=await MContext.EntitiesNames.Where(P => P.ID==Name.ID).FirstOrDefaultAsync();

			if (NameFromDB!=null)
			{
				NameFromDB.FirstName=Name.FirstName;
				NameFromDB.LastName=Name.LastName;
				NameFromDB.Age=Name.Age;
				NameFromDB.Sex=(EEntitySex) Name.Sex;

				await MContext.SaveChangesAsync();

				CDtoFullName									FullName=new CDtoFullName(Name.ID,Name.FirstName,Name.LastName,Name.Age,Name.Sex);

				return(FullName);
			}
			else
			{
				return(null);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public async Task DeleteName(int ID)
		{
			await MContext.EntitiesNames.Where(P => P.ID==ID).ExecuteDeleteAsync();
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------