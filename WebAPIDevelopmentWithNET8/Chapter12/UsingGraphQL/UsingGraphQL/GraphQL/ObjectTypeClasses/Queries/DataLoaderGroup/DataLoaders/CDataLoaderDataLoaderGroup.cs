using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading;
using System.Threading.Tasks;
using GreenDonut;
using Microsoft.EntityFrameworkCore;
//----------------------------------------------------------------------------------------------------------------------
namespace UsingGraphQL
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class CDataLoaderDataLoaderGroup : GroupedDataLoader<int,CDataLoaderGroupDependent>
	{
//----------------------------------------------------------------------------------------------------------------------
		private readonly IMyLoggerService						MMyLoggerService;
		private readonly IDbContextFactory<CDBContext>			MDBContextFactory;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		// !!! V DATA LOADER CLASSES je mozne pouzit aj CONTRUCTOR DEPENDENCY INJECTION.
		public CDataLoaderDataLoaderGroup(IMyLoggerService MyLoggerService, IDbContextFactory<CDBContext> DBContextFactory, IBatchScheduler BatchScheduler, DataLoaderOptions Options)
			: base(BatchScheduler,Options)
		{
			MMyLoggerService=MyLoggerService;
			MDBContextFactory=DBContextFactory;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		protected async override Task<ILookup<int,CDataLoaderGroupDependent>> LoadGroupedBatchAsync(IReadOnlyList<int> Keys, CancellationToken CancellationToken)
		{
			MMyLoggerService.LogDataLoader(nameof(CDataLoaderDataLoaderGroup),nameof(LoadGroupedBatchAsync));

			using(CDBContext DBContext=await MDBContextFactory.CreateDbContextAsync())
			{
				// !!! Citaju sa DEPENDENT ENTITIES na zaklade PRINCIPAL ENTITY IDs.
				List<CEntityDataLoaderGroupDependent>			List=await DBContext.EntitiesDataLoaderGroupDependent.Where(P => Keys.Contains(P.EntityPrincipalID)).ToListAsync(CancellationToken);
				ILookup<int,CDataLoaderGroupDependent>			Lookup=List.ToLookup(P => P.EntityPrincipalID,P => new CDataLoaderGroupDependent(P.EntityDependentID,P.EntityDependentValue1,P.EntityDependentValue2));

				return(Lookup);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------