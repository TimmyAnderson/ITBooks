package my.example.InjectionTypes;
//----------------------------------------------------------------------------------------------------------------------
import org.springframework.beans.factory.annotation.Autowired;

import org.springframework.stereotype.Component;
//----------------------------------------------------------------------------------------------------------------------
@Component
public class CInjectionTypesPrivateMembers
{
//----------------------------------------------------------------------------------------------------------------------
	private final CInjectionTypesBean							beanConstructor;
//----------------------------------------------------------------------------------------------------------------------
	private CInjectionTypesBean									beanSetter;
//----------------------------------------------------------------------------------------------------------------------
	// !!! Pri AUTOWIRING VISIBILITY daneho MEMBER NIE je DOLEZITA, kedze DEPENDENCY INJECTION sa robi pomocou REFLECTION.
	@Autowired
	private CInjectionTypesBean									beanField;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	// !!! Pri AUTOWIRING VISIBILITY daneho MEMBER NIE je DOLEZITA, kedze DEPENDENCY INJECTION sa robi pomocou REFLECTION.
	@Autowired
	private CInjectionTypesPrivateMembers(CInjectionTypesBean beanConstructor)
	{
		this.beanConstructor=beanConstructor;
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	// !!! Pri AUTOWIRING VISIBILITY daneho MEMBER NIE je DOLEZITA, kedze DEPENDENCY INJECTION sa robi pomocou REFLECTION.
	@Autowired
	private void MySetter(CInjectionTypesBean bean)
	{
		this.beanSetter=bean;
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	public void Test()
	{
		String													TextConstructor=beanConstructor.Print();
		String													TextSetter=beanSetter.Print();
		String													TextField=beanField.Print();
		
		System.out.printf("CONSTRUCTOR INJECTION - BEAN [%s].\n",TextConstructor);
		System.out.printf("SETTER INJECTION - BEAN [%s].\n",TextSetter);
		System.out.printf("FIELD INJECTION - BEAN [%s].\n",TextField);
	}	
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------