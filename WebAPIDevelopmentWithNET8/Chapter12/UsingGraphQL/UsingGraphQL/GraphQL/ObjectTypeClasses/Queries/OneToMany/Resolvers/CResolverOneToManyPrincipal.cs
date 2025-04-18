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
	public sealed class CResolverOneToManyPrincipal
	{
//----------------------------------------------------------------------------------------------------------------------
		public async Task<COneToManyPrincipal> FieldResolverDelegatePrincipal(IResolverContext Context)
		{
			// !!! SERVICE sa ziska PROGRAMOVO.
			IMyLoggerService									MyLoggerService=Context.Service<IMyLoggerService>();

			MyLoggerService.LogResolver(nameof(CResolverOneToManyPrincipal),nameof(FieldResolverDelegatePrincipal));

			// !!!!! PARAMETER sa cita z ARGUMENT.
			int													ID=Context.ArgumentValue<int>("id");

			// !!!!!! Kvoli THREAD SAFETY sa MUSI pouzivat TYPE [IDbContextFactory<TDbContext>], ktory reprezentuje DB CONTEXT POOL FACTORY.
			IDbContextFactory<CDBContext>						DBContextFactory=Context.Service<IDbContextFactory<CDBContext>>();

			// !!!!! Z DB CONTEXT POOL sa vyberie DB CONTEXT.
			// !!!!! MUSI sa pouzit USING SYNTAX, lebo iba pri DISPOSE sa vrati DB CONTEXT OBJECT spat do DB CONTEXT POOL.
			using(CDBContext DBContext=await DBContextFactory.CreateDbContextAsync())
			{
				CEntityOneToManyPrincipal						EntityChildObject=await DBContext.EntitiesOneToManyPrincipal.Where(P => P.EntityPrincipalID==ID).FirstOrDefaultAsync();

				if (EntityChildObject!=null)
				{
					COneToManyPrincipal							Result=new COneToManyPrincipal(EntityChildObject.EntityPrincipalID,EntityChildObject.EntityPrincipalValue);

					return(Result);
				}
				else
				{
					return(null);
				}
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public async Task<COneToManyPrincipal[]> FieldResolverDelegatePrincipalArray(IResolverContext Context)
		{
			// !!! SERVICE sa ziska PROGRAMOVO.
			IMyLoggerService									MyLoggerService=Context.Service<IMyLoggerService>();

			MyLoggerService.LogResolver(nameof(CResolverOneToManyPrincipal),nameof(FieldResolverDelegatePrincipalArray));

			// !!!!!! Kvoli THREAD SAFETY sa MUSI pouzivat TYPE [IDbContextFactory<TDbContext>], ktory reprezentuje DB CONTEXT POOL FACTORY.
			IDbContextFactory<CDBContext>						DBContextFactory=Context.Service<IDbContextFactory<CDBContext>>();

			// !!!!! Z DB CONTEXT POOL sa vyberie DB CONTEXT.
			// !!!!! MUSI sa pouzit USING SYNTAX, lebo iba pri DISPOSE sa vrati DB CONTEXT OBJECT spat do DB CONTEXT POOL.
			using(CDBContext DBContext=await DBContextFactory.CreateDbContextAsync())
			{
				CEntityOneToManyPrincipal[]						EntityChildObjects=await DBContext.EntitiesOneToManyPrincipal.ToArrayAsync();

				if (EntityChildObjects!=null)
				{
					COneToManyPrincipal[]						Result=EntityChildObjects.Select(P => new COneToManyPrincipal(P.EntityPrincipalID,P.EntityPrincipalValue)).ToArray();

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