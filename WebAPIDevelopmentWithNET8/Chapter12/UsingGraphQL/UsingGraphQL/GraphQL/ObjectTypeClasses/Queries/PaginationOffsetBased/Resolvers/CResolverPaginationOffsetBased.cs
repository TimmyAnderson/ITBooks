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
	// !!!!! Aby nad OBJECTS bolo mozne vykonat PAGINATION, FILTERING a SORTING, je NUTNE VRATIT TYPE [IQueryable<TType>].
	// !!!!! MUSIA sa vracat ENTITY OBJECTS a nie DATA OBJECTS, inak by sa PAGINATION, FILTERING a SORTING robil v MEMORY, a NIE nad DATABASE.
	public sealed class CResolverPaginationOffsetBased
	{
//----------------------------------------------------------------------------------------------------------------------
		public async Task<IQueryable<CEntityPaginationOffsetBased>> FieldResolverDelegateArray(IResolverContext Context)
		{
			// !!! SERVICE sa ziska PROGRAMOVO.
			IMyLoggerService									MyLoggerService=Context.Service<IMyLoggerService>();

			MyLoggerService.LogResolver(nameof(CResolverPaginationOffsetBased),nameof(FieldResolverDelegateArray));

			// !!!!!! Kvoli THREAD SAFETY sa MUSI pouzivat TYPE [IDbContextFactory<TDbContext>], ktory reprezentuje DB CONTEXT POOL FACTORY.
			IDbContextFactory<CDBContext>						DBContextFactory=Context.Service<IDbContextFactory<CDBContext>>();

			// !!!!! Z DB CONTEXT POOL sa vyberie DB CONTEXT.
			CDBContext											DBContext=await DBContextFactory.CreateDbContextAsync();

			IQueryable<CEntityPaginationOffsetBased>			Result=DBContext.EntitiesPaginationOffsetBased.AsQueryable();

			// !!!!! DB CONTEXT sa NESMIE UVOLNIT volanim METHOD [IDisposable.Dispose()], inak by sa QUERY nemala ako vykonat.

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------