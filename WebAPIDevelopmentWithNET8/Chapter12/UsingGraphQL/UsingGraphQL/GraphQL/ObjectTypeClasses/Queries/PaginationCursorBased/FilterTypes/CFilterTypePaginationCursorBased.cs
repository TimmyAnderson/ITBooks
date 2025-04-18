using HotChocolate.Data.Filters;
//----------------------------------------------------------------------------------------------------------------------
namespace UsingGraphQL
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class CFilterTypePaginationCursorBased : FilterInputType<CEntityPaginationCursorBased>
	{
//----------------------------------------------------------------------------------------------------------------------
		private static void ConfigureFieldID(IFilterInputTypeDescriptor<CEntityPaginationCursorBased> Descriptor)
		{
			// !!! FIELD sa prida do FILTER INPUT TYPE.
			Descriptor.Field(P => P.ID);
		}
//----------------------------------------------------------------------------------------------------------------------
		private static void ConfigureFieldValue1(IFilterInputTypeDescriptor<CEntityPaginationCursorBased> Descriptor)
		{
			// !!! FIELD sa prida do FILTER INPUT TYPE.
			Descriptor.Field(P => P.Value1);
		}
//----------------------------------------------------------------------------------------------------------------------
		private static void ConfigureFieldValue2(IFilterInputTypeDescriptor<CEntityPaginationCursorBased> Descriptor)
		{
			// !!! FIELD sa prida do FILTER INPUT TYPE.
			Descriptor.Field(P => P.Value2);
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		protected override void Configure(IFilterInputTypeDescriptor<CEntityPaginationCursorBased> Descriptor)
		{
			// !!! METHOD nastavi, aby ziaden FIELD nebol automaticky pridany ako FILTERING FIELD do FILTER INPUT TYPE.
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