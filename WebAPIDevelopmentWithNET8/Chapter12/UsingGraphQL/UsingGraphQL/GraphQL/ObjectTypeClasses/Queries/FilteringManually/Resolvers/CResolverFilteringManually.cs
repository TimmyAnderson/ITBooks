using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading;
using System.Threading.Tasks;
using HotChocolate.Data.Filters;
using HotChocolate.Resolvers;
using HotChocolate.Types;
using Microsoft.EntityFrameworkCore;
//----------------------------------------------------------------------------------------------------------------------
namespace UsingGraphQL
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class CResolverFilteringManually
	{
//----------------------------------------------------------------------------------------------------------------------
		// !!!!! METHOD UMYSELNE nevracia TYPE [IQueryable<TRuntimeType>], aby sa demonstroval MANUAL FILTERING.
		private static async Task<CFilteringManually[]> FieldResolverDelegateFilteringManuallyAll(IResolverContext Context, CancellationToken CancellationToken)
		{
			// !!!!!! Kvoli THREAD SAFETY sa MUSI pouzivat TYPE [IDbContextFactory<TDbContext>], ktory reprezentuje DB CONTEXT POOL FACTORY.
			IDbContextFactory<CDBContext>						DBContextFactory=Context.Service<IDbContextFactory<CDBContext>>();

			// !!!!! Z DB CONTEXT POOL sa vyberie DB CONTEXT.
			// !!!!! MUSI sa pouzit USING SYNTAX, lebo iba pri DISPOSE sa vrati DB CONTEXT OBJECT spat do DB CONTEXT POOL.
			using(CDBContext DBContext=await DBContextFactory.CreateDbContextAsync())
			{
				CEntityFilteringManually[]						Entities=await DBContext.EntitiesFilteringManually.ToArrayAsync(CancellationToken);

				if (Entities!=null)
				{
					CFilteringManually[]						Result=Entities.Select(P => new CFilteringManually(P.ID,P.StringValue,P.IntValue)).ToArray();

					return(Result);
				}
				else
				{
					return(null);
				}
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		// !!!!! METHOD UMYSELNE nevracia TYPE [IQueryable<TRuntimeType>], aby sa demonstroval MANUAL FILTERING.
		private static async Task<CFilteringManually[]> FieldResolverDelegateFilteringManuallyByID(IResolverContext Context, CancellationToken CancellationToken, int ID)
		{
			// !!!!!! Kvoli THREAD SAFETY sa MUSI pouzivat TYPE [IDbContextFactory<TDbContext>], ktory reprezentuje DB CONTEXT POOL FACTORY.
			IDbContextFactory<CDBContext>						DBContextFactory=Context.Service<IDbContextFactory<CDBContext>>();

			// !!!!! Z DB CONTEXT POOL sa vyberie DB CONTEXT.
			// !!!!! MUSI sa pouzit USING SYNTAX, lebo iba pri DISPOSE sa vrati DB CONTEXT OBJECT spat do DB CONTEXT POOL.
			using(CDBContext DBContext=await DBContextFactory.CreateDbContextAsync())
			{
				CEntityFilteringManually[]						Entities=await DBContext.EntitiesFilteringManually.Where(P => P.ID==ID).ToArrayAsync(CancellationToken);

				if (Entities!=null)
				{
					CFilteringManually[]						Result=Entities.Select(P => new CFilteringManually(P.ID,P.StringValue,P.IntValue)).ToArray();

					return(Result);
				}
				else
				{
					return(null);
				}
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		// !!!!! METHOD UMYSELNE nevracia TYPE [IQueryable<TRuntimeType>], aby sa demonstroval MANUAL FILTERING.
		private static async Task<CFilteringManually[]> FieldResolverDelegateFilteringManuallyByIDs(IResolverContext Context, CancellationToken CancellationToken, int[] IDs)
		{
			// !!!!!! Kvoli THREAD SAFETY sa MUSI pouzivat TYPE [IDbContextFactory<TDbContext>], ktory reprezentuje DB CONTEXT POOL FACTORY.
			IDbContextFactory<CDBContext>						DBContextFactory=Context.Service<IDbContextFactory<CDBContext>>();

			// !!!!! Z DB CONTEXT POOL sa vyberie DB CONTEXT.
			// !!!!! MUSI sa pouzit USING SYNTAX, lebo iba pri DISPOSE sa vrati DB CONTEXT OBJECT spat do DB CONTEXT POOL.
			using(CDBContext DBContext=await DBContextFactory.CreateDbContextAsync())
			{
				CEntityFilteringManually[]						Entities=await DBContext.EntitiesFilteringManually.Where(P => IDs.Contains(P.ID)==true).ToArrayAsync(CancellationToken);

				if (Entities!=null)
				{
					CFilteringManually[]						Result=Entities.Select(P => new CFilteringManually(P.ID,P.StringValue,P.IntValue)).ToArray();

					return(Result);
				}
				else
				{
					return(null);
				}
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		// !!!!! METHOD demonstruje MANUAL FILTERING.
		public async Task<CFilteringManually[]> FieldResolverDelegateFilteringManually(IResolverContext Context, CancellationToken CancellationToken, IMyLoggerService MyLoggerService)
		{
			const string										FIELD_ID="ID";
			const string										OPERATION_EQ="eq";
			const string										OPERATION_IN="in";

			MyLoggerService.LogResolver(nameof(CResolverFilteringManually),nameof(FieldResolverDelegateFilteringManually));

			IFilterContext										FilterContext=Context.GetFilterContext();

			if (FilterContext!=null)
			{
				IDictionary<string,object>						FilterContextDictionary=FilterContext.ToDictionary();

				if (FilterContextDictionary!=null)
				{
					bool										HasFilterField=FilterContextDictionary.ContainsKey(FIELD_ID);

					if (HasFilterField==true)
					{
						IDictionary<string,object>				FilterFieldID=(FilterContextDictionary[FIELD_ID] as IDictionary<string,object>);

						if (FilterFieldID!=null)
						{
							if (FilterFieldID.ContainsKey(OPERATION_EQ)==true)
							{
								object							OperationParameter=FilterFieldID[OPERATION_EQ];

								if ((OperationParameter is int)==true)
								{
									int							TypedOperationParameter=(int) OperationParameter;
									CFilteringManually[]		Objects=await FieldResolverDelegateFilteringManuallyByID(Context,CancellationToken,TypedOperationParameter);

									return(Objects);
								}
								else
								{
									throw(new InvalidOperationException($"PARAMETER [{FIELD_ID}] has INVALID OPERATION TYPE [{OperationParameter?.GetType()}]."));
								}
							}
							else if (FilterFieldID.ContainsKey(OPERATION_IN)==true)
							{
								object							OperationParameter=FilterFieldID[OPERATION_IN];

								if ((OperationParameter is IEnumerable<int>)==true)
								{
									int[]						TypedOperationParameter=((IEnumerable<int>) OperationParameter).ToArray();
									CFilteringManually[]		Objects=await FieldResolverDelegateFilteringManuallyByIDs(Context,CancellationToken,TypedOperationParameter);

									return(Objects);
								}
								else
								{
									throw(new InvalidOperationException($"PARAMETER [{FIELD_ID}] has INVALID OPERATION TYPE [{OperationParameter?.GetType()}]."));
								}
							}
						}
					}
				}
			}

			// !!! Ak nebol povoleny FILTERING, vracia sa vsetky RECORDS.

			{
				CFilteringManually[]							Objects=await FieldResolverDelegateFilteringManuallyAll(Context,CancellationToken);

				return(Objects);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------