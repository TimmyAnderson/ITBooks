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
	public sealed class CResolverDataLoaderBatchPrincipal
	{
//----------------------------------------------------------------------------------------------------------------------
		public async Task<CDataLoaderBatchPrincipal> FieldResolverDelegatePrincipal(IResolverContext Context, IMyLoggerService MyLoggerService)
		{
			MyLoggerService.LogResolver(nameof(CResolverDataLoaderBatchPrincipal),nameof(FieldResolverDelegatePrincipal));

			// !!!!! PARAMETER sa cita z ARGUMENT.
			int													ID=Context.ArgumentValue<int>("id");

			// !!!!!! Kvoli THREAD SAFETY sa MUSI pouzivat TYPE [IDbContextFactory<TDbContext>], ktory reprezentuje DB CONTEXT POOL FACTORY.
			IDbContextFactory<CDBContext>						DBContextFactory=Context.Service<IDbContextFactory<CDBContext>>();

			// !!!!! Z DB CONTEXT POOL sa vyberie DB CONTEXT.
			// !!!!! MUSI sa pouzit USING SYNTAX, lebo iba pri DISPOSE sa vrati DB CONTEXT OBJECT spat do DB CONTEXT POOL.
			using(CDBContext DBContext=await DBContextFactory.CreateDbContextAsync())
			{
				CEntityDataLoaderBatchPrincipal					EntityChildObject=await DBContext.EntitiesDataLoaderBatchPrincipal.Where(P => P.EntityPrincipalID==ID).FirstOrDefaultAsync();

				if (EntityChildObject!=null)
				{
					CDataLoaderBatchPrincipal					Result=new CDataLoaderBatchPrincipal(EntityChildObject.EntityPrincipalID,EntityChildObject.EntityPrincipalValue1,EntityChildObject.EntityPrincipalValue2);

					return(Result);
				}
				else
				{
					return(null);
				}
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public async Task<CDataLoaderBatchPrincipal[]> FieldResolverDelegatePrincipalArray(IResolverContext Context)
		{
			Console.WriteLine($"!!!!!!!!!! RESOLVER [{nameof(FieldResolverDelegatePrincipalArray)}] is EXECUTING on THREAD [{Thread.CurrentThread.ManagedThreadId}].");

			// !!!!!! Kvoli THREAD SAFETY sa MUSI pouzivat TYPE [IDbContextFactory<TDbContext>], ktory reprezentuje DB CONTEXT POOL FACTORY.
			IDbContextFactory<CDBContext>						DBContextFactory=Context.Service<IDbContextFactory<CDBContext>>();

			// !!!!! Z DB CONTEXT POOL sa vyberie DB CONTEXT.
			// !!!!! MUSI sa pouzit USING SYNTAX, lebo iba pri DISPOSE sa vrati DB CONTEXT OBJECT spat do DB CONTEXT POOL.
			using(CDBContext DBContext=await DBContextFactory.CreateDbContextAsync())
			{
				CEntityDataLoaderBatchPrincipal[]				EntityChildObjects=await DBContext.EntitiesDataLoaderBatchPrincipal.ToArrayAsync();

				if (EntityChildObjects!=null)
				{
					CDataLoaderBatchPrincipal[]					Result=EntityChildObjects.Select(P => new CDataLoaderBatchPrincipal(P.EntityPrincipalID,P.EntityPrincipalValue1,P.EntityPrincipalValue2)).ToArray();

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