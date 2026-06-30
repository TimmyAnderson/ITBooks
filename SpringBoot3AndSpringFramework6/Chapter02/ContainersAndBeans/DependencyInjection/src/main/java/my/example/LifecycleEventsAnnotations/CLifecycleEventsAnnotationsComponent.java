package my.example.LifecycleEventsAnnotations;
//----------------------------------------------------------------------------------------------------------------------
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Component;
//----------------------------------------------------------------------------------------------------------------------
@Component
public class CLifecycleEventsAnnotationsComponent
{
//----------------------------------------------------------------------------------------------------------------------
	private final CLifecycleEventsAnnotationsBean1				bean1;
	private final CLifecycleEventsAnnotationsBean2				bean2;
	private final CLifecycleEventsAnnotationsBean3				bean3;
	private final CLifecycleEventsAnnotationsBean4				bean4;
	private final CLifecycleEventsAnnotationsBean5				bean5;
	private final CLifecycleEventsAnnotationsBean6				bean6;
	private final CLifecycleEventsAnnotationsDerivedClassBean1	derivedClassBean1;
	private final CLifecycleEventsAnnotationsDerivedClassBean2	derivedClassBean2;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	@Autowired
	public CLifecycleEventsAnnotationsComponent(CLifecycleEventsAnnotationsBean1 bean1, CLifecycleEventsAnnotationsBean2 bean2, CLifecycleEventsAnnotationsBean3 bean3, CLifecycleEventsAnnotationsBean4 bean4, CLifecycleEventsAnnotationsBean5 bean5, CLifecycleEventsAnnotationsBean6 bean6, CLifecycleEventsAnnotationsDerivedClassBean1 derivedClassBean1, CLifecycleEventsAnnotationsDerivedClassBean2 derivedClassBean2)
	{
		this.bean1=bean1;
		this.bean2=bean2;
		this.bean3=bean3;
		this.bean4=bean4;
		this.bean5=bean5;
		this.bean6=bean6;
		this.derivedClassBean1=derivedClassBean1;
		this.derivedClassBean2=derivedClassBean2;
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
		String													beanText6=bean6.GetText();
		String													derivedClassBeanText1=derivedClassBean1.GetText();
		String													derivedClassBeanText2=derivedClassBean2.GetText();
		
		System.out.printf("BEAN 1 - VALUE [%s].\n",beanText1);
		System.out.printf("BEAN 2 - VALUE [%s].\n",beanText2);
		System.out.printf("BEAN 3 - VALUE [%s].\n",beanText3);
		System.out.printf("BEAN 4 - VALUE [%s].\n",beanText4);
		System.out.printf("BEAN 5 - VALUE [%s].\n",beanText5);
		System.out.printf("BEAN 6 - VALUE [%s].\n",beanText6);
		System.out.printf("DERIVED CLASS BEAN 1 - VALUE [%s].\n",derivedClassBeanText1);
		System.out.printf("DERIVED CLASS BEAN 2 - VALUE [%s].\n",derivedClassBeanText2);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------