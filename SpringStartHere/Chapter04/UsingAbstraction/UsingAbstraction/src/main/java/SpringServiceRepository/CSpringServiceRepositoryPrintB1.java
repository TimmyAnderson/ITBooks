//----------------------------------------------------------------------------------------------------------------------
package SpringServiceRepository;
//----------------------------------------------------------------------------------------------------------------------
import org.springframework.beans.factory.annotation.Qualifier;
import org.springframework.stereotype.Repository;
//----------------------------------------------------------------------------------------------------------------------
// !!!!! ANNOTATION [@Repository] sa VZDY aplikuje na TYPES z ktorych je mozne vytvorit instanciu. Teda NIE na INTERFACES a ABSTRACT CLASSES.
@Repository
// !!! ANNOTATION [@Qualifier] urcuje nazov SPRING BEAN OBJECT.
@Qualifier("B1")
public class CSpringServiceRepositoryPrintB1 implements ISpringServiceRepositoryPrintB
{
//----------------------------------------------------------------------------------------------------------------------
	@Override
	public void DoPrint2(CSpringServiceRepositoryMessage Message)
	{
		System.out.format("FROM [CSpringServiceRepositoryPrintB1] - MESSAGE [%s] !\n",Message.getMessage());
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------