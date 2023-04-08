//----------------------------------------------------------------------------------------------------------------------
package AspectsOrder;
//----------------------------------------------------------------------------------------------------------------------
import org.aspectj.lang.annotation.Around;
import org.aspectj.lang.annotation.Aspect;
import org.aspectj.lang.ProceedingJoinPoint;
import org.springframework.core.annotation.Order;
import org.springframework.stereotype.Component;
//----------------------------------------------------------------------------------------------------------------------
@Component
@Aspect
// !!!!! ANNOTATION [@Order] urcuje poradie v akom sa ASPECT vola voci inym ASPECTS.
@Order(2)
public class CAspectsOrderAspect2
{
//----------------------------------------------------------------------------------------------------------------------
	// !!! METHOD reprezentuje ASPECT. Obsahuje CODE ASPECT. METHOD MUSI byt oznacena pomocou ANNOTATION [@Around].
	// !!!!! ASPECTJ CODE oznacuje, aby sa ASPECT aplikovat na METHODS, ktore su oznacene CUSTOM ANNOTATION 'IAspectsOrderAnnotation'.
	@Around("@annotation(IAspectsOrderAnnotation)") 
	public Object DoLog(ProceedingJoinPoint JoinPoint) throws Throwable
	{
		System.out.println("ASPECT [CAspectsOrderAspect2] BEFORE METHOD CALL.");
		
		// !!!!! Zavola sa POVODNA METHOD TARGET OBJECT.
		Object													ReturnValue=JoinPoint.proceed();
	
		System.out.println("ASPECT [CAspectsOrderAspect2] AFTER METHOD CALL.");
		
		return(ReturnValue);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------