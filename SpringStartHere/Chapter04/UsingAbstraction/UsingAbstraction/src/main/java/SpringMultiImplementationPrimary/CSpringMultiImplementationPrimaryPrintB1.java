//----------------------------------------------------------------------------------------------------------------------
package SpringMultiImplementationPrimary;
//----------------------------------------------------------------------------------------------------------------------
import org.springframework.context.annotation.Primary;
import org.springframework.stereotype.Component;
//----------------------------------------------------------------------------------------------------------------------
// !!!!! ANNOTATION [@Component] sa VZDY aplikuje na TYPES z ktorych je mozne vytvorit instanciu. Teda NIE na INTERFACES a ABSTRACT CLASSES.
@Component
// !!!!! ANNOTATION [@Primary] definuje, ze CLASS bude reprezentovat primarnu implementaciu INTERFACE 'ISpringMultiImplementationPrimaryPrintB', ktoru SPRING FRAMEWORK vyuzije na vytvaranie BEANS TYPE 'ISpringMultiImplementationPrimaryPrintB'.
@Primary
public class CSpringMultiImplementationPrimaryPrintB1 implements ISpringMultiImplementationPrimaryPrintB
{
//----------------------------------------------------------------------------------------------------------------------
	@Override
	public void DoPrint2(CSpringMultiImplementationPrimaryMessage Message)
	{
		System.out.format("FROM [CSpringMultiImplementationPrimaryPrintB1] - MESSAGE [%s] !\n",Message.getMessage());
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------