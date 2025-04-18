using HotChocolate.Data.Filters;
using HotChocolate.Data.Sorting;
//----------------------------------------------------------------------------------------------------------------------
namespace UsingGraphQL
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class CSortTypeFilteringByFluentAPI : SortInputType<CEntitySortingByFluentAPI>
	{
//----------------------------------------------------------------------------------------------------------------------
		private static void ConfigureFieldStringValue(ISortInputTypeDescriptor<CEntitySortingByFluentAPI> Descriptor)
		{
			// !!! FIELD sa prida do SORT INPUT TYPE.
			Descriptor.Field(P => P.ValueString);
		}
//----------------------------------------------------------------------------------------------------------------------
		private static void ConfigureFieldIntValue(ISortInputTypeDescriptor<CEntitySortingByFluentAPI> Descriptor)
		{
			// !!! FIELD sa prida do SORT INPUT TYPE.
			Descriptor.Field(P => P.ValueInt);
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	    protected override void Configure(ISortInputTypeDescriptor<CEntitySortingByFluentAPI> Descriptor)
		{
			// !!! METHOD nastavi, aby ziaden FIELD nebol automaticky pridany ako SORTING FIELD do SORT INPUT TYPE.
			Descriptor.BindFieldsExplicitly();

			ConfigureFieldStringValue(Descriptor);
			ConfigureFieldIntValue(Descriptor);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------