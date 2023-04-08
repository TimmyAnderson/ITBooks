//----------------------------------------------------------------------------------------------------------------------
package AspectBefore;
//----------------------------------------------------------------------------------------------------------------------
import java.lang.annotation.ElementType;
import java.lang.annotation.Retention;
import java.lang.annotation.RetentionPolicy;
import java.lang.annotation.Target;
//----------------------------------------------------------------------------------------------------------------------
// !!! DEFINUJE CUSTOM ANNOTATION.
// !!!!! Na CUSTOM ANNOTATION MUSI byt aplikovany ANNOTATION [@Retention], aby ANNOTATION bol pristupny aj v RUNTIME.
@Retention(RetentionPolicy.RUNTIME)
@Target(ElementType.METHOD)
public @interface IAspectBeforeAnnotation
{
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------