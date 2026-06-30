package my.example.LifecycleEventsInterfaces;
//----------------------------------------------------------------------------------------------------------------------
import org.springframework.beans.factory.annotation.Autowired;

import org.springframework.stereotype.Component;
//----------------------------------------------------------------------------------------------------------------------
@Component
public class CLifecycleEventsInterfacesComponent
{
//----------------------------------------------------------------------------------------------------------------------
	private final CLifecycleEventsInterfacesBean1				bean1;
	private final CLifecycleEventsInterfacesBean2				bean2;
	private final CLifecycleEventsInterfacesBean3				bean3;
	private final CLifecycleEventsInterfacesAwareBean			beanAware;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	@Autowired
	public CLifecycleEventsInterfacesComponent(CLifecycleEventsInterfacesBean1 bean1, CLifecycleEventsInterfacesBean2 bean2, CLifecycleEventsInterfacesBean3 bean3, CLifecycleEventsInterfacesAwareBean beanAware)
	{
		this.bean1=bean1;
		this.bean2=bean2;
		this.bean3=bean3;
		this.beanAware=beanAware;
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	public void Test()
	{
		String													beanText1=bean1.GetText();
		String													beanText2=bean2.GetText();
		String													beanText3=bean3.GetText();
		String													beanAwareText=beanAware.GetText();
		
		System.out.printf("BEAN 1 - VALUE [%s].\n",beanText1);
		System.out.printf("BEAN 2 - VALUE [%s].\n",beanText2);
		System.out.printf("BEAN 3 - VALUE [%s].\n",beanText3);
		System.out.printf("BEAN AWARE - VALUE [%s].\n",beanAwareText);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------