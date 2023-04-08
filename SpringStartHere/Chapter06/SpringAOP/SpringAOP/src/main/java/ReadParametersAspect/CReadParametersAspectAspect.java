//----------------------------------------------------------------------------------------------------------------------
package ReadParametersAspect;
//----------------------------------------------------------------------------------------------------------------------
import org.aspectj.lang.annotation.Around;
import org.aspectj.lang.annotation.Aspect;
import org.aspectj.lang.ProceedingJoinPoint;
import org.springframework.stereotype.Component;
//----------------------------------------------------------------------------------------------------------------------
// !!! CLASS obsahuje ASPECTS, a preto musi byt oznacena ANNOTATION [@Aspect].
// !!! ASPECT MUSI byt zaroven aj SPRING BEAN.
@Component
@Aspect
public class CReadParametersAspectAspect
{
//----------------------------------------------------------------------------------------------------------------------
	// !!! METHOD reprezentuje ASPECT. Obsahuje CODE ASPECT. METHOD MUSI byt oznacena pomocou ANNOTATION [@Around].
	@Around("execution(* ReadParametersAspect.CReadParametersAspectBean.*(..))") 
	public Object DoLog(ProceedingJoinPoint JoinPoint) throws Throwable
	{
		System.out.println("ASPECT [CReadParametersAspectAspect] BEFORE METHOD CALL.");

		// !!! Vracia SIGNATURE povodnej TARGET OBJECT METHOD.
		System.out.format("ASPECT [CReadParametersAspectAspect] TARGET OBJECT METHOD [%s].\n",JoinPoint.getSignature().getName());

		// !!! Vracia PARAMETERS povodnej TARGET OBJECT METHOD.
		Object[]												OriginalParametersObjects=JoinPoint.getArgs();

		System.out.format("ASPECT [CReadParametersAspectAspect] ORIGINAL PARAMETERS [%s].\n",OriginalParametersObjects);
		
		// !!!!! Zavola sa POVODNA TARGET OBJECT METHOD.
		// !!!!! METHOD [Object ProceedingJoinPoint.proceed() throws Throwable] vola TARGET OBJECT METHOD s POVODNYMI PARAMETERS. 
		// !!!!! RETURN VALUE METHOD je RETURN VALUE METHOD TARGET OBJECT.  
		Object													OriginalReturnValue=JoinPoint.proceed();
	
		// !!! Vracia RETURN VALUE povodnej TARGET OBJECT METHOD.
		System.out.format("ASPECT [CReadParametersAspectAspect] ORIGINAL RETURN VALUE [%s].\n",OriginalReturnValue);
	
		System.out.println("ASPECT [CReadParametersAspectAspect] AFTER METHOD CALL.");
		
		return(OriginalReturnValue);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------