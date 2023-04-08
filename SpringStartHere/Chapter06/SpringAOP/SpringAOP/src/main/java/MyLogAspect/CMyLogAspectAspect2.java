//----------------------------------------------------------------------------------------------------------------------
package MyLogAspect;
//----------------------------------------------------------------------------------------------------------------------
import org.aspectj.lang.annotation.Around;
import org.aspectj.lang.annotation.Aspect;
import org.aspectj.lang.ProceedingJoinPoint;
//----------------------------------------------------------------------------------------------------------------------
// !!! CLASS obsahuje ASPECTS, a preto musi byt oznacena ANNOTATION [@Aspect].
// !!! ASPECT MUSI byt zaroven aj SPRING BEAN.
@Aspect
public class CMyLogAspectAspect2
{
//----------------------------------------------------------------------------------------------------------------------
	// !!! METHOD reprezentuje ASPECT. Obsahuje CODE ASPECT. METHOD MUSI byt oznacena pomocou ANNOTATION [@Around].
	@Around("execution(* MyLogAspect.CMyLogAspectBean.*(..))") 
	public void DoLog(ProceedingJoinPoint JoinPoint) throws Throwable
	{
		System.out.println("ASPECT [CMyLogAspectAspect2] BEFORE METHOD CALL.");
		
		// !!!!! Zavola sa POVODNA METHOD TARGET OBJECT.
		JoinPoint.proceed();
	
		System.out.println("ASPECT [CMyLogAspectAspect2] AFTER METHOD CALL.");
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------