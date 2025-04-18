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
	public sealed class CResolverFilteringByFluentAPIExplicit
	{
//----------------------------------------------------------------------------------------------------------------------
		// !!!!! Aby nad OBJECTS bolo mozne vykonat FILTERING, je NUTNE VRATIT TYPE [IQueryable<TType>].
		// !!!!! MUSIA sa vracat ENTITY OBJECTS a nie DATA OBJECTS, inak by sa FILTERING robil v MEMORY, a NIE nad DATABASE.
		public async Task<IQueryable<CEntityFilteringByFluentAPIExplicit>> FieldResolverDelegateFilteringByFluentAPIExplicitArray(IResolverContext Context, CancellationToken CancellationToken, IMyLoggerService MyLoggerService)
		{
			MyLoggerService.LogResolver(nameof(CResolverFilteringByFluentAPIExplicit),nameof(FieldResolverDelegateFilteringByFluentAPIExplicitArray));

			// !!!!!! Kvoli THREAD SAFETY sa MUSI pouzivat TYPE [IDbContextFactory<TDbContext>], ktory reprezentuje DB CONTEXT POOL FACTORY.
			IDbContextFactory<CDBContext>						DBContextFactory=Context.Service<IDbContextFactory<CDBContext>>();

			// !!!!! Z DB CONTEXT POOL sa vyberie DB CONTEXT.
			CDBContext											DBContext=await DBContextFactory.CreateDbContextAsync();
			IQueryable<CEntityFilteringByFluentAPIExplicit>		QueryableResult=DBContext.EntitiesFilteringByFluentAPIExplicit.AsQueryable();

			// !!!!! DB CONTEXT sa NESMIE UVOLNIT volanim METHOD [IDisposable.Dispose()], inak by sa QUERY nemala ako vykonat.

			return(QueryableResult);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------