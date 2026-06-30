package my.example.InjectionTypes;
//----------------------------------------------------------------------------------------------------------------------
import org.springframework.beans.factory.annotation.Autowired;

import org.springframework.stereotype.Component;
//----------------------------------------------------------------------------------------------------------------------
@Component
public class CInjectionTypesMultipleDependencies
{
//----------------------------------------------------------------------------------------------------------------------
	private final CInjectionTypesBean1							beanConstructor1;
	private final CInjectionTypesBean2							beanConstructor2;
//----------------------------------------------------------------------------------------------------------------------
	private CInjectionTypesBean1								beanSetter1;
	private CInjectionTypesBean2								beanSetter2;
//----------------------------------------------------------------------------------------------------------------------
	// !!! Pri AUTOWIRING VISIBILITY daneho MEMBER NIE je DOLEZITA, kedze DEPENDENCY INJECTION sa robi pomocou REFLECTION.
	@Autowired
	private CInjectionTypesBean1								beanField1;
	// !!! Pri AUTOWIRING VISIBILITY daneho MEMBER NIE je DOLEZITA, kedze DEPENDENCY INJECTION sa robi pomocou REFLECTION.
	@Autowired
	private CInjectionTypesBean2								beanField2;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	// !!! Pri AUTOWIRING VISIBILITY daneho MEMBER NIE je DOLEZITA, kedze DEPENDENCY INJECTION sa robi pomocou REFLECTION.
	@Autowired
	private CInjectionTypesMultipleDependencies(CInjectionTypesBean1 beanConstructor1, CInjectionTypesBean2 beanConstructor2)
	{
		this.beanConstructor1=beanConstructor1;
		this.beanConstructor2=beanConstructor2;
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	// !!! Pri AUTOWIRING VISIBILITY daneho MEMBER NIE je DOLEZITA, kedze DEPENDENCY INJECTION sa robi pomocou REFLECTION.
	// !!!!! SETTER moze mat aj VIACERO PARAMETERS, ktore reprezentuju jednotlive BEANS.
	@Autowired
	private void MySetter(CInjectionTypesBean1 bean1, CInjectionTypesBean2 bean2)
	{
		this.beanSetter1=bean1;
		this.beanSetter2=bean2;
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	public void Test()
	{
		String													TextConstructor1=beanConstructor1.Print();
		String													TextConstructor2=beanConstructor2.Print();
		String													TextSetter1=beanSetter1.Print();
		String													TextSetter2=beanSetter2.Print();
		String													TextField1=beanField1.Print();
		String													TextField2=beanField2.Print();
		
		System.out.printf("CONSTRUCTOR INJECTION - BEAN 1 [%s].\n",TextConstructor1);
		System.out.printf("CONSTRUCTOR INJECTION - BEAN 2 [%s].\n",TextConstructor2);
		System.out.printf("SETTER INJECTION - BEAN 1 [%s].\n",TextSetter1);
		System.out.printf("SETTER INJECTION - BEAN 2 [%s].\n",TextSetter2);
		System.out.printf("FIELD INJECTION - BEAN 1 [%s].\n",TextField1);
		System.out.printf("FIELD INJECTION - BEAN 2 [%s].\n",TextField2);
	}	
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------