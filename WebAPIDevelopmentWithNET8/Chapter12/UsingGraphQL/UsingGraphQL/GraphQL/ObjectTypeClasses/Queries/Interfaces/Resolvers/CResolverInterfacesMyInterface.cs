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
	public sealed class CResolverInterfacesMyInterface
	{
//----------------------------------------------------------------------------------------------------------------------
		public async Task<IInterfacesMyInterface[]> FieldResolverDelegateMyInterfaceArray(IResolverContext Context, CancellationToken CancellationToken, IMyLoggerService MyLoggerService)
		{
			MyLoggerService.LogResolver(nameof(CResolverInterfacesMyInterface),nameof(FieldResolverDelegateMyInterfaceArray));

			// !!!!!! Kvoli THREAD SAFETY sa MUSI pouzivat TYPE [IDbContextFactory<TDbContext>], ktory reprezentuje DB CONTEXT POOL FACTORY.
			IDbContextFactory<CDBContext>						DBContextFactory=Context.Service<IDbContextFactory<CDBContext>>();

			// !!!!! Z DB CONTEXT POOL sa vyberie DB CONTEXT.
			// !!!!! MUSI sa pouzit USING SYNTAX, lebo iba pri DISPOSE sa vrati DB CONTEXT OBJECT spat do DB CONTEXT POOL.
			using(CDBContext DBContext=await DBContextFactory.CreateDbContextAsync())
			{
				CInterfacesMyInterface1[]						MyInterface1Objects=await DBContext.EntitiesInterfacesMyInterface1.Select(P => new CInterfacesMyInterface1(P.ID,P.SharedValue1,P.SharedValue2,P.Class1Value1,P.Class1Value2)).ToArrayAsync(CancellationToken);
				CInterfacesMyInterface2[]						MyInterface2Objects=await DBContext.EntitiesInterfacesMyInterface2.Select(P => new CInterfacesMyInterface2(P.ID,P.SharedValue1,P.SharedValue2,P.Class2Value1,P.Class2Value2)).ToArrayAsync(CancellationToken);
				List<IInterfacesMyInterface>					MyInterfaceObjectsCollection=new List<IInterfacesMyInterface>();

				MyInterfaceObjectsCollection.AddRange(MyInterface1Objects);
				MyInterfaceObjectsCollection.AddRange(MyInterface2Objects);

				IInterfacesMyInterface[]						MyInterfaceObjects=MyInterfaceObjectsCollection.ToArray();

				return(MyInterfaceObjects);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------