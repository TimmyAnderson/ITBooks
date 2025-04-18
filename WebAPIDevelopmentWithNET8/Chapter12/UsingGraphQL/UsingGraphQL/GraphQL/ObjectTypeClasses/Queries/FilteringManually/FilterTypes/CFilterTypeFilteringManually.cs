using HotChocolate.Data.Filters;
//----------------------------------------------------------------------------------------------------------------------
namespace UsingGraphQL
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class CFilterTypeFilteringManually : FilterInputType<CFilteringManually>
	{
//----------------------------------------------------------------------------------------------------------------------
		private static void ConfigureFieldID(IFilterInputTypeDescriptor<CFilteringManually> Descriptor)
		{
			// !!! FIELD sa prida do FILTER INPUT TYPE.
			IFilterFieldDescriptor								FilterFieldDescriptor=Descriptor.Field(P => P.ID);

			FilterFieldDescriptor.Name("ID");

			// !!!!! Nastavi sa CUSTOM FILTER INPUT TYPE pre FIELD, ktory obsahuje FILTERING OPERATIONS, ktore mozne nad danym FIELD vykonavat.
			FilterFieldDescriptor.Type<CCustomFilterInputTypeFilteringManuallyInt>();
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		protected override void Configure(IFilterInputTypeDescriptor<CFilteringManually> Descriptor)
		{
			// !!! METHOD nastavi, aby ziaden FIELD nebol automaticky pridany ako FILTERING FIELD do FILTER INPUT TYPE.
			Descriptor.BindFieldsExplicitly();
			
			Descriptor.Name("FilteringManually");

			// !!! Zakaze sa OPERATOR [and].
			Descriptor.AllowAnd(false);

			// !!! Zakaze sa OPERATOR [or].
			Descriptor.AllowOr(false);

			ConfigureFieldID(Descriptor);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------