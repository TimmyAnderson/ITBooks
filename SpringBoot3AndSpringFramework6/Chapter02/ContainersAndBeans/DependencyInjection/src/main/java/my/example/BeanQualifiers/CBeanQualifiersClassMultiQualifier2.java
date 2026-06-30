package my.example.BeanQualifiers;
//----------------------------------------------------------------------------------------------------------------------
import org.springframework.stereotype.Component;
//----------------------------------------------------------------------------------------------------------------------
@Component
// !!!!! ANNOTATION [@IBeanQualifiersMultiAnnotation2] definuje UNIKATNY IDENTIFIKATOR BEAN.
@IBeanQualifiersMultiAnnotation2
public class CBeanQualifiersClassMultiQualifier2
{
//----------------------------------------------------------------------------------------------------------------------
	public String GetStringValue()
	{
		return("From MULTI QUALIFIER 2.");
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------