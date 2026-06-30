package my.example.Components;
//----------------------------------------------------------------------------------------------------------------------
import org.springframework.context.annotation.ComponentScan;
import org.springframework.context.annotation.FilterType;

import my.example.Components.Annotations.IMyComponentScanAnnotation;
//----------------------------------------------------------------------------------------------------------------------
// !!!!! COMPONENT SCAN sa robi v PACKAGE [my.example.Package1] a PACKAGE [my.example.Package2].
// !!!!! Kedze ELEMENT [useDefaultFilters] je ponechany na DEFAULT VALUE [true], tak sa IMPLICITNE PRIDAVAJU tie TYPES, na ktore je aplikovana ANNOTATION [@Component], alebo niektora z jej CHILD ANNOTATIONS.
// !!!!! Aplikovany ELEMENT [excludeFilters] znamena, ze sa vyradia vsetky tie TYPES na ktore je aplikovana ANNOTATION [@IMyComponentScanAnnotation], alebo niektora z jej CHILD ANNOTATIONS.
@ComponentScan(basePackages={"my.example.Package1 my.example.Package2"},excludeFilters={@ComponentScan.Filter(type=FilterType.ANNOTATION,classes={IMyComponentScanAnnotation.class})})
public class CMyCustomMainConfigurationExcludeFilters
{
//----------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------