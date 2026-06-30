package my.example.Components;
import my.example.Package1.CNonComponentPackage1Class;
//----------------------------------------------------------------------------------------------------------------------
import my.example.Package1.CPackage1Class;
import my.example.Package2.CPackage2Class;
import my.example.Package3.CPackage3Class;

import org.springframework.context.annotation.ComponentScan;
import org.springframework.context.annotation.FilterType;
//----------------------------------------------------------------------------------------------------------------------
// !!!!! COMPONENT SCAN sa robi v PACKAGE [my.example.Package1] a PACKAGE [my.example.Package2].
// !!!!! Kedze je nastaveny ELEMENT [useDefaultFilters] na VALUE [false], tak sa IMPLICITNE NEPRIDAVAJU ZIADNE BEANS.
// !!!!! BEANS, ktore maju byt pridane su EXPLICITNE definovane pomocou ELEMENT [includeFilters].
// !!!!! Ako BEAN sa zavedie aj CLASS [CNonComponentPackage1Class] hoci NIE je oznacena pomocou ANNOTATION [@Component].
@ComponentScan(basePackages={"my.example.Package1 my.example.Package2"},useDefaultFilters=false,includeFilters={@ComponentScan.Filter(type=FilterType.ASSIGNABLE_TYPE,classes={CPackage1Class.class,CPackage2Class.class}),@ComponentScan.Filter(type=FilterType.ASSIGNABLE_TYPE,classes=CPackage3Class.class),@ComponentScan.Filter(type=FilterType.ASSIGNABLE_TYPE,classes=CNonComponentPackage1Class.class)})
public class CMyCustomMainConfigurationIncludeFilters
{
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------