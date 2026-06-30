package my.example.Components.Annotations;
//----------------------------------------------------------------------------------------------------------------------
import java.lang.annotation.Target;
import java.lang.annotation.ElementType;
import java.lang.annotation.Retention;
import java.lang.annotation.RetentionPolicy;

import org.springframework.stereotype.Component;
//----------------------------------------------------------------------------------------------------------------------
// !!!!! CUSTOM ANNOTATION na oznacenie COMPONENTS.
// !!!!! TYPES oznacene touto ANNOTATION budu povazovane za SPRING MANAGED BEANS, pretoze na CUSTOM ANNOTATION je aplikovana ANNOTATION [].
@Target(value=ElementType.TYPE)
@Retention(RetentionPolicy.RUNTIME)
@Component
public @interface IMyCustomComponentAnnotation
{
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------