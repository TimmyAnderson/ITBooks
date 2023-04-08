//----------------------------------------------------------------------------------------------------------------------
package SpringServiceRepository;
//----------------------------------------------------------------------------------------------------------------------
import org.springframework.beans.factory.annotation.Qualifier;
import org.springframework.stereotype.Repository;
//----------------------------------------------------------------------------------------------------------------------
// !!!!! ANNOTATION [@Repository] sa VZDY aplikuje na TYPES z ktorych je mozne vytvorit instanciu. Teda NIE na INTERFACES a ABSTRACT CLASSES.
@Repository
// !!! ANNOTATION [@Qualifier] urcuje nazov SPRING BEAN OBJECT.
@Qualifier("A2")
public class CSpringServiceRepositoryPrintA2 implements ISpringServiceRepositoryPrintA
{
//----------------------------------------------------------------------------------------------------------------------
	@Override
	public void DoPrint1(CSpringServiceRepositoryMessage Message)
	{
		System.out.format("FROM [CSpringServiceRepositoryPrintA2] - MESSAGE [%s] !\n",Message.getMessage());
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------