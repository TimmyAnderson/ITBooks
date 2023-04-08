//----------------------------------------------------------------------------------------------------------------------
package SpringMultiImplementationPrimary;
//----------------------------------------------------------------------------------------------------------------------
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Component;
//----------------------------------------------------------------------------------------------------------------------
// !!!!! ANNOTATION [@Component] sa VZDY aplikuje na TYPES z ktorych je mozne vytvorit instanciu. Teda NIE na INTERFACES a ABSTRACT CLASSES.
@Component
//----------------------------------------------------------------------------------------------------------------------
public class CSpringMultiImplementationPrimaryPrinter
{
//----------------------------------------------------------------------------------------------------------------------
	private final ISpringMultiImplementationPrimaryPrintA		MPrintA;
	private final ISpringMultiImplementationPrimaryPrintB		MPrintB;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	@Autowired
	public CSpringMultiImplementationPrimaryPrinter(ISpringMultiImplementationPrimaryPrintA PrintA, ISpringMultiImplementationPrimaryPrintB PrintB)
	{
		MPrintA=PrintA;	
		MPrintB=PrintB;	
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	public void PrintMessage(CSpringMultiImplementationPrimaryMessage Message)
	{
		MPrintA.DoPrint1(Message);
		MPrintB.DoPrint2(Message);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------