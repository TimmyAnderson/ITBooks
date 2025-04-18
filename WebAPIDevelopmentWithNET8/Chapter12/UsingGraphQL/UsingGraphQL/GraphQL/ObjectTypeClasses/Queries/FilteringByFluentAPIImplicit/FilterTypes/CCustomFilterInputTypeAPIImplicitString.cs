using HotChocolate.Data.Filters;
using HotChocolate.Types;
//----------------------------------------------------------------------------------------------------------------------
namespace UsingGraphQL
{
//----------------------------------------------------------------------------------------------------------------------
	// !!! Vytvori sa CUSTOM FILTER INPUT TYPE pre STANDARD TYPE.
	public sealed class CCustomFilterInputTypeAPIImplicitString : StringOperationFilterInputType
	{
//----------------------------------------------------------------------------------------------------------------------
		private static void ConfigureOperationStartsWith(IFilterInputTypeDescriptor Descriptor)
		{
			IFilterOperationFieldDescriptor						OperationDescriptor=Descriptor.Operation(DefaultFilterOperations.StartsWith);

			// !!! Pre OPERATION sa nastavi jej FILTER INPUT TYPE cim sa OPERATION povoli.
			OperationDescriptor.Type<StringType>();
		}
//----------------------------------------------------------------------------------------------------------------------
		private static void ConfigureOperationEndsWith(IFilterInputTypeDescriptor Descriptor)
		{
			IFilterOperationFieldDescriptor						OperationDescriptor=Descriptor.Operation(DefaultFilterOperations.EndsWith);

			// !!! Pre OPERATION sa nastavi jej FILTER INPUT TYPE cim sa OPERATION povoli.
			OperationDescriptor.Type<StringType>();
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		protected override void Configure(IFilterInputTypeDescriptor Descriptor)
		{
			ConfigureOperationStartsWith(Descriptor);
			ConfigureOperationEndsWith(Descriptor);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------