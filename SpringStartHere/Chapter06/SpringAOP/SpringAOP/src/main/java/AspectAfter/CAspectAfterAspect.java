//----------------------------------------------------------------------------------------------------------------------
package AspectAfter;
//----------------------------------------------------------------------------------------------------------------------
import org.aspectj.lang.annotation.After;
import org.aspectj.lang.annotation.Aspect;
import org.aspectj.lang.JoinPoint;
import org.springframework.stereotype.Component;
//----------------------------------------------------------------------------------------------------------------------
@Component
@Aspect
public class CAspectAfterAspect
{
//----------------------------------------------------------------------------------------------------------------------
	// !!! METHOD reprezentuje ASPECT. Obsahuje CODE ASPECT. METHOD MUSI byt oznacena pomocou ANNOTATION [@After].
	// !!!!! ASPECT je volany pred vykonanim TARGET METHOD.
	// !!!!! ASPECTJ CODE oznacuje, aby sa ASPECT aplikovat na METHODS, ktore su oznacene CUSTOM ANNOTATION 'IAspectAfterAnnotation'.
	@After("@annotation(IAspectAfterAnnotation)") 
	public void DoLog(JoinPoint JoinPoint) throws Throwable
	{
		System.out.format("ASPECT [CAspectAfterAspect] CALLED. TARGET CLASS [%s]. TARGET METHOD [%s].\n",JoinPoint.getTarget().getClass().getName(),JoinPoint.getSignature().getName());
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------