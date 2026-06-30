package my.example.DependsOnBeans;
//----------------------------------------------------------------------------------------------------------------------
import org.springframework.stereotype.Component;
//----------------------------------------------------------------------------------------------------------------------
@Component
public class CDependsOnBeansComponent
{
//----------------------------------------------------------------------------------------------------------------------
	private final CDependsOnBeansBean1							bean1;
	private final CDependsOnBeansBean2							bean2;
	private final CDependsOnBeansBean3							bean3;
	private final CDependsOnBeansBean4							bean4;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	public CDependsOnBeansComponent(CDependsOnBeansBean1 bean1, CDependsOnBeansBean2 bean2, CDependsOnBeansBean3 bean3, CDependsOnBeansBean4 bean4)
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
		String													beanText1=bean1.GetText();
		String													beanText2=bean2.GetText();
		String													beanText3=bean3.GetText();
		String													beanText4=bean4.GetText();
		
		System.out.printf("BEAN 1 - VALUE [%s].\n",beanText1);
		System.out.printf("BEAN 2 - VALUE [%s].\n",beanText2);
		System.out.printf("BEAN 3 - VALUE [%s].\n",beanText3);
		System.out.printf("BEAN 4 - VALUE [%s].\n",beanText4);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------