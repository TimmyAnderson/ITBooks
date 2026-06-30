package my.example.ConditionalOnPropertyBeans;
//----------------------------------------------------------------------------------------------------------------------
import org.springframework.beans.factory.annotation.Autowired;

import org.springframework.stereotype.Component;
//----------------------------------------------------------------------------------------------------------------------
@Component
public class CConditionalOnPropertyBeansComponent
{
//----------------------------------------------------------------------------------------------------------------------
	private final CConditionalOnPropertyBeansBean1				bean1;
	private final CConditionalOnPropertyBeansBean2				bean2;
	private final CConditionalOnPropertyBeansBean3				bean3;
	private final CConditionalOnPropertyBeansBean4				bean4;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	public CConditionalOnPropertyBeansComponent(@Autowired(required=false) CConditionalOnPropertyBeansBean1 bean1, @Autowired(required=false) CConditionalOnPropertyBeansBean2 bean2, @Autowired(required=false) CConditionalOnPropertyBeansBean3 bean3, @Autowired(required=false) CConditionalOnPropertyBeansBean4 bean4)
	{
		this.bean1=bean1;
		this.bean2=bean2;
		this.bean3=bean3;
		this.bean4=bean4;
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	public void Test()
	{
		String													beanText1=(bean1!=null) ? bean1.GetText() : "";
		String													beanText2=(bean2!=null) ? bean2.GetText() : "";
		String													beanText3=(bean3!=null) ? bean3.GetText() : "";
		String													beanText4=(bean4!=null) ? bean4.GetText() : "";
		
		System.out.printf("BEAN 1 - VALUE [%s].\n",beanText1);
		System.out.printf("BEAN 2 - VALUE [%s].\n",beanText2);
		System.out.printf("BEAN 3 - VALUE [%s].\n",beanText3);
		System.out.printf("BEAN 4 - VALUE [%s].\n",beanText4);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------