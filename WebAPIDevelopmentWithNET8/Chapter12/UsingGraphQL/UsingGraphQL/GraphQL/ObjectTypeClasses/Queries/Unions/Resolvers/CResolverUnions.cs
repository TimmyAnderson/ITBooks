using System;
using System.Collections.Generic;
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
	public sealed class CResolverUnions
	{
//----------------------------------------------------------------------------------------------------------------------
		public async Task<CUnionsMyClass1[]> FieldResolverDelegateMyClass1Array(IResolverContext Context, CancellationToken CancellationToken, IMyLoggerService MyLoggerService)
		{
			MyLoggerService.LogResolver(nameof(CResolverUnions),nameof(FieldResolverDelegateMyClass1Array));

			// !!!!!! Kvoli THREAD SAFETY sa MUSI pouzivat TYPE [IDbContextFactory<TDbContext>], ktory reprezentuje DB CONTEXT POOL FACTORY.
			IDbContextFactory<CDBContext>						DBContextFactory=Context.Service<IDbContextFactory<CDBContext>>();

			// !!!!! Z DB CONTEXT POOL sa vyberie DB CONTEXT.
			// !!!!! MUSI sa pouzit USING SYNTAX, lebo iba pri DISPOSE sa vrati DB CONTEXT OBJECT spat do DB CONTEXT POOL.
			using(CDBContext DBContext=await DBContextFactory.CreateDbContextAsync())
			{
				CUnionsMyClass1[]								MyUnionObjects=await DBContext.EntitiesUnionsMyClass1.Select(P => new CUnionsMyClass1(P.ID,P.SharedValue1,P.SharedValue2,P.Class1Value1,P.Class1Value2)).ToArrayAsync(CancellationToken);

				return(MyUnionObjects);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public async Task<CUnionsMyClass2[]> FieldResolverDelegateMyClass2Array(IResolverContext Context, CancellationToken CancellationToken, IMyLoggerService MyLoggerService)
		{
			MyLoggerService.LogResolver(nameof(CResolverUnions),nameof(FieldResolverDelegateMyClass2Array));

			// !!!!!! Kvoli THREAD SAFETY sa MUSI pouzivat TYPE [IDbContextFactory<TDbContext>], ktory reprezentuje DB CONTEXT POOL FACTORY.
			IDbContextFactory<CDBContext>						DBContextFactory=Context.Service<IDbContextFactory<CDBContext>>();

			// !!!!! Z DB CONTEXT POOL sa vyberie DB CONTEXT.
			// !!!!! MUSI sa pouzit USING SYNTAX, lebo iba pri DISPOSE sa vrati DB CONTEXT OBJECT spat do DB CONTEXT POOL.
			using(CDBContext DBContext=await DBContextFactory.CreateDbContextAsync())
			{
				CUnionsMyClass2[]								MyUnionObjects=await DBContext.EntitiesUnionsMyClass2.Select(P => new CUnionsMyClass2(P.ID,P.SharedValue1,P.SharedValue2,P.Class2Value1,P.Class2Value2)).ToArrayAsync(CancellationToken);

				return(MyUnionObjects);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public async Task<object[]> FieldResolverDelegateMyUnionsArray(IResolverContext Context, CancellationToken CancellationToken, IMyLoggerService MyLoggerService)
		{
			CUnionsMyClass1[]									Class1Objects=await FieldResolverDelegateMyClass1Array(Context,CancellationToken,MyLoggerService);
			CUnionsMyClass2[]									Class2Objects=await FieldResolverDelegateMyClass2Array(Context,CancellationToken,MyLoggerService);
			List<object>										ObjectsCollection=new List<object>();

			ObjectsCollection.AddRange(Class1Objects);
			ObjectsCollection.AddRange(Class2Objects);

			object[]											Objects=ObjectsCollection.ToArray();

			return(Objects);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------