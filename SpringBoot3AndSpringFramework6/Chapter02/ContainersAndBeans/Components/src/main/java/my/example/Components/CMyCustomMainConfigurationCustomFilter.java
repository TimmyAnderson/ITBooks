package my.example.Components;
//----------------------------------------------------------------------------------------------------------------------
import my.example.Components.TypeFilters.CMyCustomTypeFilter;

import org.springframework.context.annotation.ComponentScan;
import org.springframework.context.annotation.FilterType;
//----------------------------------------------------------------------------------------------------------------------
// !!!!! COMPONENT SCAN sa robi v PACKAGE [my.example.Package1] a PACKAGE [my.example.Package2].
// !!!!! Kedze ELEMENT [useDefaultFilters] ma VALUE [false], implicitne nie su vlozene ziadne BEANS.
// !!!!! COMPONENT SCAN ako INCLUDE FILTER pouziva CUSTOM TYPE FILTER [CMyCustomTypeFilter]. 
@ComponentScan(basePackages={"my.example.Package1 my.example.Package2"},useDefaultFilters=false,includeFilters={@ComponentScan.Filter(type=FilterType.CUSTOM,classes=CMyCustomTypeFilter.class)})
public class CMyCustomMainConfigurationCustomFilter
{
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------