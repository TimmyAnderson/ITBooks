//----------------------------------------------------------------------------------------------------------------------
package MultipleBeansFieldQualifier;
//----------------------------------------------------------------------------------------------------------------------
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Qualifier;
//----------------------------------------------------------------------------------------------------------------------
public class CMultipleBeansFieldQualifierParent
{
//----------------------------------------------------------------------------------------------------------------------
	private String												MValue;
	// !!! ANNOTATION [@Autowired] sa aplikuje na FIELD, aby FIELD bol automaticky nastaveny SPRING FRAMEWORK pomocou DEPENDENCY INJECTION.
	// !!!!! Nazov v ANNOTATION [@Qualifier] sa MUSI zhodovat s nazvom BEAN.
	@Autowired
	@Qualifier("MyChild")
	private CMultipleBeansFieldQualifierChild					MChild;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	public CMultipleBeansFieldQualifierParent()
	{
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
	public CMultipleBeansFieldQualifierChild getChild()
	{
		return(MChild);
	}
//----------------------------------------------------------------------------------------------------------------------
	public void setChild(CMultipleBeansFieldQualifierChild Child)
	{
		MChild=Child;
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------