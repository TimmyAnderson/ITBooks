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
	public sealed class CObjectTypeDataLoaderGroupPrincipal : ObjectType<CDataLoaderGroupPrincipal>
	{
//----------------------------------------------------------------------------------------------------------------------
		private static void ConfigureFieldDependents(IObjectTypeDescriptor<CDataLoaderGroupPrincipal> Descriptor)
		{
			IObjectFieldDescriptor								FieldDescriptor=Descriptor.Field(P => P.Dependents);

			FieldDescriptor.Name("Dependents");

			FieldDescriptor.Description($"This is FIELD [{nameof(CDataLoaderGroupPrincipal.Dependents)}].");

			FieldDescriptor.Type<ListType<CObjectTypeDataLoaderGroupDependent>>();

			FieldDescriptor.ResolveWith<CResolverDataLoaderGroupDependent>(P => P.FieldResolverDelegateDependentArray(default,default,default,default));
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		protected override void Configure(IObjectTypeDescriptor<CDataLoaderGroupPrincipal> Descriptor)
		{
			Descriptor.Name("myDataLoaderGroupPrincipal");

			Descriptor.Description($"This is OBJECT [{nameof(CDataLoaderGroupPrincipal)}].");

			ConfigureFieldDependents(Descriptor);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------