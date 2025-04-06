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
	// !!! CLASS predstavuje OBJECT TYPE pre DATA CLASS TYPE [COneToOnePrincipal1].
	public sealed class CObjectTypeOneToOnePrincipal1 : ObjectType<COneToOnePrincipal1>
	{
//----------------------------------------------------------------------------------------------------------------------
		private static async Task<COneToOneDependent1> FieldResolverDelegateDependent(IResolverContext Context)
		{
			Console.WriteLine($"!!!!!!!!!! RESOLVER [{nameof(CObjectTypeOneToOnePrincipal1)}] is EXECUTING on THREAD [{Thread.CurrentThread.ManagedThreadId}].");

			// !!! Ziska sa PARENT OBJECT.
			COneToOnePrincipal1									ParentObject=Context.Parent<COneToOnePrincipal1>();

			// !!!!!! Kvoli THREAD SAFETY sa MUSI pouzivat TYPE [IDbContextFactory<TDbContext>], ktory reprezentuje DB CONTEXT POOL FACTORY.
			IDbContextFactory<CDBContext>						DBContextFactory=Context.Service<IDbContextFactory<CDBContext>>();

			// !!!!! Z DB CONTEXT POOL sa vyberie DB CONTEXT.
			// !!!!! MUSI sa pouzit USING SYNTAX, lebo iba pri DISPOSE sa vrati DB CONTEXT OBJECT spat do DB CONTEXT POOL.
			using(CDBContext DBContext=await DBContextFactory.CreateDbContextAsync())
			{
				Console.WriteLine($"READING TYPE [{nameof(CEntityOneToOneDependent1)}] for ID [{ParentObject.PrincipalID}].");

				CEntityOneToOneDependent1						EntityChildObject=await DBContext.EntitiesOneToOneDependent1.Where(P => P.EntityPrincipalID==ParentObject.PrincipalID).FirstOrDefaultAsync();

				if (EntityChildObject!=null)
				{
					COneToOneDependent1								Result=new COneToOneDependent1(EntityChildObject.EntityDependentID,EntityChildObject.EntityDependentValue);

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
		private static void ConfigureFieldDependent(IObjectTypeDescriptor<COneToOnePrincipal1> Descriptor)
		{
			// !!! Ziska sa FIELD, ktory sa na nakonfigurovat.
			IObjectFieldDescriptor								FieldDescriptor=Descriptor.Field(P => P.Dependent);

			FieldDescriptor.Name("myOneToOneDependent1");

			FieldDescriptor.Description($"This is FIELD [{nameof(COneToOnePrincipal1.Dependent)}].");

			// !!! Nastavi sa OBJECT TYPE, ktory konfiguruje TYPE daneho FIELD.
			FieldDescriptor.Type<CObjectTypeOneToOneDependent1>();

			// !!! Definuje sa RESOLVER OBJECT, ktoreho ulohou je nacitat data pre dany FIELD, ak je FIELD pozadovany v QUERY.
			FieldDescriptor.Resolve(FieldResolverDelegateDependent);
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		protected override void Configure(IObjectTypeDescriptor<COneToOnePrincipal1> Descriptor)
		{
			// !!! Nastavi sa NAME OBJECT TYPE.
			Descriptor.Name("myOneToOnePrincipal1");

			Descriptor.Description($"This is OBJECT TYPE [{nameof(CObjectTypeOneToOnePrincipal1)}].");

			ConfigureFieldDependent(Descriptor);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------