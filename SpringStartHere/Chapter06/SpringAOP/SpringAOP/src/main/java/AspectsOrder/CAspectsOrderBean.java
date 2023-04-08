//----------------------------------------------------------------------------------------------------------------------
package AspectsOrder;
//----------------------------------------------------------------------------------------------------------------------
import org.springframework.stereotype.Component;
//----------------------------------------------------------------------------------------------------------------------
// !!! CLASS reprezentuje SPRING BEAN na ktory su aplikovane ASPECTS.
@Component
public class CAspectsOrderBean
{
//----------------------------------------------------------------------------------------------------------------------
	// !!!!! Aplikuje sa CUSTOM ANNOTATION, aby sa na METHOD aplikoval ASPECT 'CAspectsOrderAspect'.
	@IAspectsOrderAnnotation
	public String PrintMessage(String Message)
	{
		System.out.format("CAspectsOrderBean - MESSAGE [%s].\n",Message);
		
		return("My RETURN VALUE.");	
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------