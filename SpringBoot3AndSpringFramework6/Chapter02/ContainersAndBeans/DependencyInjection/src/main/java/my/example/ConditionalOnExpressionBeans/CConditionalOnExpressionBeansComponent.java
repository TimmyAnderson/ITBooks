package my.example.ConditionalOnExpressionBeans;
//----------------------------------------------------------------------------------------------------------------------
import org.springframework.beans.factory.annotation.Autowired;

import org.springframework.stereotype.Component;
//----------------------------------------------------------------------------------------------------------------------
@Component
public class CConditionalOnExpressionBeansComponent
{
//----------------------------------------------------------------------------------------------------------------------
	private final CConditionalOnExpressionBeansBean1			bean1;
	private final CConditionalOnExpressionBeansBean2			bean2;
	private final CConditionalOnExpressionBeansBean3			bean3;
	private final CConditionalOnExpressionBeansBean4			bean4;
	private final CConditionalOnExpressionBeansBean5			bean5;
	private final CConditionalOnExpressionBeansBean6			bean6;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	public CConditionalOnExpressionBeansComponent(@Autowired(required=false) CConditionalOnExpressionBeansBean1 bean1, @Autowired(required=false) CConditionalOnExpressionBeansBean2 bean2, @Autowired(required=false) CConditionalOnExpressionBeansBean3 bean3, @Autowired(required=false) CConditionalOnExpressionBeansBean4 bean4, @Autowired(required=false) CConditionalOnExpressionBeansBean5 bean5, @Autowired(required=false) CConditionalOnExpressionBeansBean6 bean6)
	{
		this.bean1=bean1;
		this.bean2=bean2;
		this.bean3=bean3;
		this.bean4=bean4;
		this.bean5=bean5;
		this.bean6=bean6;
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
		String													beanText5=(bean5!=null) ? bean5.GetText() : "";
		String													beanText6=(bean6!=null) ? bean6.GetText() : "";
		
		System.out.printf("BEAN 1 - VALUE [%s].\n",beanText1);
		System.out.printf("BEAN 2 - VALUE [%s].\n",beanText2);
		System.out.printf("BEAN 3 - VALUE [%s].\n",beanText3);
		System.out.printf("BEAN 4 - VALUE [%s].\n",beanText4);
		System.out.printf("BEAN 5 - VALUE [%s].\n",beanText5);
		System.out.printf("BEAN 6 - VALUE [%s].\n",beanText6);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------