using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading;
using System.Threading.Tasks;
using HotChocolate.Resolvers;
using HotChocolate.Types;
using HotChocolate.Types.Pagination;
using Microsoft.EntityFrameworkCore;
//----------------------------------------------------------------------------------------------------------------------
namespace UsingGraphQL
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class CMyQueriesObjectType : ObjectType<CMyQueries>
	{
//----------------------------------------------------------------------------------------------------------------------
		private static void ConfigureArgumentOneToOne1ID(IArgumentDescriptor ArgumentDescriptor)
		{
			ArgumentDescriptor.Type<NonNullType<IntType>>();
		}
//----------------------------------------------------------------------------------------------------------------------
		private static void ConfigureArgumentOneToOne2ID(IArgumentDescriptor ArgumentDescriptor)
		{
			ArgumentDescriptor.Type<NonNullType<IntType>>();
		}
//----------------------------------------------------------------------------------------------------------------------
		private static void ConfigureArgumentOneToManyID(IArgumentDescriptor ArgumentDescriptor)
		{
			ArgumentDescriptor.Type<NonNullType<IntType>>();
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private static async Task<COneToOnePrincipal1[]> FieldResolverDelegateObjectsOneToOne1Principal(IResolverContext Context)
		{
			Console.WriteLine($"!!!!!!!!!! RESOLVER [{nameof(FieldResolverDelegateObjectsOneToOne1Principal)}] is EXECUTING on THREAD [{Thread.CurrentThread.ManagedThreadId}].");

			// !!!!!! Kvoli THREAD SAFETY sa MUSI pouzivat TYPE [IDbContextFactory<TDbContext>], ktory reprezentuje DB CONTEXT POOL FACTORY.
			IDbContextFactory<CDBContext>						DBContextFactory=Context.Service<IDbContextFactory<CDBContext>>();

			// !!!!! Z DB CONTEXT POOL sa vyberie DB CONTEXT.
			// !!!!! MUSI sa pouzit USING SYNTAX, lebo iba pri DISPOSE sa vrati DB CONTEXT OBJECT spat do DB CONTEXT POOL.
			using(CDBContext DBContext=await DBContextFactory.CreateDbContextAsync())
			{
				CEntityOneToOnePrincipal1[]						EntityChildObject=await DBContext.EntitiesOneToOnePrincipal1.ToArrayAsync();

				if (EntityChildObject!=null)
				{
					COneToOnePrincipal1[]						Result=EntityChildObject.Select(P => new COneToOnePrincipal1(P.EntityPrincipalID,P.EntityPrincipalValue)).ToArray();

					return(Result);
				}
				else
				{
					return(null);
				}
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		private static async Task<COneToOnePrincipal1> FieldResolverDelegateObjectOneToOne1Principal(IResolverContext Context)
		{
			Console.WriteLine($"!!!!!!!!!! RESOLVER [{nameof(FieldResolverDelegateObjectOneToOne1Principal)}] is EXECUTING on THREAD [{Thread.CurrentThread.ManagedThreadId}].");

			int													ID=Context.ArgumentValue<int>("id");

			// !!!!!! Kvoli THREAD SAFETY sa MUSI pouzivat TYPE [IDbContextFactory<TDbContext>], ktory reprezentuje DB CONTEXT POOL FACTORY.
			IDbContextFactory<CDBContext>						DBContextFactory=Context.Service<IDbContextFactory<CDBContext>>();

			// !!!!! Z DB CONTEXT POOL sa vyberie DB CONTEXT.
			// !!!!! MUSI sa pouzit USING SYNTAX, lebo iba pri DISPOSE sa vrati DB CONTEXT OBJECT spat do DB CONTEXT POOL.
			using(CDBContext DBContext=await DBContextFactory.CreateDbContextAsync())
			{
				CEntityOneToOnePrincipal1						EntityChildObject=await DBContext.EntitiesOneToOnePrincipal1.Where(P => P.EntityPrincipalID==ID).FirstOrDefaultAsync();

				if (EntityChildObject!=null)
				{
					COneToOnePrincipal1							Result=new COneToOnePrincipal1(EntityChildObject.EntityPrincipalID,EntityChildObject.EntityPrincipalValue);

					return(Result);
				}
				else
				{
					return(null);
				}
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		private static async Task<COneToOnePrincipal2[]> FieldResolverDelegateObjectsOneToOne2Principal(IResolverContext Context)
		{
			Console.WriteLine($"!!!!!!!!!! RESOLVER [{nameof(FieldResolverDelegateObjectsOneToOne2Principal)}] is EXECUTING on THREAD [{Thread.CurrentThread.ManagedThreadId}].");

			// !!!!!! Kvoli THREAD SAFETY sa MUSI pouzivat TYPE [IDbContextFactory<TDbContext>], ktory reprezentuje DB CONTEXT POOL FACTORY.
			IDbContextFactory<CDBContext>						DBContextFactory=Context.Service<IDbContextFactory<CDBContext>>();

			// !!!!! Z DB CONTEXT POOL sa vyberie DB CONTEXT.
			// !!!!! MUSI sa pouzit USING SYNTAX, lebo iba pri DISPOSE sa vrati DB CONTEXT OBJECT spat do DB CONTEXT POOL.
			using(CDBContext DBContext=await DBContextFactory.CreateDbContextAsync())
			{
				CEntityOneToOnePrincipal2[]						EntityChildObject=await DBContext.EntitiesOneToOnePrincipal2.ToArrayAsync();

				if (EntityChildObject!=null)
				{
					COneToOnePrincipal2[]						Result=EntityChildObject.Select(P => new COneToOnePrincipal2(P.EntityPrincipalID,P.EntityPrincipalValue)).ToArray();

					return(Result);
				}
				else
				{
					return(null);
				}
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		private static async Task<COneToOnePrincipal2> FieldResolverDelegateObjectOneToOne2Principal(IResolverContext Context)
		{
			Console.WriteLine($"!!!!!!!!!! RESOLVER [{nameof(FieldResolverDelegateObjectOneToOne2Principal)}] is EXECUTING on THREAD [{Thread.CurrentThread.ManagedThreadId}].");

			int													ID=Context.ArgumentValue<int>("id");

			// !!!!!! Kvoli THREAD SAFETY sa MUSI pouzivat TYPE [IDbContextFactory<TDbContext>], ktory reprezentuje DB CONTEXT POOL FACTORY.
			IDbContextFactory<CDBContext>						DBContextFactory=Context.Service<IDbContextFactory<CDBContext>>();

			// !!!!! Z DB CONTEXT POOL sa vyberie DB CONTEXT.
			// !!!!! MUSI sa pouzit USING SYNTAX, lebo iba pri DISPOSE sa vrati DB CONTEXT OBJECT spat do DB CONTEXT POOL.
			using(CDBContext DBContext=await DBContextFactory.CreateDbContextAsync())
			{
				CEntityOneToOnePrincipal2						EntityChildObject=await DBContext.EntitiesOneToOnePrincipal2.Where(P => P.EntityPrincipalID==ID).FirstOrDefaultAsync();

				if (EntityChildObject!=null)
				{
					COneToOnePrincipal2							Result=new COneToOnePrincipal2(EntityChildObject.EntityPrincipalID,EntityChildObject.EntityPrincipalValue);

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
		private static void ConfigureFieldObjectsOneToOne1(IObjectTypeDescriptor<CMyQueries> Descriptor)
		{
			IObjectFieldDescriptor								FieldDescriptor=Descriptor.Field(P => P.ObjectsOneToOnes1);

			FieldDescriptor.Name("ObjectsOneToOne1");

			FieldDescriptor.Description($"This is FIELD [{nameof(CMyQueries.ObjectsOneToOnes1)}].");

			// !!! Nastavi sa OBJECT TYPE pre FIELD.
			// !!!!! Kedze sa vracia COLLECTION, je NUTNE pouzit TYPE [ListType<TType>].
			FieldDescriptor.Type<ListType<CObjectTypeOneToOnePrincipal1>>();

			FieldDescriptor.Resolve(FieldResolverDelegateObjectsOneToOne1Principal);
		}
//----------------------------------------------------------------------------------------------------------------------
		private static void ConfigureFieldObjectOneToOne1(IObjectTypeDescriptor<CMyQueries> Descriptor)
		{
			IObjectFieldDescriptor								FieldDescriptor=Descriptor.Field(P => P.ObjectOneToOne1);

			FieldDescriptor.Name("ObjectOneToOne1");

			FieldDescriptor.Description($"This is FIELD [{nameof(CMyQueries.ObjectOneToOne1)}].");

			// !!! Nastavi sa OBJECT TYPE pre FIELD.
			FieldDescriptor.Type<CObjectTypeOneToOnePrincipal1>();

			FieldDescriptor.Argument("id",ConfigureArgumentOneToOne1ID);

			FieldDescriptor.Resolve(FieldResolverDelegateObjectOneToOne1Principal);
		}
//----------------------------------------------------------------------------------------------------------------------
		private static void ConfigureFieldObjectsOneToOne2(IObjectTypeDescriptor<CMyQueries> Descriptor)
		{
			IObjectFieldDescriptor								FieldDescriptor=Descriptor.Field(P => P.ObjectsOneToOnes2);

			FieldDescriptor.Name("ObjectsOneToOne2");

			FieldDescriptor.Description($"This is FIELD [{nameof(CMyQueries.ObjectsOneToOnes2)}].");

			// !!! Nastavi sa OBJECT TYPE pre FIELD.
			// !!!!! Kedze sa vracia COLLECTION, je NUTNE pouzit TYPE [ListType<TType>].
			FieldDescriptor.Type<ListType<CObjectTypeOneToOnePrincipal2>>();

			FieldDescriptor.Resolve(FieldResolverDelegateObjectsOneToOne2Principal);
		}
//----------------------------------------------------------------------------------------------------------------------
		private static void ConfigureFieldObjectOneToOne2(IObjectTypeDescriptor<CMyQueries> Descriptor)
		{
			IObjectFieldDescriptor								FieldDescriptor=Descriptor.Field(P => P.ObjectOneToOne2);

			FieldDescriptor.Name("ObjectOneToOne2");

			FieldDescriptor.Description($"This is FIELD [{nameof(CMyQueries.ObjectOneToOne2)}].");

			// !!! Nastavi sa OBJECT TYPE pre FIELD.
			FieldDescriptor.Type<CObjectTypeOneToOnePrincipal2>();

			FieldDescriptor.Argument("id",ConfigureArgumentOneToOne2ID);

			FieldDescriptor.Resolve(FieldResolverDelegateObjectOneToOne2Principal);
		}
//----------------------------------------------------------------------------------------------------------------------
		private static void ConfigureFieldObjectsOneToMany(IObjectTypeDescriptor<CMyQueries> Descriptor)
		{
			IObjectFieldDescriptor								FieldDescriptor=Descriptor.Field(P => P.ObjectsOneToMany);

			FieldDescriptor.Name("ObjectsOneToMany");

			FieldDescriptor.Description($"This is FIELD [{nameof(CMyQueries.ObjectsOneToMany)}].");

			// !!! Nastavi sa OBJECT TYPE pre FIELD.
			// !!!!! Kedze sa vracia COLLECTION, je NUTNE pouzit TYPE [ListType<TType>].
			FieldDescriptor.Type<ListType<CObjectTypeOneToManyPrincipal>>();

			FieldDescriptor.ResolveWith<CResolverOneToManyPrincipal>(P => P.FieldResolverDelegatePrincipalArray(default));
		}
//----------------------------------------------------------------------------------------------------------------------
		private static void ConfigureFieldObjectOneToMany(IObjectTypeDescriptor<CMyQueries> Descriptor)
		{
			IObjectFieldDescriptor								FieldDescriptor=Descriptor.Field(P => P.ObjectOneToMany);

			FieldDescriptor.Name("ObjectOneToMany");

			FieldDescriptor.Description($"This is FIELD [{nameof(CMyQueries.ObjectOneToMany)}].");

			// !!! Nastavi sa OBJECT TYPE pre FIELD.
			FieldDescriptor.Type<CObjectTypeOneToManyPrincipal>();

			FieldDescriptor.Argument("id",ConfigureArgumentOneToManyID);

			FieldDescriptor.ResolveWith<CResolverOneToManyPrincipal>(P => P.FieldResolverDelegatePrincipal(default));
		}
//----------------------------------------------------------------------------------------------------------------------
		private static void ConfigureFieldObjectsDataLoaderBatch(IObjectTypeDescriptor<CMyQueries> Descriptor)
		{
			IObjectFieldDescriptor								FieldDescriptor=Descriptor.Field(P => P.ObjectsDataLoaderBatch);

			FieldDescriptor.Name("ObjectsDataLoaderBatch");

			FieldDescriptor.Description($"This is FIELD [{nameof(CMyQueries.ObjectsDataLoaderBatch)}].");

			// !!! Nastavi sa OBJECT TYPE pre FIELD.
			// !!!!! Kedze sa vracia COLLECTION, je NUTNE pouzit TYPE [ListType<TType>].
			FieldDescriptor.Type<ListType<CObjectTypeDataLoaderBatchPrincipal>>();

			FieldDescriptor.ResolveWith<CResolverDataLoaderBatchPrincipal>(P => P.FieldResolverDelegatePrincipalArray(default));
		}
//----------------------------------------------------------------------------------------------------------------------
		private static void ConfigureFieldObjectsDataLoaderGroup(IObjectTypeDescriptor<CMyQueries> Descriptor)
		{
			IObjectFieldDescriptor								FieldDescriptor=Descriptor.Field(P => P.ObjectsDataLoaderGroup);

			FieldDescriptor.Name("ObjectsDataLoaderGroup");

			FieldDescriptor.Description($"This is FIELD [{nameof(CMyQueries.ObjectsDataLoaderGroup)}].");

			// !!! Nastavi sa OBJECT TYPE pre FIELD.
			// !!!!! Kedze sa vracia COLLECTION, je NUTNE pouzit TYPE [ListType<TType>].
			FieldDescriptor.Type<ListType<CObjectTypeDataLoaderGroupPrincipal>>();

			FieldDescriptor.ResolveWith<CResolverDataLoaderGroupPrincipal>(P => P.FieldResolverDelegatePrincipalArray(default,default));
		}
//----------------------------------------------------------------------------------------------------------------------
		private static void ConfigureFieldObjectsMyInterface(IObjectTypeDescriptor<CMyQueries> Descriptor)
		{
			IObjectFieldDescriptor								FieldDescriptor=Descriptor.Field(P => P.ObjectsMyInterface);

			FieldDescriptor.Name("ObjectsMyInterface");

			FieldDescriptor.Description($"This is FIELD [{nameof(CMyQueries.ObjectsMyInterface)}].");

			// !!! Nastavi sa OBJECT TYPE pre FIELD.
			// !!!!! Kedze sa vracia COLLECTION, je NUTNE pouzit TYPE [ListType<TType>].
			FieldDescriptor.Type<ListType<CObjectTypeInterfacesMyInterface>>();

			FieldDescriptor.ResolveWith<CResolverInterfacesMyInterface>(P => P.FieldResolverDelegateMyInterfaceArray(default,default,default));
		}
//----------------------------------------------------------------------------------------------------------------------
		private static void ConfigureFieldObjectsMyUnions(IObjectTypeDescriptor<CMyQueries> Descriptor)
		{
			IObjectFieldDescriptor								FieldDescriptor=Descriptor.Field(P => P.ObjectsUnions);

			FieldDescriptor.Name("ObjectsUnions");

			FieldDescriptor.Description($"This is FIELD [{nameof(CMyQueries.ObjectsUnions)}].");

			// !!! Nastavi sa OBJECT TYPE pre FIELD.
			// !!!!! Kedze sa vracia COLLECTION, je NUTNE pouzit TYPE [ListType<TType>].
			FieldDescriptor.Type<ListType<CObjectTypeUnions>>();

			FieldDescriptor.ResolveWith<CResolverUnions>(P => P.FieldResolverDelegateMyUnionsArray(default,default,default));
		}
//----------------------------------------------------------------------------------------------------------------------
		private static void ConfigureFieldObjectsFilteringByConvention(IObjectTypeDescriptor<CMyQueries> Descriptor)
		{
			IObjectFieldDescriptor								FieldDescriptor=Descriptor.Field(P => P.ObjectsFilteringByConvention);

			FieldDescriptor.Name("ObjectsFilteringByConvention");

			FieldDescriptor.Description($"This is FIELD [{nameof(CMyQueries.ObjectsFilteringByConvention)}].");

			// !!! Povoli sa FILTERING.
			FieldDescriptor.UseFiltering();

			FieldDescriptor.ResolveWith<CResolverFilteringByConvention>(P => P.FieldResolverDelegateFilteringByConventionArray(default,default,default));
		}
//----------------------------------------------------------------------------------------------------------------------
		private static void ConfigureFieldObjectsFilteringByFluentAPIImplicit(IObjectTypeDescriptor<CMyQueries> Descriptor)
		{
			IObjectFieldDescriptor								FieldDescriptor=Descriptor.Field(P => P.ObjectsFilteringByFluentAPIImplicit);

			FieldDescriptor.Name("ObjectsFilteringByFluentAPIImplicit");

			FieldDescriptor.Description($"This is FIELD [{nameof(CMyQueries.ObjectsFilteringByFluentAPIImplicit)}].");

			// !!! Povoli sa FILTERING.
			FieldDescriptor.UseFiltering<CFilterTypeFilteringByFluentAPIImplicit>();

			FieldDescriptor.ResolveWith<CResolverFilteringByFluentAPIImplicit>(P => P.FieldResolverDelegateFilteringByFluentAPIImplicitArray(default,default,default));
		}
//----------------------------------------------------------------------------------------------------------------------
		private static void ConfigureFieldObjectsFilteringByFluentAPIExplicit(IObjectTypeDescriptor<CMyQueries> Descriptor)
		{
			IObjectFieldDescriptor								FieldDescriptor=Descriptor.Field(P => P.ObjectsFilteringByFluentAPIExplicit);

			FieldDescriptor.Name("ObjectsFilteringByFluentAPIExplicit");

			FieldDescriptor.Description($"This is FIELD [{nameof(CMyQueries.ObjectsFilteringByFluentAPIExplicit)}].");

			// !!! Povoli sa FILTERING.
			FieldDescriptor.UseFiltering<CFilterTypeFilteringByFluentAPIExplicit>();

			FieldDescriptor.ResolveWith<CResolverFilteringByFluentAPIExplicit>(P => P.FieldResolverDelegateFilteringByFluentAPIExplicitArray(default,default,default));
		}
//----------------------------------------------------------------------------------------------------------------------
		private static void ConfigureFieldObjectsFilteringManually(IObjectTypeDescriptor<CMyQueries> Descriptor)
		{
			IObjectFieldDescriptor								FieldDescriptor=Descriptor.Field(P => P.ObjectsFilteringManually);

			FieldDescriptor.Name("ObjectsFilteringManually");

			FieldDescriptor.Description($"This is FIELD [{nameof(CMyQueries.ObjectsFilteringManually)}].");

			// !!! Povoli sa FILTERING.
			FieldDescriptor.UseFiltering<CFilterTypeFilteringManually>();

			FieldDescriptor.ResolveWith<CResolverFilteringManually>(P => P.FieldResolverDelegateFilteringManually(default,default,default));
		}
//----------------------------------------------------------------------------------------------------------------------
		private static void ConfigureFieldObjectsSortingByConvention(IObjectTypeDescriptor<CMyQueries> Descriptor)
		{
			IObjectFieldDescriptor								FieldDescriptor=Descriptor.Field(P => P.ObjectsSortingByConvention);

			FieldDescriptor.Name("ObjectsSortingByConvention");

			FieldDescriptor.Description($"This is FIELD [{nameof(CMyQueries.ObjectsSortingByConvention)}].");

			// !!! Povoli sa SORTING.
			FieldDescriptor.UseSorting();

			FieldDescriptor.ResolveWith<CResolverSortingByConvention>(P => P.FieldResolverDelegateArray(default));
		}
//----------------------------------------------------------------------------------------------------------------------
		private static void ConfigureFieldObjectsSortingByFluentAPI(IObjectTypeDescriptor<CMyQueries> Descriptor)
		{
			IObjectFieldDescriptor								FieldDescriptor=Descriptor.Field(P => P.ObjectsSortingByFluentAPI);

			FieldDescriptor.Name("ObjectsSortingByFluentAPI");

			FieldDescriptor.Description($"This is FIELD [{nameof(CMyQueries.ObjectsSortingByFluentAPI)}].");

			// !!! Povoli sa SORTING.
			FieldDescriptor.UseSorting<CSortTypeFilteringByFluentAPI>();

			FieldDescriptor.ResolveWith<CResolverSortingByFluentAPI>(P => P.FieldResolverDelegateArray(default));
		}
//----------------------------------------------------------------------------------------------------------------------
		private static void ConfigureFieldObjectsSortingManually(IObjectTypeDescriptor<CMyQueries> Descriptor)
		{
			IObjectFieldDescriptor								FieldDescriptor=Descriptor.Field(P => P.ObjectsSortingManually);

			FieldDescriptor.Name("ObjectsSortingManually");

			FieldDescriptor.Description($"This is FIELD [{nameof(CMyQueries.ObjectsSortingManually)}].");

			// !!! Povoli sa SORTING.
			FieldDescriptor.UseSorting<CSortTypeSortingManually>();

			FieldDescriptor.ResolveWith<CResolverSortingManually>(P => P.FieldResolverDelegateSortingManually(default,default,default));
		}
//----------------------------------------------------------------------------------------------------------------------
		private static void ConfigureFieldObjectsPaginationCursorBased(IObjectTypeDescriptor<CMyQueries> Descriptor)
		{
			IObjectFieldDescriptor								FieldDescriptor=Descriptor.Field(P => P.ObjectsPaginationCursorBased);

			FieldDescriptor.Name("ObjectsPaginationCursorBased");

			FieldDescriptor.Description($"This is FIELD [{nameof(CMyQueries.ObjectsPaginationCursorBased)}].");

			// !!! Nastavi sa OBJECT TYPE pre FIELD.
			FieldDescriptor.Type<CObjectTypePaginationCursorBased>();

			PagingOptions										PagingOptions=new PagingOptions();

			PagingOptions.DefaultPageSize=5;
			PagingOptions.IncludeNodesField=true;
			PagingOptions.IncludeTotalCount=true;

			// !!! Povoli sa PAGINATION.
			// !!!!! METHOD sa MUSI volat pred METHODS povolujucimi FILTERING a SORTING/
			FieldDescriptor.UsePaging(options: PagingOptions);

			// !!! Povoli sa FILTERING.
			FieldDescriptor.UseFiltering<CFilterTypePaginationCursorBased>();

			// !!! Povoli sa SORTING.
			FieldDescriptor.UseSorting<CSortTypePaginationCursorBased>();

			FieldDescriptor.ResolveWith<CResolverPaginationCursorBased>(P => P.FieldResolverDelegateArray(default));
		}
//----------------------------------------------------------------------------------------------------------------------
		private static void ConfigureFieldObjectsPaginationOffsetBased(IObjectTypeDescriptor<CMyQueries> Descriptor)
		{
			IObjectFieldDescriptor								FieldDescriptor=Descriptor.Field(P => P.ObjectsPaginationOffsetBased);

			FieldDescriptor.Name("ObjectsPaginationOffsetBased");

			FieldDescriptor.Description($"This is FIELD [{nameof(CMyQueries.ObjectsPaginationOffsetBased)}].");

			// !!! Nastavi sa OBJECT TYPE pre FIELD.
			FieldDescriptor.Type<CObjectTypePaginationOffsetBased>();

			PagingOptions										PagingOptions=new PagingOptions();

			PagingOptions.DefaultPageSize=5;
			PagingOptions.IncludeNodesField=true;
			PagingOptions.IncludeTotalCount=true;

			// !!! Povoli sa PAGINATION.
			// !!!!! METHOD sa MUSI volat pred METHODS povolujucimi FILTERING a SORTING/
			FieldDescriptor.UseOffsetPaging(options: PagingOptions);

			// !!! Povoli sa FILTERING.
			FieldDescriptor.UseFiltering<CFilterTypePaginationOffsetBased>();

			// !!! Povoli sa SORTING.
			FieldDescriptor.UseSorting<CSortTypePaginationOffsetBased>();

			FieldDescriptor.ResolveWith<CResolverPaginationOffsetBased>(P => P.FieldResolverDelegateArray(default));
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		protected override void Configure(IObjectTypeDescriptor<CMyQueries> Descriptor)
		{
			Descriptor.Name("myQueries");

			Descriptor.Description("This is QUERIES OBJECT TYPE.");

			ConfigureFieldObjectsOneToOne1(Descriptor);
			ConfigureFieldObjectOneToOne1(Descriptor);

			ConfigureFieldObjectsOneToOne2(Descriptor);
			ConfigureFieldObjectOneToOne2(Descriptor);

			ConfigureFieldObjectsOneToMany(Descriptor);
			ConfigureFieldObjectOneToMany(Descriptor);

			ConfigureFieldObjectsDataLoaderBatch(Descriptor);

			ConfigureFieldObjectsDataLoaderGroup(Descriptor);

			ConfigureFieldObjectsMyInterface(Descriptor);

			ConfigureFieldObjectsMyUnions(Descriptor);

			ConfigureFieldObjectsFilteringByConvention(Descriptor);
			ConfigureFieldObjectsFilteringByFluentAPIImplicit(Descriptor);
			ConfigureFieldObjectsFilteringByFluentAPIExplicit(Descriptor);
			ConfigureFieldObjectsFilteringManually(Descriptor);

			ConfigureFieldObjectsSortingByConvention(Descriptor);
			ConfigureFieldObjectsSortingByFluentAPI(Descriptor);
			ConfigureFieldObjectsSortingManually(Descriptor);

			ConfigureFieldObjectsPaginationCursorBased(Descriptor);
			ConfigureFieldObjectsPaginationOffsetBased(Descriptor);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------