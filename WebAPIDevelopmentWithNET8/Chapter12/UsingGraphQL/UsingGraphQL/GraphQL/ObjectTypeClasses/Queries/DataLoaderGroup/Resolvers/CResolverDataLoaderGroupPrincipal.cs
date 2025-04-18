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
	public sealed class CResolverDataLoaderGroupPrincipal
	{
//----------------------------------------------------------------------------------------------------------------------
		public async Task<CDataLoaderGroupPrincipal> FieldResolverDelegatePrincipal(IResolverContext Context, IMyLoggerService MyLoggerService)
		{
			MyLoggerService.LogResolver(nameof(CResolverDataLoaderGroupPrincipal),nameof(FieldResolverDelegatePrincipal));

			// !!!!! PARAMETER sa cita z ARGUMENT.
			int													ID=Context.ArgumentValue<int>("id");

			// !!!!!! Kvoli THREAD SAFETY sa MUSI pouzivat TYPE [IDbContextFactory<TDbContext>], ktory reprezentuje DB CONTEXT POOL FACTORY.
			IDbContextFactory<CDBContext>						DBContextFactory=Context.Service<IDbContextFactory<CDBContext>>();

			// !!!!! Z DB CONTEXT POOL sa vyberie DB CONTEXT.
			// !!!!! MUSI sa pouzit USING SYNTAX, lebo iba pri DISPOSE sa vrati DB CONTEXT OBJECT spat do DB CONTEXT POOL.
			using(CDBContext DBContext=await DBContextFactory.CreateDbContextAsync())
			{
				CEntityDataLoaderGroupPrincipal					EntityChildObject=await DBContext.EntitiesDataLoaderGroupPrincipal.Where(P => P.EntityPrincipalID==ID).FirstOrDefaultAsync();

				if (EntityChildObject!=null)
				{
					CDataLoaderGroupPrincipal					Result=new CDataLoaderGroupPrincipal(EntityChildObject.EntityPrincipalID,EntityChildObject.EntityPrincipalValue1,EntityChildObject.EntityPrincipalValue2);

					return(Result);
				}
				else
				{
					return(null);
				}
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public async Task<CDataLoaderGroupPrincipal[]> FieldResolverDelegatePrincipalArray(IResolverContext Context, IMyLoggerService MyLoggerService)
		{
			MyLoggerService.LogResolver(nameof(CResolverDataLoaderGroupPrincipal),nameof(FieldResolverDelegatePrincipalArray));

			// !!!!!! Kvoli THREAD SAFETY sa MUSI pouzivat TYPE [IDbContextFactory<TDbContext>], ktory reprezentuje DB CONTEXT POOL FACTORY.
			IDbContextFactory<CDBContext>						DBContextFactory=Context.Service<IDbContextFactory<CDBContext>>();

			// !!!!! Z DB CONTEXT POOL sa vyberie DB CONTEXT.
			// !!!!! MUSI sa pouzit USING SYNTAX, lebo iba pri DISPOSE sa vrati DB CONTEXT OBJECT spat do DB CONTEXT POOL.
			using(CDBContext DBContext=await DBContextFactory.CreateDbContextAsync())
			{
				CEntityDataLoaderGroupPrincipal[]				EntityChildObjects=await DBContext.EntitiesDataLoaderGroupPrincipal.ToArrayAsync();

				if (EntityChildObjects!=null)
				{
					CDataLoaderGroupPrincipal[]					Result=EntityChildObjects.Select(P => new CDataLoaderGroupPrincipal(P.EntityPrincipalID,P.EntityPrincipalValue1,P.EntityPrincipalValue2)).ToArray();

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