//----------------------------------------------------------------------------------------------------------------------
package AspectAfterReturning;
//----------------------------------------------------------------------------------------------------------------------
import org.springframework.stereotype.Component;
//----------------------------------------------------------------------------------------------------------------------
// !!! CLASS reprezentuje SPRING BEAN na ktory su aplikovane ASPECTS.
@Component
public class CAspectAfterReturningBean
{
//----------------------------------------------------------------------------------------------------------------------
	// !!!!! Aplikuje sa CUSTOM ANNOTATION, aby sa na METHOD aplikoval ASPECT 'CAspectAfterReturningAspect'.
	@IAspectAfterReturningAnnotation
	public String PrintMessage(String Message, boolean ThrowException) throws Throwable
	{
		System.out.format("CAspectAfterReturningBean - MESSAGE [%s].\n",Message);
		
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