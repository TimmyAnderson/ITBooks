package my.example.BeansFactoryMethods;
//----------------------------------------------------------------------------------------------------------------------
import java.util.Optional;
//----------------------------------------------------------------------------------------------------------------------
// !!! CLASS NEMUSI byt oznacena pomocou ANNOTATION [@Component].
public class CBeansFactoryMethodsBeanWithDependencies
{
//----------------------------------------------------------------------------------------------------------------------
	private final CBeansFactoryMethodsBean1						bean1;
	private final CBeansFactoryMethodsBean2						bean2;
	// !!!!! CLASS [CBeansFactoryMethodsNotBean] NIE je BEAN a je prenasana ako OPTIONAL BEAN.
	private final Optional<CBeansFactoryMethodsNotBean>			notBean;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	public CBeansFactoryMethodsBeanWithDependencies(CBeansFactoryMethodsBean1 bean1, CBeansFactoryMethodsBean2 bean2, Optional<CBeansFactoryMethodsNotBean> notBean)
	{
		this.bean1=bean1;
		this.bean2=bean2;
		this.notBean=notBean;
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	public void Print()
	{
		String													bean1Text=bean1.GetMessage();
		String													bean2Text=bean2.GetMessage();
		String													notBeanText=(notBean.isPresent()==true) ? notBean.get().GetMessage() : "NONE";
		
		System.out.printf("This is BEAN WITH DEPENDENCIES.\n");
		System.out.printf("BEAN WITH DEPENDENCIES - FROM BEAN 1 [%s].\n",bean1Text);
		System.out.printf("BEAN WITH DEPENDENCIES - FROM BEAN 2 [%s].\n",bean2Text);
		System.out.printf("BEAN WITH DEPENDENCIES - FROM NOT BEAN [%s].\n",notBeanText);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------