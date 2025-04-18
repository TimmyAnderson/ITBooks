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
	public sealed class CObjectTypeDataLoaderBatchDependent : ObjectType<CDataLoaderBatchDependent>
	{
//----------------------------------------------------------------------------------------------------------------------
		private static void ConfigureFieldID(IObjectTypeDescriptor<CDataLoaderBatchDependent> Descriptor)
		{
			IObjectFieldDescriptor								FieldDescriptor=Descriptor.Field(P => P.DependentID);

			FieldDescriptor.Name("ID");
		}
//----------------------------------------------------------------------------------------------------------------------
		private static void ConfigureFieldValue1(IObjectTypeDescriptor<CDataLoaderBatchDependent> Descriptor)
		{
			IObjectFieldDescriptor								FieldDescriptor=Descriptor.Field(P => P.DependentValue1);

			FieldDescriptor.Name("VALUE1");
		}
//----------------------------------------------------------------------------------------------------------------------
		private static void ConfigureFieldValue2(IObjectTypeDescriptor<CDataLoaderBatchDependent> Descriptor)
		{
			IObjectFieldDescriptor								FieldDescriptor=Descriptor.Field(P => P.DependentValue2);

			FieldDescriptor.Name("VALUE2");
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		protected override void Configure(IObjectTypeDescriptor<CDataLoaderBatchDependent> Descriptor)
		{
			Descriptor.Description($"This is OBJECT [{nameof(CDataLoaderBatchDependent)}].");

			ConfigureFieldID(Descriptor);

			ConfigureFieldValue1(Descriptor);
			ConfigureFieldValue2(Descriptor);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------