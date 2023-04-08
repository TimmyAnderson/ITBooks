//----------------------------------------------------------------------------------------------------------------------
package AspectsOnAnnotations;
//----------------------------------------------------------------------------------------------------------------------
import org.springframework.stereotype.Component;
//----------------------------------------------------------------------------------------------------------------------
// !!! CLASS reprezentuje SPRING BEAN na ktory su aplikovane ASPECTS.
@Component
public class CAspectsOnAnnotationsBean
{
//----------------------------------------------------------------------------------------------------------------------
	// !!!!! Aplikuje sa CUSTOM ANNOTATION, aby sa na METHOD aplikoval ASPECT 'CAspectsOnAnnotationsAspect'.
	@IAspectsOnAnnotationsAnnotation
	public String PrintMessage(String Message)
	{
		System.out.format("CAspectsOnAnnotationsBean - MESSAGE [%s].\n",Message);
		
		return("My RETURN VALUE.");	
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------