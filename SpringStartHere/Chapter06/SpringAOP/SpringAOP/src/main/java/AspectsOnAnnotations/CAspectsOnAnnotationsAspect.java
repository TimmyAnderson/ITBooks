//----------------------------------------------------------------------------------------------------------------------
package AspectsOnAnnotations;
//----------------------------------------------------------------------------------------------------------------------
import org.aspectj.lang.annotation.Around;
import org.aspectj.lang.annotation.Aspect;
import org.aspectj.lang.ProceedingJoinPoint;
import org.springframework.stereotype.Component;
//----------------------------------------------------------------------------------------------------------------------
@Component
@Aspect
public class CAspectsOnAnnotationsAspect
{
//----------------------------------------------------------------------------------------------------------------------
	// !!! METHOD reprezentuje ASPECT. Obsahuje CODE ASPECT. METHOD MUSI byt oznacena pomocou ANNOTATION [@Around].
	// !!!!! ASPECTJ CODE oznacuje, aby sa ASPECT aplikovat na METHODS, ktore su oznacene CUSTOM ANNOTATION 'IAspectsOnAnnotationsAnnotation'.
	@Around("@annotation(IAspectsOnAnnotationsAnnotation)") 
	public Object DoLog(ProceedingJoinPoint JoinPoint) throws Throwable
	{
		System.out.println("ASPECT [CAspectsOnAnnotationsAspect] BEFORE METHOD CALL.");
		
		// !!!!! Zavola sa POVODNA METHOD TARGET OBJECT.
		Object													ReturnValue=JoinPoint.proceed();
	
		System.out.println("ASPECT [CAspectsOnAnnotationsAspect] AFTER METHOD CALL.");
		
		return(ReturnValue);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------