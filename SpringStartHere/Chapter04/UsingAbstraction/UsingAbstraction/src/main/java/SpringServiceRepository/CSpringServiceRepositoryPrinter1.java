//----------------------------------------------------------------------------------------------------------------------
package SpringServiceRepository;
//----------------------------------------------------------------------------------------------------------------------
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Qualifier;
import org.springframework.stereotype.Repository;
//----------------------------------------------------------------------------------------------------------------------
// !!!!! ANNOTATION [@Repository] sa VZDY aplikuje na TYPES z ktorych je mozne vytvorit instanciu. Teda NIE na INTERFACES a ABSTRACT CLASSES.
@Repository
//----------------------------------------------------------------------------------------------------------------------
public class CSpringServiceRepositoryPrinter1
{
//----------------------------------------------------------------------------------------------------------------------
	private final ISpringServiceRepositoryPrintA				MPrintA;
	private final ISpringServiceRepositoryPrintB				MPrintB;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	@Autowired
	// !!! ANNOTATION [@Qualifier] urcuju, ktore BEANS sa maju pouzit.
	public CSpringServiceRepositoryPrinter1(@Qualifier("A1") ISpringServiceRepositoryPrintA PrintA, @Qualifier("B1") ISpringServiceRepositoryPrintB PrintB)
	{
		MPrintA=PrintA;	
		MPrintB=PrintB;	
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	public void PrintMessage(CSpringServiceRepositoryMessage Message)
	{
		MPrintA.DoPrint1(Message);
		MPrintB.DoPrint2(Message);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------