//----------------------------------------------------------------------------------------------------------------------
package Spring2;
//----------------------------------------------------------------------------------------------------------------------
import org.springframework.beans.factory.annotation.Autowired;
//----------------------------------------------------------------------------------------------------------------------
public class CSpring2Printer
{
//----------------------------------------------------------------------------------------------------------------------
	// !!! Na FIELD sa aplikuje ANNOTATION [@Autowired], aby FIELD naplnil SPRING FRAMEWORK. 
	@Autowired
	private ISpring2PrintA										MPrintA;
	// !!! Na FIELD sa aplikuje ANNOTATION [@Autowired], aby FIELD naplnil SPRING FRAMEWORK. 
	@Autowired
	private ISpring2PrintB										MPrintB;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	public CSpring2Printer()
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	public void PrintMessage(CSpring2Message Message)
	{
		MPrintA.DoPrint1(Message);
		MPrintB.DoPrint2(Message);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------