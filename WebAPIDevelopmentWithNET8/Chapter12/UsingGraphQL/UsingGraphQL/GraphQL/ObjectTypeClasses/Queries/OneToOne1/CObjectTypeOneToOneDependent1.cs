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
	// !!! CLASS predstavuje OBJECT TYPE pre DATA CLASS TYPE [COneToOneDependent1].
	public sealed class CObjectTypeOneToOneDependent1 : ObjectType<COneToOneDependent1>
	{
//----------------------------------------------------------------------------------------------------------------------
		private static void ConfigureFieldID(IObjectTypeDescriptor<COneToOneDependent1> Descriptor)
		{
			IObjectFieldDescriptor								FieldDescriptor=Descriptor.Field(P => P.DependentID);

			FieldDescriptor.Name("ID");
		}
//----------------------------------------------------------------------------------------------------------------------
		private static void ConfigureFieldValue(IObjectTypeDescriptor<COneToOneDependent1> Descriptor)
		{
			IObjectFieldDescriptor								FieldDescriptor=Descriptor.Field(P => P.DependentValue);

			FieldDescriptor.Name("VALUE");
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		protected override void Configure(IObjectTypeDescriptor<COneToOneDependent1> Descriptor)
		{
			Descriptor.Description($"This is OBJECT [{nameof(COneToOneDependent1)}].");

			ConfigureFieldID(Descriptor);

			ConfigureFieldValue(Descriptor);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------