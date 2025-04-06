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
	public sealed class CObjectTypeOneToManyPrincipal : ObjectType<COneToManyPrincipal>
	{
//----------------------------------------------------------------------------------------------------------------------
		private static void ConfigureFieldDependents(IObjectTypeDescriptor<COneToManyPrincipal> Descriptor)
		{
			IObjectFieldDescriptor								FieldDescriptor=Descriptor.Field(P => P.Dependents);

			FieldDescriptor.Name("Dependents");

			FieldDescriptor.Description($"This is FIELD [{nameof(COneToManyPrincipal.Dependents)}].");

			FieldDescriptor.Type<ListType<CObjectTypeOneToManyDependent>>();

			FieldDescriptor.ResolveWith<CResolverOneToManyDependent>(P => P.FieldResolverDelegateDependentArray(default));
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		protected override void Configure(IObjectTypeDescriptor<COneToManyPrincipal> Descriptor)
		{
			Descriptor.Name("myOneToManyPrincipal");

			Descriptor.Description($"This is OBJECT [{nameof(COneToManyPrincipal)}].");

			ConfigureFieldDependents(Descriptor);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------