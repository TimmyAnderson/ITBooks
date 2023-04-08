//----------------------------------------------------------------------------------------------------------------------
package AspectBefore;
//----------------------------------------------------------------------------------------------------------------------
import org.springframework.stereotype.Component;
//----------------------------------------------------------------------------------------------------------------------
// !!! CLASS reprezentuje SPRING BEAN na ktory su aplikovane ASPECTS.
@Component
public class CAspectBeforeBean
{
//----------------------------------------------------------------------------------------------------------------------
	// !!!!! Aplikuje sa CUSTOM ANNOTATION, aby sa na METHOD aplikoval ASPECT 'CAspectBeforeAspect'.
	@IAspectBeforeAnnotation
	public String PrintMessage(String Message)
	{
		System.out.format("CAspectBeforeBean - MESSAGE [%s].\n",Message);
		
		return("My RETURN VALUE.");	
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------