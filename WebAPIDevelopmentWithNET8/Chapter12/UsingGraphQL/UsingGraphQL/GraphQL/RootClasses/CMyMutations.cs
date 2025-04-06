using System.Threading.Tasks;
using HotChocolate;
using Microsoft.EntityFrameworkCore;
//----------------------------------------------------------------------------------------------------------------------
namespace UsingGraphQL
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class CMyMutations
	{
//----------------------------------------------------------------------------------------------------------------------
		public async Task<CMutationsAddNamePayload> MyAddNameAsync(CMutationsAddNameInput MyInput, [Service] IDbContextFactory<CDBContext> DBContextFactory)
		{
			// !!!!! Z DB CONTEXT POOL sa vyberie DB CONTEXT.
			// !!!!! MUSI sa pouzit USING SYNTAX, lebo iba pri DISPOSE sa vrati DB CONTEXT OBJECT spat do DB CONTEXT POOL.
			using(CDBContext DBContext=await DBContextFactory.CreateDbContextAsync())
			{
				CEntityName										EntityObject=new CEntityName(MyInput.FirstName,MyInput.LastName,MyInput.Age,MyInput.Sex);

				DBContext.EntitiesNames.Add(EntityObject);

				await DBContext.SaveChangesAsync();

				CMutationsAddNamePayload						Payload=new CMutationsAddNamePayload(EntityObject.ID,EntityObject.FirstName,EntityObject.LastName,EntityObject.Age,EntityObject.Sex);

				return(Payload);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------