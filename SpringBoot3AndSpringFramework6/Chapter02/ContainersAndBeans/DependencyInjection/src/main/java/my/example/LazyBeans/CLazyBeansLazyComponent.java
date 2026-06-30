package my.example.LazyBeans;
//----------------------------------------------------------------------------------------------------------------------
import org.springframework.beans.factory.annotation.Autowired;

import org.springframework.context.annotation.Lazy;

import org.springframework.stereotype.Component;
//----------------------------------------------------------------------------------------------------------------------
@Lazy
@Component
public class CLazyBeansLazyComponent
{
//----------------------------------------------------------------------------------------------------------------------
	private final CLazyBeansBean1								bean1;
	private final CLazyBeansBean2								bean2;
	private final CLazyBeansBean3								bean3;
	private final CLazyBeansBean4								bean4;
	private final CLazyBeansBean5								bean5;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	@Autowired
	public CLazyBeansLazyComponent(CLazyBeansBean1 bean1, CLazyBeansBean2 bean2, CLazyBeansBean3 bean3, CLazyBeansBean4 bean4, CLazyBeansBean5 bean5)
	{
		this.bean1=bean1;
		this.bean2=bean2;
		this.bean3=bean3;
		this.bean4=bean4;
		this.bean5=bean5;
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	public void Test()
	{
		String													beanText1=bean1.GetText();
		String													beanText2=bean2.GetText();
		String													beanText3=bean3.GetText();
		String													beanText4=bean4.GetText();
		String													beanText5=bean5.GetText();
		
		System.out.printf("BEAN 1 - VALUE [%s].\n",beanText1);
		System.out.printf("BEAN 2 - VALUE [%s].\n",beanText2);
		System.out.printf("BEAN 3 - VALUE [%s].\n",beanText3);
		System.out.printf("BEAN 4 - VALUE [%s].\n",beanText4);
		System.out.printf("BEAN 5 - VALUE [%s].\n",beanText5);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------