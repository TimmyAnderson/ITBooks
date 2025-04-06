using System;
using System.Linq;
using System.Threading.Tasks;
using HotChocolate.Resolvers;
using HotChocolate.Types;
using Microsoft.EntityFrameworkCore;
//----------------------------------------------------------------------------------------------------------------------
namespace UsingGraphQL
{
//----------------------------------------------------------------------------------------------------------------------
	// !!! CLASS predstavuje OBJECT TYPE pre DATA CLASS TYPE [COneToOneDependent2].
	public sealed class CObjectTypeOneToOneDependent2 : ObjectType<COneToOneDependent2>
	{
//----------------------------------------------------------------------------------------------------------------------
		private static void ConfigureFieldID(IObjectTypeDescriptor<COneToOneDependent2> Descriptor)
		{
			IObjectFieldDescriptor								FieldDescriptor=Descriptor.Field(P => P.DependentID);

			FieldDescriptor.Name("ID");
		}
//----------------------------------------------------------------------------------------------------------------------
		private static void ConfigureFieldValue(IObjectTypeDescriptor<COneToOneDependent2> Descriptor)
		{
			IObjectFieldDescriptor								FieldDescriptor=Descriptor.Field(P => P.DependentValue);

			FieldDescriptor.Name("VALUE");
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		protected override void Configure(IObjectTypeDescriptor<COneToOneDependent2> Descriptor)
		{
			Descriptor.Description($"This is OBJECT [{nameof(COneToOneDependent2)}].");

			ConfigureFieldID(Descriptor);

			ConfigureFieldValue(Descriptor);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------