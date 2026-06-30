package my.example.GenericTypesBeans;
//----------------------------------------------------------------------------------------------------------------------
import org.springframework.beans.factory.annotation.Autowired;

import org.springframework.stereotype.Component;
//----------------------------------------------------------------------------------------------------------------------
@Component
public class CGenericTypesBeansTestBean
{
//----------------------------------------------------------------------------------------------------------------------
	private final CGenericTypesBeansBean<String>				stringBean;
	private final CGenericTypesBeansBean<Integer>				integerBean;
	// !!!!! SPRING FRAMEWORK NESPRAVIL korektnu substituciu GENERIC PARAMETER. Aj tento BEAN obsahuje ako PARAMETER TYPE [Boolean], pretoze TYPE [Boolean] bol oznaceny ako PRIMARY TYPE.
	// !!!!! SPRING FRAMEWORK pre COMPONENTS, ktore NIE su vytvarane pomocou FACTORY METHODS NEDOKAZE spravne substituovat GENERIC PARAMETERS.
	private final CGenericTypesBeansComponent1<Boolean>			booleanBean1;
	private final CGenericTypesBeansComponent1<Double>			doubleBean1;
	private final CGenericTypesBeansComponent2<Boolean>			booleanBean2;
	private final CGenericTypesBeansComponent2<Double>			doubleBean2;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	@Autowired
	public CGenericTypesBeansTestBean(CGenericTypesBeansBean<String> stringBean, CGenericTypesBeansBean<Integer> integerBean, CGenericTypesBeansComponent1<Boolean> booleanBean1, CGenericTypesBeansComponent1<Double> doubleBean1, CGenericTypesBeansComponent2<Boolean> booleanBean2, CGenericTypesBeansComponent2<Double> doubleBean2)
	{
		this.stringBean=stringBean;
		this.integerBean=integerBean;
		this.booleanBean1=booleanBean1;
		this.doubleBean1=doubleBean1;
		this.booleanBean2=booleanBean2;
		this.doubleBean2=doubleBean2;
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	public void Test()
	{
		booleanBean2.setValue(false);
		doubleBean2.setValue(123.456);
		
		String													text1=stringBean.PrintValue();
		String													text2=integerBean.PrintValue();
		String													text3=booleanBean1.Print();
		String													text4=doubleBean1.Print();
		String													text5=booleanBean2.Print();
		String													text6=doubleBean2.Print();
	
		System.out.printf("GENERIC BEAN - STRING BEAN [%s].\n",text1);
		System.out.printf("GENERIC BEAN - INTEGER BEAN [%s].\n",text2);
		System.out.printf("GENERIC COMPONENT 1 - BOOLEAN BEAN [%s].\n",text3);
		System.out.printf("GENERIC COMPONENT 1 - DOUBLE BEAN [%s].\n",text4);
		System.out.printf("GENERIC COMPONENT 2 - BOOLEAN BEAN [%s].\n",text5);
		System.out.printf("GENERIC COMPONENT 2 - DOUBLE BEAN [%s].\n",text6);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------