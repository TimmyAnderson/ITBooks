//----------------------------------------------------------------------------------------------------------------------
package DI2;
//----------------------------------------------------------------------------------------------------------------------
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Component;
//----------------------------------------------------------------------------------------------------------------------
// !!! Pouzije sa ANNOTATION [@Component], no mohol by sa pouzit aj ANNOTATION [@Bean] aplikovany na FACTORY METHOD v CONFIGURATION CLASS.
@Component
public class CDIConstructorParent
{
//----------------------------------------------------------------------------------------------------------------------
	private String												MValue;
	// !!! FIELD moze byt nastaveny na FINAL.
	private final CDIConstructorChild							MChild;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	// !!! ANNOTATION [@Autowired] sa aplikuje na CONSTRUCTOR, aby CONSTRUCTOR PARAMETER bol automaticky nastaveny SPRING FRAMEWORK pomocou DEPENDENCY INJECTION. 
	@Autowired
	public CDIConstructorParent(CDIConstructorChild Child)
	{
		System.out.println("CDIConstructorParent CREATED.");
		
		MValue="PARENT set in CONSTRUCTOR !!!";
		
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
	public CDIConstructorChild getChild()
	{
		return(MChild);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------