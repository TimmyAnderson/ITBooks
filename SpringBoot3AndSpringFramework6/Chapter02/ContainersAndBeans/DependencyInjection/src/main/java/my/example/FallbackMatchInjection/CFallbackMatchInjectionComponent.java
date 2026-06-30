package my.example.FallbackMatchInjection;
//----------------------------------------------------------------------------------------------------------------------
import org.springframework.beans.factory.annotation.Autowired;

import org.springframework.stereotype.Component;
//----------------------------------------------------------------------------------------------------------------------
@Component
public class CFallbackMatchInjectionComponent
{
//----------------------------------------------------------------------------------------------------------------------
	// !!!! DEPENDENCY INJECTION je RESOLVED na zaklade BEAN NAME. BEAN [CFallbackMatchInjectionBean1] je COMPONENT a jeho ma NAME [CFallbackMatchInjectionBean1]. Ak FIELD, alebo PARAMETER ma rovnaky NAME ako BEAN NAME, SPRING FRAMEWORK dokaze na zaklade tohto NAME spravit SUBSTITUTION.
	private final IFallbackMatchInjectionInterface				CFallbackMatchInjectionBean1;
	// !!!! DEPENDENCY INJECTION je RESOLVED na zaklade BEAN NAME. BEAN [CFallbackMatchInjectionBean2] je COMPONENT a jeho ma NAME [CFallbackMatchInjectionBean2]. Ak FIELD, alebo PARAMETER ma rovnaky NAME ako BEAN NAME, SPRING FRAMEWORK dokaze na zaklade tohto NAME spravit SUBSTITUTION.
	private final IFallbackMatchInjectionInterface				CFallbackMatchInjectionBean2;
	// !!!! DEPENDENCY INJECTION je RESOLVED na zaklade BEAN NAME. BEAN [CFallbackMatchInjectionBean3] je vytvoreny pomocou FACTORY METHOD [MyBean3()] teda BEAN ma NAME [MyBean3]. Ak FIELD, alebo PARAMETER ma rovnaky NAME ako BEAN NAME, SPRING FRAMEWORK dokaze na zaklade tohto NAME spravit SUBSTITUTION.
	private final IFallbackMatchInjectionInterface				MyBean3;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	@Autowired
	// !!!! DEPENDENCY INJECTION je RESOLVED na zaklade BEAN NAME. BEAN [CFallbackMatchInjectionBean1] je COMPONENT a jeho ma NAME [CFallbackMatchInjectionBean1]. Ak FIELD, alebo PARAMETER ma rovnaky NAME ako BEAN NAME, SPRING FRAMEWORK dokaze na zaklade tohto NAME spravit SUBSTITUTION.
	// !!!! DEPENDENCY INJECTION je RESOLVED na zaklade BEAN NAME. BEAN [CFallbackMatchInjectionBean2] je COMPONENT a jeho ma NAME [CFallbackMatchInjectionBean2]. Ak FIELD, alebo PARAMETER ma rovnaky NAME ako BEAN NAME, SPRING FRAMEWORK dokaze na zaklade tohto NAME spravit SUBSTITUTION.
	// !!!! DEPENDENCY INJECTION je RESOLVED na zaklade BEAN NAME. BEAN [CFallbackMatchInjectionBean3] je vytvoreny pomocou FACTORY METHOD [MyBean3()] teda BEAN ma NAME [MyBean3]. Ak FIELD, alebo PARAMETER ma rovnaky NAME ako BEAN NAME, SPRING FRAMEWORK dokaze na zaklade tohto NAME spravit SUBSTITUTION.
	public CFallbackMatchInjectionComponent(IFallbackMatchInjectionInterface CFallbackMatchInjectionBean1, IFallbackMatchInjectionInterface CFallbackMatchInjectionBean2, IFallbackMatchInjectionInterface MyBean3)
	{
		this.CFallbackMatchInjectionBean1=CFallbackMatchInjectionBean1;
		this.CFallbackMatchInjectionBean2=CFallbackMatchInjectionBean2;
		this.MyBean3=MyBean3;
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	public void Test()
	{
		String													myBeanText1=CFallbackMatchInjectionBean1.GetText();
		String													myBeanText2=CFallbackMatchInjectionBean2.GetText();
		String													myBeanText3=MyBean3.GetText();
		
		System.out.printf("BEAN 1 [%s].\n",myBeanText1);
		System.out.printf("BEAN 2 [%s].\n",myBeanText2);
		System.out.printf("BEAN 3 [%s].\n",myBeanText3);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------