//----------------------------------------------------------------------------------------------------------------------
package main;
//----------------------------------------------------------------------------------------------------------------------
import org.springframework.context.annotation.AnnotationConfigApplicationContext;
import Helpers.*;
import SingletonByBean.*;
import SingletonByStereotype.*;
import SingletonEagerVsLazy.*;
import PrototypeByBean.*;
import PrototypeByStereotype.*;
import PrototypeBeanInSingletonBean.*;
//----------------------------------------------------------------------------------------------------------------------
public class Main
{
//----------------------------------------------------------------------------------------------------------------------
	public static void TestSingletonByBean()
	{
		CHelpers.PrintLineSeparator();

		System.out.println("CONTEXT CREATING !");
		
		AnnotationConfigApplicationContext						Context=new AnnotationConfigApplicationContext(CSingletonByBeanConfguration.class);

		System.out.println("CONTEXT CREATED !");

		CSingletonByBeanBean									Bean11=Context.getBean("BEAN_1",CSingletonByBeanBean.class);
		CSingletonByBeanBean									Bean12=Context.getBean("BEAN_1",CSingletonByBeanBean.class);
		CSingletonByBeanBean									Bean21=Context.getBean("BEAN_2",CSingletonByBeanBean.class);
		CSingletonByBeanBean									Bean22=Context.getBean("BEAN_2",CSingletonByBeanBean.class);

		System.out.format("BEAN [Bean11] has VALUE [%s] !\n",Bean11.getValue());
		System.out.format("BEAN [Bean12] has VALUE [%s] !\n",Bean12.getValue());
		System.out.format("BEAN [Bean21] has VALUE [%s] !\n",Bean21.getValue());
		System.out.format("BEAN [Bean22] has VALUE [%s] !\n",Bean22.getValue());

		// Vrati TRUE.
		if (Bean11==Bean12)
		{
			System.out.format("BEAN [Bean11] and BEAN [Bean12] point to the SAME OBJECT !\n");
		}
		else
		{
			System.out.format("BEAN [Bean11] and BEAN [Bean12] point to DIFFERENT OBJECTS !\n");
		}

		// Vrati FALSE.
		if (Bean11==Bean21)
		{
			System.out.format("BEAN [Bean11] and BEAN [Bean21] point to the SAME OBJECT !\n");
		}
		else
		{
			System.out.format("BEAN [Bean11] and BEAN [Bean21] point to DIFFERENT OBJECTS !\n");
		}

		// Vrati FALSE.
		if (Bean11==Bean22)
		{
			System.out.format("BEAN [Bean11] and BEAN [Bean22] point to the SAME OBJECT !\n");
		}
		else
		{
			System.out.format("BEAN [Bean11] and BEAN [Bean22] point to DIFFERENT OBJECTS !\n");
		}

		// Vrati FALSE.
		if (Bean12==Bean21)
		{
			System.out.format("BEAN [Bean12] and BEAN [Bean21] point to the SAME OBJECT !\n");
		}
		else
		{
			System.out.format("BEAN [Bean12] and BEAN [Bean21] point to DIFFERENT OBJECTS !\n");
		}

		// Vrati FALSE.
		if (Bean12==Bean22)
		{
			System.out.format("BEAN [Bean12] and BEAN [Bean22] point to the SAME OBJECT !\n");
		}
		else
		{
			System.out.format("BEAN [Bean12] and BEAN [Bean22] point to DIFFERENT OBJECTS !\n");
		}

		// Vrati TRUE.
		if (Bean21==Bean22)
		{
			System.out.format("BEAN [Bean21] and BEAN [Bean22] point to the SAME OBJECT !\n");
		}
		else
		{
			System.out.format("BEAN [Bean21] and BEAN [Bean22] point to DIFFERENT OBJECTS !\n");
		}

		Context.close();
		
		CHelpers.PrintLineSeparator();
	}
//----------------------------------------------------------------------------------------------------------------------
	public static void TestSingletonByStereotype()
	{
		CHelpers.PrintLineSeparator();

		System.out.println("CONTEXT CREATING !");
		
		AnnotationConfigApplicationContext						Context=new AnnotationConfigApplicationContext(CSingletonByStereotypeConfiguration.class);

		System.out.println("CONTEXT CREATED !");

		CSingletonByStereotypeBeanParent1						BeanParent1=Context.getBean(CSingletonByStereotypeBeanParent1.class);
		CSingletonByStereotypeBeanParent2						BeanParent2=Context.getBean(CSingletonByStereotypeBeanParent2.class);
		CSingletonByStereotypeBeanChild							BeanChild=Context.getBean(CSingletonByStereotypeBeanChild.class);

		// Vrati TRUE.
		if (BeanParent1.getChild()==BeanParent2.getChild())
		{
			System.out.format("BEAN [BeanParent1.Child] and BEAN [BeanParent2] point to the SAME OBJECT !\n");
		}
		else
		{
			System.out.format("BEAN [BeanParent1.Child] and BEAN [BeanParent2] point to DIFFERENT OBJECTS !\n");
		}

		// Vrati TRUE.
		if (BeanParent1.getChild()==BeanChild)
		{
			System.out.format("BEAN [BeanParent1.Child] and BEAN [BeanChild] point to the SAME OBJECT !\n");
		}
		else
		{
			System.out.format("BEAN [BeanParent1.Child] and BEAN [BeanChild] point to DIFFERENT OBJECTS !\n");
		}

		// Vrati TRUE.
		if (BeanParent2.getChild()==BeanChild)
		{
			System.out.format("BEAN [BeanParent2.Child] and BEAN [BeanChild] point to the SAME OBJECT !\n");
		}
		else
		{
			System.out.format("BEAN [BeanParent2.Child] and BEAN [BeanChild] point to DIFFERENT OBJECTS !\n");
		}

		Context.close();
		
		CHelpers.PrintLineSeparator();
	}
//----------------------------------------------------------------------------------------------------------------------
	public static void TestSingletonEagerVsLazy()
	{
		CHelpers.PrintLineSeparator();

		System.out.println("CONTEXT CREATING !");
		
		AnnotationConfigApplicationContext						Context=new AnnotationConfigApplicationContext(CSingletonEagerVsLazyConfiguration.class);

		System.out.println("CONTEXT CREATED !");

		System.out.println("BEAN [CSingletonEagerVsLazyBeanLazy] CREATING !");

		CSingletonEagerVsLazyBeanLazy							Bean1=Context.getBean(CSingletonEagerVsLazyBeanLazy.class);

		System.out.println("BEAN [CSingletonEagerVsLazyBeanLazy] CREATED !");

		System.out.println("BEAN [CSingletonEagerVsLazyBeanEager] CREATING !");
		
		CSingletonEagerVsLazyBeanEager							Bean2=Context.getBean(CSingletonEagerVsLazyBeanEager.class);

		System.out.println("BEAN [CSingletonEagerVsLazyBeanEager] CREATED !");

		Bean1.Print();
		Bean2.Print();

		Context.close();
		
		CHelpers.PrintLineSeparator();
	}
//----------------------------------------------------------------------------------------------------------------------
	public static void TestPrototypeByBean()
	{
		CHelpers.PrintLineSeparator();

		System.out.println("CONTEXT CREATING !");
		
		AnnotationConfigApplicationContext						Context=new AnnotationConfigApplicationContext(CPrototypeByBeanConfguration.class);

		System.out.println("CONTEXT CREATED !");

		CPrototypeByBeanBean									Bean11=Context.getBean("BEAN_1",CPrototypeByBeanBean.class);
		CPrototypeByBeanBean									Bean12=Context.getBean("BEAN_1",CPrototypeByBeanBean.class);
		CPrototypeByBeanBean									Bean21=Context.getBean("BEAN_2",CPrototypeByBeanBean.class);
		CPrototypeByBeanBean									Bean22=Context.getBean("BEAN_2",CPrototypeByBeanBean.class);

		System.out.format("BEAN [Bean11] has VALUE [%s] !\n",Bean11.getValue());
		System.out.format("BEAN [Bean12] has VALUE [%s] !\n",Bean12.getValue());
		System.out.format("BEAN [Bean21] has VALUE [%s] !\n",Bean21.getValue());
		System.out.format("BEAN [Bean22] has VALUE [%s] !\n",Bean22.getValue());

		// Vrati FALSE.
		if (Bean11==Bean12)
		{
			System.out.format("BEAN [Bean11] and BEAN [Bean12] point to the SAME OBJECT !\n");
		}
		else
		{
			System.out.format("BEAN [Bean11] and BEAN [Bean12] point to DIFFERENT OBJECTS !\n");
		}

		// Vrati FALSE.
		if (Bean11==Bean21)
		{
			System.out.format("BEAN [Bean11] and BEAN [Bean21] point to the SAME OBJECT !\n");
		}
		else
		{
			System.out.format("BEAN [Bean11] and BEAN [Bean21] point to DIFFERENT OBJECTS !\n");
		}

		// Vrati FALSE.
		if (Bean11==Bean22)
		{
			System.out.format("BEAN [Bean11] and BEAN [Bean22] point to the SAME OBJECT !\n");
		}
		else
		{
			System.out.format("BEAN [Bean11] and BEAN [Bean22] point to DIFFERENT OBJECTS !\n");
		}

		// Vrati FALSE.
		if (Bean12==Bean21)
		{
			System.out.format("BEAN [Bean12] and BEAN [Bean21] point to the SAME OBJECT !\n");
		}
		else
		{
			System.out.format("BEAN [Bean12] and BEAN [Bean21] point to DIFFERENT OBJECTS !\n");
		}

		// Vrati FALSE.
		if (Bean12==Bean22)
		{
			System.out.format("BEAN [Bean12] and BEAN [Bean22] point to the SAME OBJECT !\n");
		}
		else
		{
			System.out.format("BEAN [Bean12] and BEAN [Bean22] point to DIFFERENT OBJECTS !\n");
		}

		// Vrati FALSE.
		if (Bean21==Bean22)
		{
			System.out.format("BEAN [Bean21] and BEAN [Bean22] point to the SAME OBJECT !\n");
		}
		else
		{
			System.out.format("BEAN [Bean21] and BEAN [Bean22] point to DIFFERENT OBJECTS !\n");
		}

		Context.close();
		
		CHelpers.PrintLineSeparator();
	}
//----------------------------------------------------------------------------------------------------------------------
	public static void TestPrototypeByStereotype()
	{
		CHelpers.PrintLineSeparator();

		System.out.println("CONTEXT CREATING !");
		
		AnnotationConfigApplicationContext						Context=new AnnotationConfigApplicationContext(CPrototypeByStereotypeConfiguration.class);

		System.out.println("CONTEXT CREATED !");

		CPrototypeByStereotypeBeanParent1						BeanParent1=Context.getBean(CPrototypeByStereotypeBeanParent1.class);
		CPrototypeByStereotypeBeanParent2						BeanParent2=Context.getBean(CPrototypeByStereotypeBeanParent2.class);
		CPrototypeByStereotypeBeanChild							BeanChild=Context.getBean(CPrototypeByStereotypeBeanChild.class);

		// Vrati FALSE.
		if (BeanParent1.getChild()==BeanParent2.getChild())
		{
			System.out.format("BEAN [BeanParent1.Child] and BEAN [BeanParent2] point to the SAME OBJECT !\n");
		}
		else
		{
			System.out.format("BEAN [BeanParent1.Child] and BEAN [BeanParent2] point to DIFFERENT OBJECTS !\n");
		}

		// Vrati FALSE.
		if (BeanParent1.getChild()==BeanChild)
		{
			System.out.format("BEAN [BeanParent1.Child] and BEAN [BeanChild] point to the SAME OBJECT !\n");
		}
		else
		{
			System.out.format("BEAN [BeanParent1.Child] and BEAN [BeanChild] point to DIFFERENT OBJECTS !\n");
		}

		// Vrati FALSE.
		if (BeanParent2.getChild()==BeanChild)
		{
			System.out.format("BEAN [BeanParent2.Child] and BEAN [BeanChild] point to the SAME OBJECT !\n");
		}
		else
		{
			System.out.format("BEAN [BeanParent2.Child] and BEAN [BeanChild] point to DIFFERENT OBJECTS !\n");
		}

		Context.close();
		
		CHelpers.PrintLineSeparator();
	}
//----------------------------------------------------------------------------------------------------------------------
	public static void TestPrototypeBeanInSingletonBean()
	{
		CHelpers.PrintLineSeparator();

		System.out.println("CONTEXT CREATING !");
		
		AnnotationConfigApplicationContext						Context=new AnnotationConfigApplicationContext(CPrototypeBeanInSingletonBeanConfiguration.class);

		System.out.println("CONTEXT CREATED !");

		CPrototypeBeanInSingletonBeanSingleton					Bean=Context.getBean(CPrototypeBeanInSingletonBeanSingleton.class);

		Bean.Execute();

		Context.close();
		
		CHelpers.PrintLineSeparator();
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	public static void main(String[] args)
	{
		//TestSingletonByBean();
		//TestSingletonByStereotype();
		//TestSingletonEagerVsLazy();
		//TestPrototypeByBean();
		//TestPrototypeByStereotype();
		TestPrototypeBeanInSingletonBean();
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------