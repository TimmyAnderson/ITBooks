//----------------------------------------------------------------------------------------------------------------------
package AspectBefore;
//----------------------------------------------------------------------------------------------------------------------
import org.aspectj.lang.annotation.Before;
import org.aspectj.lang.annotation.Aspect;
import org.aspectj.lang.JoinPoint;
import org.springframework.stereotype.Component;
//----------------------------------------------------------------------------------------------------------------------
@Component
@Aspect
public class CAspectBeforeAspect
{
//----------------------------------------------------------------------------------------------------------------------
	// !!! METHOD reprezentuje ASPECT. Obsahuje CODE ASPECT. METHOD MUSI byt oznacena pomocou ANNOTATION [@Before].
	// !!!!! ASPECT je volany pred vykonanim TARGET METHOD.
	// !!!!! ASPECTJ CODE oznacuje, aby sa ASPECT aplikovat na METHODS, ktore su oznacene CUSTOM ANNOTATION 'IAspectBeforeAnnotation'.
	@Before("@annotation(IAspectBeforeAnnotation)") 
	public void DoLog(JoinPoint JoinPoint) throws Throwable
	{
		System.out.format("ASPECT [CAspectBeforeAspect] CALLED. TARGET CLASS [%s]. TARGET METHOD [%s].\n",JoinPoint.getTarget().getClass().getName(),JoinPoint.getSignature().getName());
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------