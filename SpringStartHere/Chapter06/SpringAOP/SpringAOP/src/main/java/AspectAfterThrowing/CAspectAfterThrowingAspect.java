//----------------------------------------------------------------------------------------------------------------------
package AspectAfterThrowing;
//----------------------------------------------------------------------------------------------------------------------
import org.aspectj.lang.annotation.AfterThrowing;
import org.aspectj.lang.annotation.Aspect;
import org.springframework.stereotype.Component;
//----------------------------------------------------------------------------------------------------------------------
@Component
@Aspect
public class CAspectAfterThrowingAspect
{
//----------------------------------------------------------------------------------------------------------------------
	// !!! METHOD reprezentuje ASPECT. Obsahuje CODE ASPECT. METHOD MUSI byt oznacena pomocou ANNOTATION [@AfterThrowing].
	// !!!!! ASPECT je volany ak TARGET METHOD hodi EXCEPTION.
	// !!!!! ASPECTJ CODE oznacuje, aby sa ASPECT aplikovat na METHODS, ktore su oznacene CUSTOM ANNOTATION 'IAspectAfterThrowingAnnotation'.
	@AfterThrowing(pointcut="@annotation(IAspectAfterThrowingAnnotation)",throwing="E") 
	public void DoLog(Throwable E) throws Throwable
	{
		System.out.format("ASPECT [CAspectAfterThrowingAspect] CALLED. EXCEPTION [%s].\n",E.getMessage());
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------