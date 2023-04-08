//----------------------------------------------------------------------------------------------------------------------
package DI3;
//----------------------------------------------------------------------------------------------------------------------
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Component;
//----------------------------------------------------------------------------------------------------------------------
// !!! Pouzije sa ANNOTATION [@Component], no mohol by sa pouzit aj ANNOTATION [@Bean] aplikovany na FACTORY METHOD v CONFIGURATION CLASS.
@Component
public class CDISetterParent
{
//----------------------------------------------------------------------------------------------------------------------
	private String												MValue;
	private CDISetterChild										MChild;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	public CDISetterParent()
	{
		System.out.println("CDISetterParent CREATED.");
		
		MValue="PARENT set in CONSTRUCTOR !!!";
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
	public CDISetterChild getChild()
	{
		return(MChild);
	}
//----------------------------------------------------------------------------------------------------------------------
	// !!! ANNOTATION [@Autowired] sa aplikuje na SETTER, aby SETTER bol automaticky volany SPRING FRAMEWORK. 
	@Autowired
	public void setChild(CDISetterChild Child)
	{
		System.out.println("CDISetterChild SETTER in CDISetterParent is CALLED.");
	
		MChild=Child;
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------