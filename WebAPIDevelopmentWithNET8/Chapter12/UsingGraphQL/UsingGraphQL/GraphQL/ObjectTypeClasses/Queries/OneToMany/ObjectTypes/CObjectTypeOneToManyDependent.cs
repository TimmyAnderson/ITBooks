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
	public sealed class CObjectTypeOneToManyDependent : ObjectType<COneToManyDependent>
	{
//----------------------------------------------------------------------------------------------------------------------
		private static void ConfigureFieldID(IObjectTypeDescriptor<COneToManyDependent> Descriptor)
		{
			IObjectFieldDescriptor								FieldDescriptor=Descriptor.Field(P => P.DependentID);

			FieldDescriptor.Name("ID");
		}
//----------------------------------------------------------------------------------------------------------------------
		private static void ConfigureFieldValue(IObjectTypeDescriptor<COneToManyDependent> Descriptor)
		{
			IObjectFieldDescriptor								FieldDescriptor=Descriptor.Field(P => P.DependentValue);

			FieldDescriptor.Name("VALUE");
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		protected override void Configure(IObjectTypeDescriptor<COneToManyDependent> Descriptor)
		{
			Descriptor.Description($"This is OBJECT [{nameof(COneToManyDependent)}].");

			ConfigureFieldID(Descriptor);

			ConfigureFieldValue(Descriptor);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------