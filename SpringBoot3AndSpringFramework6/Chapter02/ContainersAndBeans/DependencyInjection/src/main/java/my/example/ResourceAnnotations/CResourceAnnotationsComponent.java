package my.example.ResourceAnnotations;
//----------------------------------------------------------------------------------------------------------------------
import org.springframework.stereotype.Component;

import jakarta.annotation.Resource;
//----------------------------------------------------------------------------------------------------------------------
@Component
public class CResourceAnnotationsComponent
{
//----------------------------------------------------------------------------------------------------------------------
	// !!! Aplikuje sa FIELD DEPENDENCY na zaklade ANNOTATION [@Resource].
	@Resource(name="MyComponent1")
	private Object												bean1;
	// !!! Aplikuje sa FIELD DEPENDENCY na zaklade ANNOTATION [@Resource].
	@Resource(name="MyComponent2")
	private Object												bean2;
	private Object												bean3;
	private Object												bean4;
	// !!! Aplikuje sa FIELD DEPENDENCY na zaklade ANNOTATION [@Resource]. Kedze ANNOTATION NEMA nastaveny ELEMENT [name] ako BEAN NAME sa pouzije nazov FIELD.
	@Resource
	private Object												MyComponent1;
	private Object												MyComponent2;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	// !!! Aplikuje sa SETTER DEPENDENCY na zaklade ANNOTATION [@Resource].
	@Resource(name="MyComponent1")
	public void setBean3(Object bean)
	{
		bean3=bean;
	}
//----------------------------------------------------------------------------------------------------------------------
	// !!! Aplikuje sa SETTER DEPENDENCY na zaklade ANNOTATION [@Resource].
	@Resource(name="MyComponent2")
	public void setBean4(Object bean)
	{
		bean4=bean;
	}
//----------------------------------------------------------------------------------------------------------------------
	// !!! Aplikuje sa FIELD DEPENDENCY na zaklade ANNOTATION [@Resource]. Kedze ANNOTATION NEMA nastaveny ELEMENT [name] ako BEAN NAME sa pouzije nazov SETTER.
	@Resource
	public void setMyComponent2(Object MyComponent2)
	{
		this.MyComponent2=MyComponent2;
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	public void Test()
	{
		String													myBeanText1=((CResourceAnnotationsBean1)bean1).GetText();
		String													myBeanText2=((CResourceAnnotationsBean2)bean2).GetText();
		String													myBeanText3=((CResourceAnnotationsBean1)bean3).GetText();
		String													myBeanText4=((CResourceAnnotationsBean2)bean4).GetText();
		String													myBeanText5=((CResourceAnnotationsBean1)MyComponent1).GetText();
		String													myBeanText6=((CResourceAnnotationsBean2)MyComponent2).GetText();
		
		System.out.printf("BEAN 1 [%s].\n",myBeanText1);
		System.out.printf("BEAN 2 [%s].\n",myBeanText2);
		System.out.printf("BEAN 3 [%s].\n",myBeanText3);
		System.out.printf("BEAN 4 [%s].\n",myBeanText4);
		System.out.printf("BEAN 5 [%s].\n",myBeanText5);
		System.out.printf("BEAN 6 [%s].\n",myBeanText6);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------