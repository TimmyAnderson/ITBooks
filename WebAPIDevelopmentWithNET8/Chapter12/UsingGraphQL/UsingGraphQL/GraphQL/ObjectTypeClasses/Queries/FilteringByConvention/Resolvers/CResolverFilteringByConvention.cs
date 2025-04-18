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
	public sealed class CResolverFilteringByConvention
	{
//----------------------------------------------------------------------------------------------------------------------
		// !!!!! Aby nad OBJECTS bolo mozne vykonat FILTERING, je NUTNE VRATIT TYPE [IQueryable<TType>].
		// !!!!! MUSIA sa vracat ENTITY OBJECTS a nie DATA OBJECTS, inak by sa FILTERING robil v MEMORY, a NIE nad DATABASE.
		public async Task<IQueryable<CEntityFilteringByConvention>> FieldResolverDelegateFilteringByConventionArray(IResolverContext Context, CancellationToken CancellationToken, IMyLoggerService MyLoggerService)
		{
			MyLoggerService.LogResolver(nameof(CResolverFilteringByConvention),nameof(FieldResolverDelegateFilteringByConventionArray));

			// !!!!!! Kvoli THREAD SAFETY sa MUSI pouzivat TYPE [IDbContextFactory<TDbContext>], ktory reprezentuje DB CONTEXT POOL FACTORY.
			IDbContextFactory<CDBContext>						DBContextFactory=Context.Service<IDbContextFactory<CDBContext>>();

			// !!!!! Z DB CONTEXT POOL sa vyberie DB CONTEXT.
			CDBContext											DBContext=await DBContextFactory.CreateDbContextAsync();
			IQueryable<CEntityFilteringByConvention>			QueryableResult=DBContext.EntitiesFilteringByConvention.AsQueryable();

			// !!!!! DB CONTEXT sa NESMIE UVOLNIT volanim METHOD [IDisposable.Dispose()], inak by sa QUERY nemala ako vykonat.

			return(QueryableResult);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------