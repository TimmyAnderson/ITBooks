//----------------------------------------------------------------------------------------------------------------------
package SpringMultiImplementationQualifier;
//----------------------------------------------------------------------------------------------------------------------
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Qualifier;
import org.springframework.stereotype.Component;
//----------------------------------------------------------------------------------------------------------------------
// !!!!! ANNOTATION [@Component] sa VZDY aplikuje na TYPES z ktorych je mozne vytvorit instanciu. Teda NIE na INTERFACES a ABSTRACT CLASSES.
@Component
//----------------------------------------------------------------------------------------------------------------------
public class CSpringMultiImplementationQualifierPrinter2
{
//----------------------------------------------------------------------------------------------------------------------
	private final ISpringMultiImplementationQualifierPrintA		MPrintA;
	private final ISpringMultiImplementationQualifierPrintB		MPrintB;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	@Autowired
	// !!! ANNOTATION [@Qualifier] urcuju, ktore BEANS sa maju pouzit.
	public CSpringMultiImplementationQualifierPrinter2(@Qualifier("A2") ISpringMultiImplementationQualifierPrintA PrintA, @Qualifier("B2") ISpringMultiImplementationQualifierPrintB PrintB)
	{
		MPrintA=PrintA;	
		MPrintB=PrintB;	
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	public void PrintMessage(CSpringMultiImplementationQualifierMessage Message)
	{
		MPrintA.DoPrint1(Message);
		MPrintB.DoPrint2(Message);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------