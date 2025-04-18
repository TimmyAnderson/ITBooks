using HotChocolate.Data.Filters;
using HotChocolate.Data.Sorting;
//----------------------------------------------------------------------------------------------------------------------
namespace UsingGraphQL
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class CSortTypePaginationCursorBased : SortInputType<CEntityPaginationCursorBased>
	{
//----------------------------------------------------------------------------------------------------------------------
		private static void ConfigureFieldID(ISortInputTypeDescriptor<CEntityPaginationCursorBased> Descriptor)
		{
			// !!! FIELD sa prida do SORT INPUT TYPE.
			Descriptor.Field(P => P.ID);
		}
//----------------------------------------------------------------------------------------------------------------------
		private static void ConfigureFieldValue1(ISortInputTypeDescriptor<CEntityPaginationCursorBased> Descriptor)
		{
			// !!! FIELD sa prida do SORT INPUT TYPE.
			Descriptor.Field(P => P.Value1);
		}
//----------------------------------------------------------------------------------------------------------------------
		private static void ConfigureFieldValue2(ISortInputTypeDescriptor<CEntityPaginationCursorBased> Descriptor)
		{
			// !!! FIELD sa prida do SORT INPUT TYPE.
			Descriptor.Field(P => P.Value2);
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	    protected override void Configure(ISortInputTypeDescriptor<CEntityPaginationCursorBased> Descriptor)
		{
			// !!! METHOD nastavi, aby ziaden FIELD nebol automaticky pridany ako SORTING FIELD do SORT INPUT TYPE.
			Descriptor.BindFieldsExplicitly();

			ConfigureFieldID(Descriptor);
			ConfigureFieldValue1(Descriptor);
			ConfigureFieldValue2(Descriptor);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------