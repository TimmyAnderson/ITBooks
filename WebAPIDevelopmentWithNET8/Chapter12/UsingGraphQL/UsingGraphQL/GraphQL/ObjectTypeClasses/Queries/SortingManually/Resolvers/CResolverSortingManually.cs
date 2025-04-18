using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading;
using System.Threading.Tasks;
using HotChocolate.Data.Filters;
using HotChocolate.Language;
using HotChocolate.Resolvers;
using HotChocolate.Types;
using Microsoft.EntityFrameworkCore;
//----------------------------------------------------------------------------------------------------------------------
namespace UsingGraphQL
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class CResolverSortingManually
	{
//----------------------------------------------------------------------------------------------------------------------
		// !!!!! METHOD UMYSELNE nevracia TYPE [IQueryable<TRuntimeType>], aby sa demonstroval MANUAL SORTING.
		private static async Task<CSortingManually[]> FieldResolverDelegateSortingManuallyAll(IResolverContext Context, CancellationToken CancellationToken, string SortValueString, string SortValueInt)
		{
			// !!!!!! Kvoli THREAD SAFETY sa MUSI pouzivat TYPE [IDbContextFactory<TDbContext>], ktory reprezentuje DB CONTEXT POOL FACTORY.
			IDbContextFactory<CDBContext>						DBContextFactory=Context.Service<IDbContextFactory<CDBContext>>();

			// !!!!! Z DB CONTEXT POOL sa vyberie DB CONTEXT.
			// !!!!! MUSI sa pouzit USING SYNTAX, lebo iba pri DISPOSE sa vrati DB CONTEXT OBJECT spat do DB CONTEXT POOL.
			using(CDBContext DBContext=await DBContextFactory.CreateDbContextAsync())
			{
				IQueryable<CEntitySortingManually>				Query=DBContext.EntitiesSortingManually;

				if (SortValueString!=null)
				{
					if (SortValueInt!=null)
					{
						if (SortValueString=="ASC" && SortValueInt=="ASC")
						{
							Query=Query.OrderBy(P => P.ValueString).ThenBy(P => P.ValueInt);
						}
						else if (SortValueString=="ASC" && SortValueInt=="DESC")
						{
							Query=Query.OrderBy(P => P.ValueString).ThenByDescending(P => P.ValueInt);
						}
						else if (SortValueString=="DESC" && SortValueInt=="ASC")
						{
							Query=Query.OrderByDescending(P => P.ValueString).ThenBy(P => P.ValueInt);
						}
						else if (SortValueString=="DESC" && SortValueInt=="DESC")
						{
							Query=Query.OrderByDescending(P => P.ValueString).ThenByDescending(P => P.ValueInt);
						}
					}
					else
					{
						if (SortValueString=="ASC")
						{
							Query=Query.OrderBy(P => P.ValueString);
						}
						else if (SortValueString=="DESC")
						{
							Query=Query.OrderByDescending(P => P.ValueString);
						}
					}
				}
				else
				{
					if (SortValueInt=="ASC")
					{
						Query=Query.OrderBy(P => P.ValueInt);
					}
					else if (SortValueInt=="DESC")
					{
						Query=Query.OrderByDescending(P => P.ValueInt);
					}
				}

				CEntitySortingManually[]						Entities=await Query.ToArrayAsync(CancellationToken);

				if (Entities!=null)
				{
					CSortingManually[]							Result=Entities.Select(P => new CSortingManually(P.ID,P.ValueString,P.ValueInt)).ToArray();

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
		// !!!!! METHOD demonstruje MANUAL SORTING.
		public async Task<CSortingManually[]> FieldResolverDelegateSortingManually(IResolverContext Context, CancellationToken CancellationToken, IMyLoggerService MyLoggerService)
		{
			const string										PARAMETER_NAME="order";
			const string										FIELD_NAME_STRING="valueString";
			const string										FIELD_NAME_INT="valueInt";

			MyLoggerService.LogResolver(nameof(CResolverSortingManually),nameof(FieldResolverDelegateSortingManually));

			string												SortValueString=null;
			string												SortValueInt=null;

			// !!! Zjednodusene implementacia, kde je pevny ORDER jednotlivych SORT FIELDS.

			IValueNode											ArgumentLiteral=Context.ArgumentLiteral<IValueNode>(PARAMETER_NAME);

			if (ArgumentLiteral!=null)
			{
				if ((ArgumentLiteral is ObjectValueNode)==true)
				{
					ObjectValueNode								TypedArgumentLiteral=(ObjectValueNode) ArgumentLiteral;

					foreach(ObjectFieldNode Node in TypedArgumentLiteral.Fields)
					{
						NameNode								NodeName=Node.Name;

						if (NodeName!=null)
						{
							string								Name=NodeName.Value;

							if (Name==FIELD_NAME_STRING)
							{
								IValueNode						NodeValue=Node.Value;

								if (NodeValue!=null)
								{
									if ((NodeValue.Value is string)==true)
									{
										SortValueString=(string)NodeValue.Value;
									}
								}
							}
							else if (Name==FIELD_NAME_INT)
							{
								IValueNode						NodeValue=Node.Value;

								if (NodeValue!=null)
								{
									if ((NodeValue.Value is string)==true)
									{
										SortValueInt=(string)NodeValue.Value;
									}
								}
							}
						}
					}
				}
			}

			CSortingManually[]									Objects=await FieldResolverDelegateSortingManuallyAll(Context,CancellationToken,SortValueString,SortValueInt);

			return(Objects);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------