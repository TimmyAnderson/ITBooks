//----------------------------------------------------------------------------------------------------------------------
package WriteParametersAspect;
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
public class CWriteParametersAspectAspect
{
//----------------------------------------------------------------------------------------------------------------------
	// !!! METHOD reprezentuje ASPECT. Obsahuje CODE ASPECT. METHOD MUSI byt oznacena pomocou ANNOTATION [@Around].
	@Around("execution(* WriteParametersAspect.CWriteParametersAspectBean.*(..))") 
	public Object DoLog(ProceedingJoinPoint JoinPoint) throws Throwable
	{
		System.out.println("ASPECT [CWriteParametersAspectAspect] BEFORE METHOD CALL.");

		// !!! Vracia SIGNATURE povodnej TARGET OBJECT METHOD.
		System.out.format("ASPECT [CWriteParametersAspectAspect] TARGET OBJECT METHOD [%s].\n",JoinPoint.getSignature().getName());

		// !!! Vracia PARAMETERS povodnej TARGET OBJECT METHOD.
		Object[]												OriginalParametersObjects=JoinPoint.getArgs();

		System.out.format("ASPECT [CWriteParametersAspectAspect] ORIGINAL PARAMETERS [%s].\n",OriginalParametersObjects);

		String													NewText1="";
		String													NewText2="";

		if (OriginalParametersObjects.length>0)
		{
			Object												OriginalParameter=OriginalParametersObjects[0];
			
			if ((OriginalParameter instanceof CWriteParametersAspectMessage)==true)
			{
				CWriteParametersAspectMessage					TypedOriginalParameter=(CWriteParametersAspectMessage) OriginalParameter;

				NewText1=String.format("MODIFIED [+++%s+++].",TypedOriginalParameter.getText1());
				NewText2=String.format("MODIFIED [---%s---].",TypedOriginalParameter.getText2());
			} 
		}
	
		// !!!!! Vytvoria sa NOVE PARAMETERS, ktore sa zaslu do TARGET OBJECT METHOD.
		CWriteParametersAspectMessage							Message=new CWriteParametersAspectMessage(NewText1,NewText2);  
		Object[]												NewParametersObjects={Message};	
		
		// !!!!! Zavola sa POVODNA TARGET OBJECT METHOD.
		// !!!!! METHOD [Object ProceedingJoinPoint.proceed(Object[] args) throws Throwable] vola TARGET OBJECT METHOD s NOVYMI PARAMETERS. 
		// !!!!! RETURN VALUE METHOD je RETURN VALUE METHOD TARGET OBJECT.  
		Object													OriginalReturnValue=JoinPoint.proceed(NewParametersObjects);
	
		// !!! Vracia RETURN VALUE povodnej TARGET OBJECT METHOD.
		System.out.format("ASPECT [CWriteParametersAspectAspect] ORIGINAL RETURN VALUE [%s].\n",OriginalReturnValue);
	
		Object													ModifiedReturnValue=String.format("MODIFIED [+++%s+++].",OriginalReturnValue);
	
		System.out.println("ASPECT [CWriteParametersAspectAspect] AFTER METHOD CALL.");
		
		// !!! Vrati sa MODIFIKOVANA RETURN VALUE.
		return(ModifiedReturnValue);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------