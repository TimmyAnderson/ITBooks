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
	public sealed class CResolverOneToManyDependent
	{
//----------------------------------------------------------------------------------------------------------------------
		public async Task<COneToManyDependent[]> FieldResolverDelegateDependentArray(IResolverContext Context)
		{
			// !!! SERVICE sa ziska PROGRAMOVO.
			IMyLoggerService									MyLoggerService=Context.Service<IMyLoggerService>();

			MyLoggerService.LogResolver(nameof(CResolverOneToManyDependent),nameof(FieldResolverDelegateDependentArray));

			// !!!!!! Kvoli THREAD SAFETY sa MUSI pouzivat TYPE [IDbContextFactory<TDbContext>], ktory reprezentuje DB CONTEXT POOL FACTORY.
			IDbContextFactory<CDBContext>						DBContextFactory=Context.Service<IDbContextFactory<CDBContext>>();

			// !!!!! Z DB CONTEXT POOL sa vyberie DB CONTEXT.
			// !!!!! MUSI sa pouzit USING SYNTAX, lebo iba pri DISPOSE sa vrati DB CONTEXT OBJECT spat do DB CONTEXT POOL.
			using(CDBContext DBContext=await DBContextFactory.CreateDbContextAsync())
			{
				COneToManyPrincipal								ParentObject=Context.Parent<COneToManyPrincipal>();

				CEntityOneToManyDependent[]						EntityChildObjects=await DBContext.EntitiesOneToManyDependent.Where(P => P.EntityPrincipalID==ParentObject.PrincipalID).ToArrayAsync();

				if (EntityChildObjects!=null)
				{
					COneToManyDependent[]							Result=EntityChildObjects.Select(P => new COneToManyDependent(P.EntityDependentID,P.EntityDependentValue)).ToArray();

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