using System.Threading.Tasks;
using HotChocolate;
//----------------------------------------------------------------------------------------------------------------------
namespace UsingGraphQL
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class CMyMutations
	{
//----------------------------------------------------------------------------------------------------------------------
		public async Task<CMutationsAddNamePayload> MyAddNameAsync(CMutationsAddNameInput MyInput, [Service] CDBContext Context)
		{
			CEntityName											EntityObject=new CEntityName(MyInput.FirstName,MyInput.LastName,MyInput.Age,MyInput.Sex);

			Context.EntitiesNames.Add(EntityObject);

			await Context.SaveChangesAsync();

			CMutationsAddNamePayload							Payload=new CMutationsAddNamePayload(EntityObject.ID,EntityObject.FirstName,EntityObject.LastName,EntityObject.Age,EntityObject.Sex);

			return(Payload);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------