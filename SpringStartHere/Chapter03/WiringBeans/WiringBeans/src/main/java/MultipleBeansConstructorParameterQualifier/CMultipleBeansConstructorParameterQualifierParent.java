//----------------------------------------------------------------------------------------------------------------------
package MultipleBeansConstructorParameterQualifier;
//----------------------------------------------------------------------------------------------------------------------
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Qualifier;
import org.springframework.stereotype.Component;
//----------------------------------------------------------------------------------------------------------------------
// !!! Pouzije sa ANNOTATION [@Component], no mohol by sa pouzit aj ANNOTATION [@Bean] aplikovany na FACTORY METHOD v CONFIGURATION CLASS.
@Component
public class CMultipleBeansConstructorParameterQualifierParent
{
//----------------------------------------------------------------------------------------------------------------------
	private String												MValue;
	private CMultipleBeansConstructorParameterQualifierChild	MChild;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	// !!! ANNOTATION [@Autowired] sa aplikuje na CONSTRUCTOR, aby CONSTRUCTOR PARAMETER bol automaticky nastaveny SPRING FRAMEWORK pomocou DEPENDENCY INJECTION.
	// !!!!! Ak ma CLASS iba 1 CONSTRUCTOR, tak ANNOTATION [@Autowired] je OPTIONAL.  
	// !!!!! Nazov v CONSTRUCTOR PARAMETER ANNOTATION [@Qualifier] sa MUSI zhodovat s nazvom BEAN.
	@Autowired 
	public CMultipleBeansConstructorParameterQualifierParent(@Qualifier("MyChild") CMultipleBeansConstructorParameterQualifierChild Child)
	{
		MValue="PARENT BEAN !!!";
	
		MChild=Child;
	} 	
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	public String getValue()
	{
		return(MValue);
	}
//----------------------------------------------------------------------------------------------------------------------
	public void setValue(String Value)
	{
		MValue=Value;
	}
//----------------------------------------------------------------------------------------------------------------------
	public CMultipleBeansConstructorParameterQualifierChild getChild()
	{
		return(MChild);
	}
//----------------------------------------------------------------------------------------------------------------------
	public void setChild(CMultipleBeansConstructorParameterQualifierChild Child)
	{
		MChild=Child;
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------