package my.example.BeanQualifiers;
//----------------------------------------------------------------------------------------------------------------------
import java.lang.annotation.ElementType;
import java.lang.annotation.Retention;
import java.lang.annotation.RetentionPolicy;
import java.lang.annotation.Target;

import org.springframework.beans.factory.annotation.Qualifier;
//----------------------------------------------------------------------------------------------------------------------
@Target({ElementType.FIELD,ElementType.METHOD,ElementType.TYPE,ElementType.PARAMETER,ElementType.ANNOTATION_TYPE})
@Retention(RetentionPolicy.RUNTIME)
@Qualifier
public @interface IBeanQualifiersSingleAnnotation
{
//----------------------------------------------------------------------------------------------------------------------
	enum EValue
	{
		VALUE_1,
		VALUE_2
	}	
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	EValue value();
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------