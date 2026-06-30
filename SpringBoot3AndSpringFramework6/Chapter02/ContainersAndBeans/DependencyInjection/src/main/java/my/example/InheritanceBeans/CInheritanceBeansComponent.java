package my.example.InheritanceBeans;
//----------------------------------------------------------------------------------------------------------------------
import org.springframework.beans.factory.annotation.Autowired;

import org.springframework.stereotype.Component;
//----------------------------------------------------------------------------------------------------------------------
@Component
public class CInheritanceBeansComponent
{
//----------------------------------------------------------------------------------------------------------------------
	private final CInheritanceBeansBean1						bean1;
	private final CInheritanceBeansBean2						bean2;
	private final CInheritanceBeansBean3						bean3;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	@Autowired
	public CInheritanceBeansComponent(CInheritanceBeansBean1 bean1, CInheritanceBeansBean2 bean2, CInheritanceBeansBean3 bean3)
	{
		this.bean1=bean1;
		this.bean2=bean2;
		this.bean3=bean3;
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	public void Test()
	{
		String													beanText1=bean1.GetText();
		String													beanText2=bean2.GetText();
		String													beanText3=bean3.GetText();
		
		System.out.printf("BEAN 1 - VALUE [%s].\n",beanText1);
		System.out.printf("BEAN 2 - VALUE [%s].\n",beanText2);
		System.out.printf("BEAN 3 - VALUE [%s].\n",beanText3);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------