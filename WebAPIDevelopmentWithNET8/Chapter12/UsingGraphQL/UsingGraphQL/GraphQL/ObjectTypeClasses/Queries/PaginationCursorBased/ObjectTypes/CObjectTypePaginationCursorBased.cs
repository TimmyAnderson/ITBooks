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
	public sealed class CObjectTypePaginationCursorBased : ObjectType<CEntityPaginationCursorBased>
	{
//----------------------------------------------------------------------------------------------------------------------
		private static void ConfigureFieldID(IObjectTypeDescriptor<CEntityPaginationCursorBased> Descriptor)
		{
			IObjectFieldDescriptor								FieldDescriptor=Descriptor.Field(P => P.ID);

			FieldDescriptor.Name("ID");
		}
//----------------------------------------------------------------------------------------------------------------------
		private static void ConfigureFieldValue1(IObjectTypeDescriptor<CEntityPaginationCursorBased> Descriptor)
		{
			IObjectFieldDescriptor								FieldDescriptor=Descriptor.Field(P => P.Value1);

			FieldDescriptor.Name("VALUE_1");
		}
//----------------------------------------------------------------------------------------------------------------------
		private static void ConfigureFieldValue2(IObjectTypeDescriptor<CEntityPaginationCursorBased> Descriptor)
		{
			IObjectFieldDescriptor								FieldDescriptor=Descriptor.Field(P => P.Value2);

			FieldDescriptor.Name("VALUE_2");
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		protected override void Configure(IObjectTypeDescriptor<CEntityPaginationCursorBased> Descriptor)
		{
			Descriptor.Description($"This is OBJECT [{nameof(CEntityPaginationCursorBased)}].");

			ConfigureFieldID(Descriptor);
			ConfigureFieldValue1(Descriptor);
			ConfigureFieldValue2(Descriptor);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------