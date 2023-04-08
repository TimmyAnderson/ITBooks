//----------------------------------------------------------------------------------------------------------------------
package AspectAfterReturning;
//----------------------------------------------------------------------------------------------------------------------
import org.aspectj.lang.annotation.AfterReturning;
import org.aspectj.lang.annotation.Aspect;
import org.springframework.stereotype.Component;
//----------------------------------------------------------------------------------------------------------------------
@Component
@Aspect
public class CAspectAfterReturningAspect
{
//----------------------------------------------------------------------------------------------------------------------
	// !!! METHOD reprezentuje ASPECT. Obsahuje CODE ASPECT. METHOD MUSI byt oznacena pomocou ANNOTATION [@AfterReturning].
	// !!!!! ASPECT je volany ak TARGET METHOD vrati RETURN VALUE a nehodi EXCEPTION.
	// !!!!! ASPECTJ CODE oznacuje, aby sa ASPECT aplikovat na METHODS, ktore su oznacene CUSTOM ANNOTATION 'IAspectAfterReturningAnnotation'.
	@AfterReturning(pointcut="@annotation(IAspectAfterReturningAnnotation)",returning="ReturnValue") 
	public void DoLog(Object ReturnValue) throws Throwable
	{
		System.out.format("ASPECT [CAspectAfterReturningAspect] CALLED. RETURN VALUE [%s].\n",ReturnValue);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------