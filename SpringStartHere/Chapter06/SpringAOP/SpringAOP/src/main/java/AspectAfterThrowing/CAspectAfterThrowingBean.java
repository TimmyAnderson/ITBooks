//----------------------------------------------------------------------------------------------------------------------
package AspectAfterThrowing;
//----------------------------------------------------------------------------------------------------------------------
import org.springframework.stereotype.Component;
//----------------------------------------------------------------------------------------------------------------------
// !!! CLASS reprezentuje SPRING BEAN na ktory su aplikovane ASPECTS.
@Component
public class CAspectAfterThrowingBean
{
//----------------------------------------------------------------------------------------------------------------------
	// !!!!! Aplikuje sa CUSTOM ANNOTATION, aby sa na METHOD aplikoval ASPECT 'CAspectAfterThrowingAspect'.
	@IAspectAfterThrowingAnnotation
	public String PrintMessage(String Message, boolean ThrowException) throws Throwable
	{
		System.out.format("CAspectAfterThrowingBean - MESSAGE [%s].\n",Message);
		
		if (ThrowException==true)
		{
			throw(new Throwable("My EXCEPTION."));		
		}
		else
		{
			return("My RETURN VALUE.");	
		}
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------