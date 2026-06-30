package my.example.BeanQualifiers;
//----------------------------------------------------------------------------------------------------------------------
import org.springframework.stereotype.Component;
//----------------------------------------------------------------------------------------------------------------------
@Component
// !!!!! ANNOTATION [@IBeanQualifiersMultiAnnotation1] definuje UNIKATNY IDENTIFIKATOR BEAN.
@IBeanQualifiersMultiAnnotation1
public class CBeanQualifiersClassMultiQualifier1
{
//----------------------------------------------------------------------------------------------------------------------
	public String GetStringValue()
	{
		return("From MULTI QUALIFIER 1.");
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------