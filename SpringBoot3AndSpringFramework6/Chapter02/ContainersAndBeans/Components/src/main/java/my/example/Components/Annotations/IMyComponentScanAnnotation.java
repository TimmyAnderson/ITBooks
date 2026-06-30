package my.example.Components.Annotations;
//----------------------------------------------------------------------------------------------------------------------
import java.lang.annotation.ElementType;
import java.lang.annotation.Retention;
import java.lang.annotation.RetentionPolicy;
import java.lang.annotation.Target;
//----------------------------------------------------------------------------------------------------------------------
// !!!!! ANNOTATIONS MUSIA byt oznacene pomocou tychto ANNOTATIONS, aby ich JAVA RUNTIME bol schopny najst.
@Target(value=ElementType.TYPE)
@Retention(RetentionPolicy.RUNTIME)
public @interface IMyComponentScanAnnotation
{
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------