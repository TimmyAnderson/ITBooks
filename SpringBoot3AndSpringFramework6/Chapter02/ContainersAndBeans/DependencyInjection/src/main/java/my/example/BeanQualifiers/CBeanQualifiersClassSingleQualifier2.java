package my.example.BeanQualifiers;
//----------------------------------------------------------------------------------------------------------------------
import org.springframework.stereotype.Component;
//----------------------------------------------------------------------------------------------------------------------
@Component
// !!!!! ANNOTATION [@IBeanQualifiersSingleAnnotation] definuje UNIKATNY IDENTIFIKATOR BEAN.
@IBeanQualifiersSingleAnnotation(IBeanQualifiersSingleAnnotation.EValue.VALUE_2)
public class CBeanQualifiersClassSingleQualifier2
{
//----------------------------------------------------------------------------------------------------------------------
	public String GetStringValue()
	{
		return("From SINGLE QUALIFIER 2.");
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------