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
	// !!!!! Aby nad OBJECTS bolo mozne vykonat SORTING, je NUTNE VRATIT TYPE [IQueryable<TType>].
	// !!!!! MUSIA sa vracat ENTITY OBJECTS a nie DATA OBJECTS, inak by sa SORTING robil v MEMORY, a NIE nad DATABASE.
	public sealed class CResolverSortingByConvention
	{
//----------------------------------------------------------------------------------------------------------------------
		public async Task<IQueryable<CEntitySortingByConvention>> FieldResolverDelegateArray(IResolverContext Context)
		{
			// !!! SERVICE sa ziska PROGRAMOVO.
			IMyLoggerService									MyLoggerService=Context.Service<IMyLoggerService>();

			MyLoggerService.LogResolver(nameof(CResolverSortingByConvention),nameof(FieldResolverDelegateArray));

			// !!!!!! Kvoli THREAD SAFETY sa MUSI pouzivat TYPE [IDbContextFactory<TDbContext>], ktory reprezentuje DB CONTEXT POOL FACTORY.
			IDbContextFactory<CDBContext>						DBContextFactory=Context.Service<IDbContextFactory<CDBContext>>();

			// !!!!! Z DB CONTEXT POOL sa vyberie DB CONTEXT.
			CDBContext											DBContext=await DBContextFactory.CreateDbContextAsync();

			IQueryable<CEntitySortingByConvention>				Result=DBContext.EntitiesSortingByConvention.AsQueryable();

			// !!!!! DB CONTEXT sa NESMIE UVOLNIT volanim METHOD [IDisposable.Dispose()], inak by sa QUERY nemala ako vykonat.

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------