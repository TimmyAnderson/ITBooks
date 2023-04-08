//----------------------------------------------------------------------------------------------------------------------
package AspectAfter;
//----------------------------------------------------------------------------------------------------------------------
import org.springframework.stereotype.Component;
//----------------------------------------------------------------------------------------------------------------------
// !!! CLASS reprezentuje SPRING BEAN na ktory su aplikovane ASPECTS.
@Component
public class CAspectAfterBean
{
//----------------------------------------------------------------------------------------------------------------------
	// !!!!! Aplikuje sa CUSTOM ANNOTATION, aby sa na METHOD aplikoval ASPECT 'CAspectAfterAspect'.
	@IAspectAfterAnnotation
	public String PrintMessage(String Message)
	{
		System.out.format("CAspectAfterBean - MESSAGE [%s].\n",Message);
		
		return("My RETURN VALUE.");	
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------