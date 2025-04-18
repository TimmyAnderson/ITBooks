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
	public sealed class CObjectTypeUnionsMyClass1 : ObjectType<CUnionsMyClass1>
	{
//----------------------------------------------------------------------------------------------------------------------
		private static void ConfigureFieldID(IObjectTypeDescriptor<CUnionsMyClass1> Descriptor)
		{
			IObjectFieldDescriptor								FieldDescriptor=Descriptor.Field(P => P.ID);

			FieldDescriptor.Name("ID");
		}
//----------------------------------------------------------------------------------------------------------------------
		private static void ConfigureFieldSharedValue1(IObjectTypeDescriptor<CUnionsMyClass1> Descriptor)
		{
			IObjectFieldDescriptor								FieldDescriptor=Descriptor.Field(P => P.SharedValue1);

			FieldDescriptor.Name("SHARED_VALUE_1");
		}
//----------------------------------------------------------------------------------------------------------------------
		private static void ConfigureFieldSharedValue2(IObjectTypeDescriptor<CUnionsMyClass1> Descriptor)
		{
			IObjectFieldDescriptor								FieldDescriptor=Descriptor.Field(P => P.SharedValue2);

			FieldDescriptor.Name("SHARED_VALUE_2");
		}
//----------------------------------------------------------------------------------------------------------------------
		private static void ConfigureFieldClass1Value1(IObjectTypeDescriptor<CUnionsMyClass1> Descriptor)
		{
			IObjectFieldDescriptor								FieldDescriptor=Descriptor.Field(P => P.Class1Value1);

			FieldDescriptor.Name("CLASS_1_VALUE_1");
		}
//----------------------------------------------------------------------------------------------------------------------
		private static void ConfigureFieldClass1Value2(IObjectTypeDescriptor<CUnionsMyClass1> Descriptor)
		{
			IObjectFieldDescriptor								FieldDescriptor=Descriptor.Field(P => P.Class1Value2);

			FieldDescriptor.Name("CLASS_1_VALUE_2");
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		protected override void Configure(IObjectTypeDescriptor<CUnionsMyClass1> Descriptor)
		{
			Descriptor.Description($"This is OBJECT [{nameof(CUnionsMyClass1)}].");

			ConfigureFieldID(Descriptor);
			ConfigureFieldSharedValue1(Descriptor);
			ConfigureFieldSharedValue2(Descriptor);
			ConfigureFieldClass1Value1(Descriptor);
			ConfigureFieldClass1Value2(Descriptor);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------