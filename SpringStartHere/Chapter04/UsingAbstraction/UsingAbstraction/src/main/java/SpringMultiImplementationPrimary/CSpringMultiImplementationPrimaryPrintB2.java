//----------------------------------------------------------------------------------------------------------------------
package SpringMultiImplementationPrimary;
//----------------------------------------------------------------------------------------------------------------------
import org.springframework.stereotype.Component;
//----------------------------------------------------------------------------------------------------------------------
// !!!!! ANNOTATION [@Component] sa VZDY aplikuje na TYPES z ktorych je mozne vytvorit instanciu. Teda NIE na INTERFACES a ABSTRACT CLASSES.
@Component
public class CSpringMultiImplementationPrimaryPrintB2 implements ISpringMultiImplementationPrimaryPrintB
{
//----------------------------------------------------------------------------------------------------------------------
	@Override
	public void DoPrint2(CSpringMultiImplementationPrimaryMessage Message)
	{
		System.out.format("FROM [CSpringMultiImplementationPrimaryPrintB2] - MESSAGE [%s] !\n",Message.getMessage());
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------