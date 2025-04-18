using HotChocolate.Data.Filters;
//----------------------------------------------------------------------------------------------------------------------
namespace UsingGraphQL
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class CFilterTypeFilteringByFluentAPIExplicit : FilterInputType<CEntityFilteringByFluentAPIExplicit>
	{
//----------------------------------------------------------------------------------------------------------------------
		private static void ConfigureFieldStringValue(IFilterInputTypeDescriptor<CEntityFilteringByFluentAPIExplicit> Descriptor)
		{
			// !!! FIELD sa prida do FILTER INPUT TYPE.
			IFilterFieldDescriptor								FilterFieldDescriptor=Descriptor.Field(P => P.StringValue);

			// !!! Nastavi sa CUSTOM FILTER INPUT TYPE pre STANDARD TYPE.
			FilterFieldDescriptor.Type<CCustomFilterInputTypeAPIExplicitString>();
		}
//----------------------------------------------------------------------------------------------------------------------
		private static void ConfigureFieldIntValue(IFilterInputTypeDescriptor<CEntityFilteringByFluentAPIExplicit> Descriptor)
		{
			// !!! FIELD sa prida do FILTER INPUT TYPE.
			Descriptor.Field(P => P.IntValue);
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		protected override void Configure(IFilterInputTypeDescriptor<CEntityFilteringByFluentAPIExplicit> Descriptor)
		{
			// !!! METHOD nastavi, aby ziaden FIELD nebol automaticky pridany ako FILTERING FIELD do FILTER INPUT TYPE.
			Descriptor.BindFieldsExplicitly();

			ConfigureFieldStringValue(Descriptor);
			ConfigureFieldIntValue(Descriptor);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------