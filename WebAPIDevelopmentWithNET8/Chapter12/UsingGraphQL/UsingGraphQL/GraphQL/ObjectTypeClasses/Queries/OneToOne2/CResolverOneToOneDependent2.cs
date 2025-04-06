using System;
using System.Linq;
using System.Threading;
using System.Threading.Tasks;
using HotChocolate.Resolvers;
using HotChocolate.Types;
using Microsoft.EntityFrameworkCore;
//----------------------------------------------------------------------------------------------------------------------
namespace UsingGraphQL
{
//----------------------------------------------------------------------------------------------------------------------
	// !!! CLASS predstavuje OBJECT TYPE pre DATA CLASS TYPE [COneToOneDependent2].
	public sealed class CResolverOneToOneDependent2
	{
//----------------------------------------------------------------------------------------------------------------------
		public async Task<COneToOneDependent2> FieldResolverDelegateDependent(IResolverContext Context)
		{
			Console.WriteLine($"!!!!!!!!!! RESOLVER [{nameof(CResolverOneToOneDependent2)}] is EXECUTING on THREAD [{Thread.CurrentThread.ManagedThreadId}].");

			// !!! Ziska sa PARENT OBJECT.
			COneToOnePrincipal2									ParentObject=Context.Parent<COneToOnePrincipal2>();

			// !!!!!! Kvoli THREAD SAFETY sa MUSI pouzivat TYPE [IDbContextFactory<TDbContext>], ktory reprezentuje DB CONTEXT POOL FACTORY.
			IDbContextFactory<CDBContext>						DBContextFactory=Context.Service<IDbContextFactory<CDBContext>>();

			// !!!!! Z DB CONTEXT POOL sa vyberie DB CONTEXT.
			// !!!!! MUSI sa pouzit USING SYNTAX, lebo iba pri DISPOSE sa vrati DB CONTEXT OBJECT spat do DB CONTEXT POOL.
			using(CDBContext DBContext=await DBContextFactory.CreateDbContextAsync())
			{
				Console.WriteLine($"READING TYPE [{nameof(CEntityOneToOneDependent2)}] for ID [{ParentObject.PrincipalID}].");

				CEntityOneToOneDependent2						EntityChildObject=await DBContext.EntitiesOneToOneDependent2.Where(P => P.EntityPrincipalID==ParentObject.PrincipalID).FirstOrDefaultAsync();

				if (EntityChildObject!=null)
				{
					COneToOneDependent2							Result=new COneToOneDependent2(EntityChildObject.EntityDependentID,EntityChildObject.EntityDependentValue);

					return(Result);
				}
				else
				{
					return(null);
				}
			}
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------