//----------------------------------------------------------------------------------------------------------------------
package SingletonByStereotype;
//----------------------------------------------------------------------------------------------------------------------
import org.springframework.stereotype.Component;
//----------------------------------------------------------------------------------------------------------------------
@Component
public class CSingletonByStereotypeBeanChild
{
//----------------------------------------------------------------------------------------------------------------------
	public CSingletonByStereotypeBeanChild()
	{
		System.out.format("BEAN [CSingletonByStereotypeBeanChild] CREATED.\n");
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------