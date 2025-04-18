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
	public sealed class CDataLoaderDataLoaderBatch : BatchDataLoader<int,CDataLoaderBatchDependent>
	{
//----------------------------------------------------------------------------------------------------------------------
		private readonly IMyLoggerService						MMyLoggerService;
		private readonly IDbContextFactory<CDBContext>			MDBContextFactory;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		// !!! V DATA LOADER CLASSES je mozne pouzit aj CONTRUCTOR DEPENDENCY INJECTION.
		public CDataLoaderDataLoaderBatch(IMyLoggerService MyLoggerService, IDbContextFactory<CDBContext> DBContextFactory, IBatchScheduler BatchScheduler, DataLoaderOptions Options)
			: base(BatchScheduler,Options)
		{
			MMyLoggerService=MyLoggerService;
			MDBContextFactory=DBContextFactory;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		protected async override Task<IReadOnlyDictionary<int,CDataLoaderBatchDependent>> LoadBatchAsync(IReadOnlyList<int> Keys, CancellationToken CancellationToken)
		{
			MMyLoggerService.LogDataLoader(nameof(CDataLoaderDataLoaderBatch),nameof(LoadBatchAsync));

			using(CDBContext DBContext=await MDBContextFactory.CreateDbContextAsync())
			{
				// !!! Citaju sa DEPENDENT ENTITIES na zaklade PRINCIPAL ENTITY IDs.
				IReadOnlyDictionary<int,CEntityDataLoaderBatchDependent>	RawDictionary=await DBContext.EntitiesDataLoaderBatchDependent.Where(P => Keys.Contains(P.EntityDependentID)).ToDictionaryAsync(P => P.EntityPrincipalID,CancellationToken);
				IReadOnlyDictionary<int,CDataLoaderBatchDependent>	Dictionary=RawDictionary.ToDictionary(P => P.Key,P => new CDataLoaderBatchDependent(P.Value.EntityDependentID,P.Value.EntityDependentValue1,P.Value.EntityDependentValue2));

				return(Dictionary);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------