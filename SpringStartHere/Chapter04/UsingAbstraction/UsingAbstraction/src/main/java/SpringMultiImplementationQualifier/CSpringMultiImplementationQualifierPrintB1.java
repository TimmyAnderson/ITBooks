//----------------------------------------------------------------------------------------------------------------------
package SpringMultiImplementationQualifier;
//----------------------------------------------------------------------------------------------------------------------
import org.springframework.beans.factory.annotation.Qualifier;
import org.springframework.stereotype.Component;
//----------------------------------------------------------------------------------------------------------------------
// !!!!! ANNOTATION [@Component] sa VZDY aplikuje na TYPES z ktorych je mozne vytvorit instanciu. Teda NIE na INTERFACES a ABSTRACT CLASSES.
@Component
// !!! ANNOTATION [@Qualifier] urcuje nazov SPRING BEAN OBJECT.
@Qualifier("B1")
public class CSpringMultiImplementationQualifierPrintB1 implements ISpringMultiImplementationQualifierPrintB
{
//----------------------------------------------------------------------------------------------------------------------
	@Override
	public void DoPrint2(CSpringMultiImplementationQualifierMessage Message)
	{
		System.out.format("FROM [CSpringMultiImplementationQualifierPrintB1] - MESSAGE [%s] !\n",Message.getMessage());
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------