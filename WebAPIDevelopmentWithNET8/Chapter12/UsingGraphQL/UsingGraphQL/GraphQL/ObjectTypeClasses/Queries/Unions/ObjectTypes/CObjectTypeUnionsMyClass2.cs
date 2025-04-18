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
	public sealed class CObjectTypeUnionsMyClass2 : ObjectType<CUnionsMyClass2>
	{
//----------------------------------------------------------------------------------------------------------------------
		private static void ConfigureFieldID(IObjectTypeDescriptor<CUnionsMyClass2> Descriptor)
		{
			IObjectFieldDescriptor								FieldDescriptor=Descriptor.Field(P => P.ID);

			FieldDescriptor.Name("ID");
		}
//----------------------------------------------------------------------------------------------------------------------
		private static void ConfigureFieldSharedValue1(IObjectTypeDescriptor<CUnionsMyClass2> Descriptor)
		{
			IObjectFieldDescriptor								FieldDescriptor=Descriptor.Field(P => P.SharedValue1);

			FieldDescriptor.Name("SHARED_VALUE_1");
		}
//----------------------------------------------------------------------------------------------------------------------
		private static void ConfigureFieldSharedValue2(IObjectTypeDescriptor<CUnionsMyClass2> Descriptor)
		{
			IObjectFieldDescriptor								FieldDescriptor=Descriptor.Field(P => P.SharedValue2);

			FieldDescriptor.Name("SHARED_VALUE_2");
		}
//----------------------------------------------------------------------------------------------------------------------
		private static void ConfigureFieldClass2Value1(IObjectTypeDescriptor<CUnionsMyClass2> Descriptor)
		{
			IObjectFieldDescriptor								FieldDescriptor=Descriptor.Field(P => P.Class2Value1);

			FieldDescriptor.Name("CLASS_2_VALUE_1");
		}
//----------------------------------------------------------------------------------------------------------------------
		private static void ConfigureFieldClass2Value2(IObjectTypeDescriptor<CUnionsMyClass2> Descriptor)
		{
			IObjectFieldDescriptor								FieldDescriptor=Descriptor.Field(P => P.Class2Value2);

			FieldDescriptor.Name("CLASS_2_VALUE_2");
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		protected override void Configure(IObjectTypeDescriptor<CUnionsMyClass2> Descriptor)
		{
			Descriptor.Description($"This is OBJECT [{nameof(CUnionsMyClass2)}].");

			ConfigureFieldID(Descriptor);
			ConfigureFieldSharedValue1(Descriptor);
			ConfigureFieldSharedValue2(Descriptor);
			ConfigureFieldClass2Value1(Descriptor);
			ConfigureFieldClass2Value2(Descriptor);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------