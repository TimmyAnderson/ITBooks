using HotChocolate.Data;
using HotChocolate.Data.Filters;
using HotChocolate.Types;
//----------------------------------------------------------------------------------------------------------------------
namespace UsingGraphQL
{
//----------------------------------------------------------------------------------------------------------------------
	// !!! CUSTOM FILTER INPUT TYPE obsahuje povolene FILTERING OPERATIONS.
	public sealed class CCustomFilterInputTypeFilteringManuallyInt : IntOperationFilterInputType
	{
//----------------------------------------------------------------------------------------------------------------------
		private static void ConfigureOperationEquals(IFilterInputTypeDescriptor Descriptor)
		{
			IFilterOperationFieldDescriptor						OperationDescriptor=Descriptor.Operation(DefaultFilterOperations.Equals);

			// !!! Pre OPERATION sa nastavi jej FILTER INPUT TYPE cim sa OPERATION povoli.
			OperationDescriptor.Type<IntType>();
		}
//----------------------------------------------------------------------------------------------------------------------
		private static void ConfigureOperationIn(IFilterInputTypeDescriptor Descriptor)
		{
			IFilterOperationFieldDescriptor						OperationDescriptor=Descriptor.Operation(DefaultFilterOperations.In);

			// !!! Pre OPERATION sa nastavi jej FILTER INPUT TYPE cim sa OPERATION povoli.
			// !!!!! Pretoze TYPE moze obsahovat viac ITEMS, pouzije sa COLLECTION TYPE.
			OperationDescriptor.Type<ListType<NonNullType<IntType>>>();
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		protected override void Configure(IFilterInputTypeDescriptor Descriptor)
		{
			ConfigureOperationEquals(Descriptor);
			ConfigureOperationIn(Descriptor);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------