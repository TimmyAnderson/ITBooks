using HotChocolate.Data.Filters;
//----------------------------------------------------------------------------------------------------------------------
namespace UsingGraphQL
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class CFilterTypeFilteringByFluentAPIImplicit : FilterInputType<CEntityFilteringByFluentAPIImplicit>
	{
//----------------------------------------------------------------------------------------------------------------------
		private static void ConfigureFieldStringValue(IFilterInputTypeDescriptor<CEntityFilteringByFluentAPIImplicit> Descriptor)
		{
			// !!! FIELD sa prida do FILTER INPUT TYPE.
			IFilterFieldDescriptor								FilterFieldDescriptor=Descriptor.Field(P => P.StringValue);

			// !!! Nastavi sa CUSTOM FILTER INPUT TYPE pre STANDARD TYPE.
			FilterFieldDescriptor.Type<CCustomFilterInputTypeAPIImplicitString>();
		}
//----------------------------------------------------------------------------------------------------------------------
		private static void ConfigureFieldLongValue(IFilterInputTypeDescriptor<CEntityFilteringByFluentAPIImplicit> Descriptor)
		{
			// !!! FIELD sa odstrani z FILTER INPUT TYPE.
			Descriptor.Ignore(P => P.LongValue);
		}
//----------------------------------------------------------------------------------------------------------------------
		private static void ConfigureFieldDoubleValue(IFilterInputTypeDescriptor<CEntityFilteringByFluentAPIImplicit> Descriptor)
		{
			// !!! FIELD sa odstrani z FILTER INPUT TYPE.
			Descriptor.Ignore(P => P.DoubleValue);
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		protected override void Configure(IFilterInputTypeDescriptor<CEntityFilteringByFluentAPIImplicit> Descriptor)
		{
			// !!! METHOD nastavi, aby vsetky FIELDS boli automaticky pridane ako FILTERING FIELDS do FILTER INPUT TYPE.
			Descriptor.BindFieldsImplicitly();
			
			ConfigureFieldStringValue(Descriptor);
			ConfigureFieldLongValue(Descriptor);
			ConfigureFieldDoubleValue(Descriptor);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------