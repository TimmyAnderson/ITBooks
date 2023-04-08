//----------------------------------------------------------------------------------------------------------------------
package SpringMultiImplementationPrimary;
//----------------------------------------------------------------------------------------------------------------------
import org.springframework.context.annotation.Primary;
import org.springframework.stereotype.Component;
//----------------------------------------------------------------------------------------------------------------------
// !!!!! ANNOTATION [@Component] sa VZDY aplikuje na TYPES z ktorych je mozne vytvorit instanciu. Teda NIE na INTERFACES a ABSTRACT CLASSES.
@Component
// !!!!! ANNOTATION [@Primary] definuje, ze CLASS bude reprezentovat primarnu implementaciu INTERFACE 'ISpringMultiImplementationPrimaryPrintA', ktoru SPRING FRAMEWORK vyuzije na vytvaranie BEANS TYPE 'ISpringMultiImplementationPrimaryPrintA'.
@Primary
public class CSpringMultiImplementationPrimaryPrintA1 implements ISpringMultiImplementationPrimaryPrintA
{
//----------------------------------------------------------------------------------------------------------------------
	@Override
	public void DoPrint1(CSpringMultiImplementationPrimaryMessage Message)
	{
		System.out.format("FROM [CSpringMultiImplementationPrimaryPrintA1] - MESSAGE [%s] !\n",Message.getMessage());
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------