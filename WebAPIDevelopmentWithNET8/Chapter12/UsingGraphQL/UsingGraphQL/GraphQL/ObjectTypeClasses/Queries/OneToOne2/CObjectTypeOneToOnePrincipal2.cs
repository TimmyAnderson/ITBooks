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
	// !!! CLASS predstavuje OBJECT TYPE pre DATA CLASS TYPE [COneToOnePrincipal2].
	public sealed class CObjectTypeOneToOnePrincipal2 : ObjectType<COneToOnePrincipal2>
	{
//----------------------------------------------------------------------------------------------------------------------
		private static void ConfigureFieldDependent(IObjectTypeDescriptor<COneToOnePrincipal2> Descriptor)
		{
			// !!! Ziska sa FIELD, ktory sa na nakonfigurovat.
			IObjectFieldDescriptor								FieldDescriptor=Descriptor.Field(P => P.Dependent);

			FieldDescriptor.Name("myOneToOneDependent2");

			FieldDescriptor.Description($"This is FIELD [{nameof(COneToOnePrincipal2.Dependent)}].");

			// !!! Nastavi sa OBJECT TYPE, ktory konfiguruje TYPE daneho FIELD.
			FieldDescriptor.Type<CObjectTypeOneToOneDependent2>();

			// !!!!! RESOLVER je v osobitnej CLASS.
			FieldDescriptor.ResolveWith<CResolverOneToOneDependent2>(P => P.FieldResolverDelegateDependent(default));
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		protected override void Configure(IObjectTypeDescriptor<COneToOnePrincipal2> Descriptor)
		{
			// !!! Nastavi sa NAME OBJECT TYPE.
			Descriptor.Name("myOneToOnePrincipal2");

			Descriptor.Description($"This is OBJECT TYPE [{nameof(CObjectTypeOneToOnePrincipal2)}].");

			ConfigureFieldDependent(Descriptor);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------