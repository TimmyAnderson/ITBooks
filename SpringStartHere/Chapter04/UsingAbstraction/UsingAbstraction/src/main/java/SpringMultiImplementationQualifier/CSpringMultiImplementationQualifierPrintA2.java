//----------------------------------------------------------------------------------------------------------------------
package SpringMultiImplementationQualifier;
//----------------------------------------------------------------------------------------------------------------------
import org.springframework.beans.factory.annotation.Qualifier;
import org.springframework.stereotype.Component;
//----------------------------------------------------------------------------------------------------------------------
// !!!!! ANNOTATION [@Component] sa VZDY aplikuje na TYPES z ktorych je mozne vytvorit instanciu. Teda NIE na INTERFACES a ABSTRACT CLASSES.
@Component
// !!! ANNOTATION [@Qualifier] urcuje nazov SPRING BEAN OBJECT.
@Qualifier("A2")
public class CSpringMultiImplementationQualifierPrintA2 implements ISpringMultiImplementationQualifierPrintA
{
//----------------------------------------------------------------------------------------------------------------------
	@Override
	public void DoPrint1(CSpringMultiImplementationQualifierMessage Message)
	{
		System.out.format("FROM [CSpringMultiImplementationQualifierPrintA2] - MESSAGE [%s] !\n",Message.getMessage());
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------