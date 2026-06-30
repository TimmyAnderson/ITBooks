package my.example.BeanQualifiers;
//----------------------------------------------------------------------------------------------------------------------
import org.springframework.stereotype.Component;
//----------------------------------------------------------------------------------------------------------------------
@Component
// !!!!! ANNOTATION [@IBeanQualifiersSingleAnnotation] definuje UNIKATNY IDENTIFIKATOR BEAN.
@IBeanQualifiersSingleAnnotation(IBeanQualifiersSingleAnnotation.EValue.VALUE_1)
public class CBeanQualifiersClassSingleQualifier1
{
//----------------------------------------------------------------------------------------------------------------------
	public String GetStringValue()
	{
		return("From SINGLE QUALIFIER 1.");
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------