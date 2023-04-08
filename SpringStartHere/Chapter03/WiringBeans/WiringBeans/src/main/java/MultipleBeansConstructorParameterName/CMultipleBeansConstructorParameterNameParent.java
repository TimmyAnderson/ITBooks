//----------------------------------------------------------------------------------------------------------------------
package MultipleBeansConstructorParameterName;
//----------------------------------------------------------------------------------------------------------------------
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Component;
//----------------------------------------------------------------------------------------------------------------------
// !!! Pouzije sa ANNOTATION [@Component], no mohol by sa pouzit aj ANNOTATION [@Bean] aplikovany na FACTORY METHOD v CONFIGURATION CLASS.
@Component
public class CMultipleBeansConstructorParameterNameParent
{
//----------------------------------------------------------------------------------------------------------------------
	private String												MValue;
	private CMultipleBeansConstructorParameterNameChild			MChild;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	// !!! ANNOTATION [@Autowired] sa aplikuje na CONSTRUCTOR, aby CONSTRUCTOR PARAMETER bol automaticky nastaveny SPRING FRAMEWORK pomocou DEPENDENCY INJECTION. 
	// !!!!! Ak ma CLASS iba 1 CONSTRUCTOR, tak ANNOTATION [@Autowired] je OPTIONAL.  
	// !!!!! Nazov CONSTRUCTOR PARAMETER sa MUSI zhodovat s nazvom BEAN. 
	@Autowired
	public CMultipleBeansConstructorParameterNameParent(CMultipleBeansConstructorParameterNameChild Child)
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
	public CMultipleBeansConstructorParameterNameChild getChild()
	{
		return(MChild);
	}
//----------------------------------------------------------------------------------------------------------------------
	public void setChild(CMultipleBeansConstructorParameterNameChild Child)
	{
		MChild=Child;
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------