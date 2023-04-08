//----------------------------------------------------------------------------------------------------------------------
package main;
//----------------------------------------------------------------------------------------------------------------------
import org.springframework.context.annotation.AnnotationConfigApplicationContext;
import Helpers.*;
import DI1.*;
import DI2.*;
import DI3.*;
import CircularDependencies.*;
import MultipleBeansFieldName.*;
import MultipleBeansConstructorParameterName.*;
import MultipleBeansSetterName.*;
import MultipleBeansPrimary.*;
import MultipleBeansFieldQualifier.*;
import MultipleBeansConstructorParameterQualifier.*;
import MultipleBeansSetterQualifier.*;
//----------------------------------------------------------------------------------------------------------------------
public class Main
{
//----------------------------------------------------------------------------------------------------------------------
	public static void TestNotWiredBeans()
	{
		CHelpers.PrintLineSeparator();
		
		AnnotationConfigApplicationContext						Context=new AnnotationConfigApplicationContext(CProjectConfiguration1.class);

		CNotWiredBeanParent										BeanParent=Context.getBean(CNotWiredBeanParent.class);
		CNotWiredBeanChild										BeanChild=Context.getBean(CNotWiredBeanChild.class);
		
		System.out.format("BeanParent.Value [%s] !\n",BeanParent.getValue());
		System.out.format("BeanChild.Value [%s] !\n",BeanChild.getValue());
		
		// !!!!! Vrati NULL, pretoze BEANS NIE SU WIRED.
		if (BeanParent.getChild()==null)
		{
			System.out.format("BeanParent.Child [%s] !\n",BeanParent.getChild());
		}
		else
		{
			System.out.format("BeanParent.Child.Value [%s] !\n",BeanParent.getChild().getValue());
		}
		
		Context.close();
		
		CHelpers.PrintLineSeparator();
	}
//----------------------------------------------------------------------------------------------------------------------
	public static void TestWiredBeans1()
	{
		CHelpers.PrintLineSeparator();
		
		System.out.println("CONTEXT CREATING !");

		// !!! Instancie SPRING BEANS sa vytvaraju uz pri vytvoreni SPRING CONTEXT. 
		AnnotationConfigApplicationContext						Context=new AnnotationConfigApplicationContext(CProjectConfiguration2.class);

		System.out.println("CONTEXT CREATED !");

		CWiredBeanChild											BeanChild=Context.getBean(CWiredBeanChild.class);
		CWiredBeanParent										BeanParent=Context.getBean(CWiredBeanParent.class);
		
		System.out.format("BeanParent.Value [%s] !\n",BeanParent.getValue());
		System.out.format("BeanChild.Value [%s] !\n",BeanChild.getValue());
		
		// !!!!! Vrati NOT NULL, pretoze BEANS SU WIRED.
		if (BeanParent.getChild()==null)
		{
			System.out.format("BeanParent.Child [%s] !\n",BeanParent.getChild());
		}
		else
		{
			System.out.format("BeanParent.Child.Value [%s] !\n",BeanParent.getChild().getValue());
		}

		// Oba BEANS su IDENTICKE OBJECTS.
		if (BeanChild==BeanParent.getChild())
		{
			System.out.format("BEAN [BeanChild] and BEAN [BeanParent.Child] point to the SAME OBJECT !\n");
		}
		else
		{
			System.out.format("BEAN [BeanChild] and BEAN [BeanParent.Child] point to DIFFERENT OBJECTS !\n");
		}
		
		Context.close();
		
		CHelpers.PrintLineSeparator();
	}
//----------------------------------------------------------------------------------------------------------------------
	public static void TestWiredBeans2()
	{
		CHelpers.PrintLineSeparator();
		
		System.out.println("CONTEXT CREATING !");

		// !!! Instancie SPRING BEANS sa vytvaraju uz pri vytvoreni SPRING CONTEXT. 
		AnnotationConfigApplicationContext						Context=new AnnotationConfigApplicationContext(CProjectConfiguration2.class);

		System.out.println("CONTEXT CREATED !");

		CWiredBeanParent										BeanParent=Context.getBean(CWiredBeanParent.class);
		
		System.out.format("BeanParent.Value [%s] !\n",BeanParent.getValue());
		
		// !!!!! Vrati NOT NULL, pretoze BEANS SU WIRED.
		if (BeanParent.getChild()==null)
		{
			System.out.format("BeanParent.Child [%s] !\n",BeanParent.getChild());
		}
		else
		{
			System.out.format("BeanParent.Child.Value [%s] !\n",BeanParent.getChild().getValue());
		}
		
		Context.close();
		
		CHelpers.PrintLineSeparator();
	}
//----------------------------------------------------------------------------------------------------------------------
	public static void TestAutoWiredBeans()
	{
		CHelpers.PrintLineSeparator();
		
		System.out.println("CONTEXT CREATING !");

		// !!! Instancie SPRING BEANS sa vytvaraju uz pri vytvoreni SPRING CONTEXT. 
		AnnotationConfigApplicationContext						Context=new AnnotationConfigApplicationContext(CProjectConfiguration3.class);

		System.out.println("CONTEXT CREATED !");

		CAutoWiredBeanParent									BeanParent=Context.getBean(CAutoWiredBeanParent.class);
		CAutoWiredBeanChild										BeanChild=Context.getBean(CAutoWiredBeanChild.class);
		
		System.out.format("BeanParent.Value [%s] !\n",BeanParent.getValue());
		System.out.format("BeanChild.Value [%s] !\n",BeanChild.getValue());
		
		// !!!!! Vrati NOT NULL, pretoze BEANS SU WIRED.
		if (BeanParent.getChild()==null)
		{
			System.out.format("BeanParent.Child [%s] !\n",BeanParent.getChild());
		}
		else
		{
			System.out.format("BeanParent.Child.Value [%s] !\n",BeanParent.getChild().getValue());
		}

		// Oba BEANS su IDENTICKE OBJECTS.
		if (BeanChild==BeanParent.getChild())
		{
			System.out.format("BEAN [BeanChild] and BEAN [BeanParent.Child] point to the SAME OBJECT !\n");
		}
		else
		{
			System.out.format("BEAN [BeanChild] and BEAN [BeanParent.Child] point to DIFFERENT OBJECTS !\n");
		}
		
		Context.close();
		
		CHelpers.PrintLineSeparator();
	}
//----------------------------------------------------------------------------------------------------------------------
	public static void TestDependencyInjectionFieldBeans()
	{
		CHelpers.PrintLineSeparator();
		
		System.out.println("CONTEXT CREATING !");

		// !!! Instancie SPRING BEANS sa vytvaraju uz pri vytvoreni SPRING CONTEXT. 
		AnnotationConfigApplicationContext						Context=new AnnotationConfigApplicationContext(CProjectConfiguration4.class);

		System.out.println("CONTEXT CREATED !");

		CDIFieldParent											BeanParent=Context.getBean(CDIFieldParent.class);
		
		System.out.format("BeanParent.Value [%s] !\n",BeanParent.getValue());
		
		// !!!!! Vrati NOT NULL, pretoze BEANS SU WIRED.
		if (BeanParent.getChild()==null)
		{
			System.out.format("BeanParent.Child [%s] !\n",BeanParent.getChild());
		}
		else
		{
			System.out.format("BeanParent.Child.Value [%s] !\n",BeanParent.getChild().getValue());
		}
		
		Context.close();
		
		CHelpers.PrintLineSeparator();
	}
//----------------------------------------------------------------------------------------------------------------------
	public static void TestDependencyInjectionConstructorBeans()
	{
		CHelpers.PrintLineSeparator();
		
		System.out.println("CONTEXT CREATING !");

		// !!! Instancie SPRING BEANS sa vytvaraju uz pri vytvoreni SPRING CONTEXT. 
		AnnotationConfigApplicationContext						Context=new AnnotationConfigApplicationContext(CProjectConfiguration5.class);

		System.out.println("CONTEXT CREATED !");

		CDIConstructorParent									BeanParent=Context.getBean(CDIConstructorParent.class);
		
		System.out.format("BeanParent.Value [%s] !\n",BeanParent.getValue());
		
		// !!!!! Vrati NOT NULL, pretoze BEANS SU WIRED.
		if (BeanParent.getChild()==null)
		{
			System.out.format("BeanParent.Child [%s] !\n",BeanParent.getChild());
		}
		else
		{
			System.out.format("BeanParent.Child.Value [%s] !\n",BeanParent.getChild().getValue());
		}
		
		Context.close();
		
		CHelpers.PrintLineSeparator();
	}
//----------------------------------------------------------------------------------------------------------------------
	public static void TestDependencyInjectionSetterBeans()
	{
		CHelpers.PrintLineSeparator();
		
		System.out.println("CONTEXT CREATING !");

		// !!! Instancie SPRING BEANS sa vytvaraju uz pri vytvoreni SPRING CONTEXT. 
		AnnotationConfigApplicationContext						Context=new AnnotationConfigApplicationContext(CProjectConfiguration6.class);

		System.out.println("CONTEXT CREATED !");

		CDISetterParent											BeanParent=Context.getBean(CDISetterParent.class);
		
		System.out.format("BeanParent.Value [%s] !\n",BeanParent.getValue());
		
		// !!!!! Vrati NOT NULL, pretoze BEANS SU WIRED.
		if (BeanParent.getChild()==null)
		{
			System.out.format("BeanParent.Child [%s] !\n",BeanParent.getChild());
		}
		else
		{
			System.out.format("BeanParent.Child.Value [%s] !\n",BeanParent.getChild().getValue());
		}
		
		Context.close();
		
		CHelpers.PrintLineSeparator();
	}
//----------------------------------------------------------------------------------------------------------------------
	public static void TestCircularDependenciesBeans()
	{
		CHelpers.PrintLineSeparator();
		
		try
		{		
			System.out.println("CONTEXT CREATING !");
	
			// !!! Instancie SPRING BEANS sa vytvaraju uz pri vytvoreni SPRING CONTEXT. 
			AnnotationConfigApplicationContext					Context=new AnnotationConfigApplicationContext(CProjectConfiguration7.class);
	
			System.out.println("CONTEXT CREATED !");
	
			CCDBean1											Bean=Context.getBean(CCDBean1.class);
			
			System.out.format("Bean.Value [%s] !\n",Bean.getValue());
			
			// !!!!! Vrati NOT NULL, pretoze BEANS SU WIRED.
			if (Bean.getChild()==null)
			{
				System.out.format("Bean.Child [%s] !\n",Bean.getChild());
			}
			else
			{
				System.out.format("Bean.Child.Value [%s] !\n",Bean.getChild().getValue());
			}
			
			Context.close();
		}
		catch(Exception E)
		{
			System.out.format("EXCEPTION [%s].\n",E.getMessage());
		}
		
		CHelpers.PrintLineSeparator();
	}
//----------------------------------------------------------------------------------------------------------------------
	public static void TestMultipleBeansFieldName()
	{
		CHelpers.PrintLineSeparator();
		
		System.out.println("CONTEXT CREATING !");

		// !!! Instancie SPRING BEANS sa vytvaraju uz pri vytvoreni SPRING CONTEXT. 
		AnnotationConfigApplicationContext						Context=new AnnotationConfigApplicationContext(CMultipleBeansFieldNameConfiguration.class);

		System.out.println("CONTEXT CREATED !");

		CMultipleBeansFieldNameParent							BeanParent=Context.getBean(CMultipleBeansFieldNameParent.class);
		
		System.out.format("BeanParent.Value [%s] !\n",BeanParent.getValue());
		
		// !!!!! Vrati NOT NULL, pretoze BEANS SU WIRED.
		if (BeanParent.getChild()==null)
		{
			System.out.format("BeanParent.Child [%s] !\n",BeanParent.getChild());
		}
		else
		{
			System.out.format("BeanParent.Child.Value [%s] !\n",BeanParent.getChild().getValue());
		}

		// !!! Vytvara sa BEAN podla NAME a TYPE.
		CMultipleBeansFieldNameChild							BeanChild=Context.getBean("OtherChild",CMultipleBeansFieldNameChild.class);
		
		System.out.format("BeanChild.Value [%s] !\n",BeanChild.getValue());
		
		Context.close();
		
		CHelpers.PrintLineSeparator();
	}
//----------------------------------------------------------------------------------------------------------------------
	public static void TestMultipleBeansConstructorParameterName()
	{
		CHelpers.PrintLineSeparator();
		
		System.out.println("CONTEXT CREATING !");

		// !!! Instancie SPRING BEANS sa vytvaraju uz pri vytvoreni SPRING CONTEXT. 
		AnnotationConfigApplicationContext						Context=new AnnotationConfigApplicationContext(CMultipleBeansConstructorParameterNameConfiguration.class);

		System.out.println("CONTEXT CREATED !");

		CMultipleBeansConstructorParameterNameParent			BeanParent=Context.getBean(CMultipleBeansConstructorParameterNameParent.class);
		
		System.out.format("BeanParent.Value [%s] !\n",BeanParent.getValue());
		
		// !!!!! Vrati NOT NULL, pretoze BEANS SU WIRED.
		if (BeanParent.getChild()==null)
		{
			System.out.format("BeanParent.Child [%s] !\n",BeanParent.getChild());
		}
		else
		{
			System.out.format("BeanParent.Child.Value [%s] !\n",BeanParent.getChild().getValue());
		}

		// !!! Vytvara sa BEAN podla NAME a TYPE.
		CMultipleBeansConstructorParameterNameChild				BeanChild=Context.getBean("OtherChild",CMultipleBeansConstructorParameterNameChild.class);
		
		System.out.format("BeanChild.Value [%s] !\n",BeanChild.getValue());
		
		Context.close();
		
		CHelpers.PrintLineSeparator();
	}
//----------------------------------------------------------------------------------------------------------------------
	public static void TestMultipleBeansSetterName()
	{
		CHelpers.PrintLineSeparator();

		System.out.println("CONTEXT CREATING !");

		// !!! Instancie SPRING BEANS sa vytvaraju uz pri vytvoreni SPRING CONTEXT. 
		AnnotationConfigApplicationContext						Context=new AnnotationConfigApplicationContext(CMultipleBeansSetterNameConfiguration.class);

		System.out.println("CONTEXT CREATED !");

		CMultipleBeansSetterNameParent							BeanParent=Context.getBean(CMultipleBeansSetterNameParent.class);
		
		System.out.format("BeanParent.Value [%s] !\n",BeanParent.getValue());
		
		// !!!!! Vrati NOT NULL, pretoze BEANS SU WIRED.
		if (BeanParent.getChild()==null)
		{
			System.out.format("BeanParent.Child [%s] !\n",BeanParent.getChild());
		}
		else
		{
			System.out.format("BeanParent.Child.Value [%s] !\n",BeanParent.getChild().getValue());
		}

		// !!! Vytvara sa BEAN podla NAME a TYPE.
		CMultipleBeansSetterNameChild							BeanChild=Context.getBean("OtherChild",CMultipleBeansSetterNameChild.class);
		
		System.out.format("BeanChild.Value [%s] !\n",BeanChild.getValue());
		
		Context.close();
		
		CHelpers.PrintLineSeparator();
	}
//----------------------------------------------------------------------------------------------------------------------
	public static void TestMultipleBeansPrimary()
	{
		CHelpers.PrintLineSeparator();

		System.out.println("CONTEXT CREATING !");

		// !!! Instancie SPRING BEANS sa vytvaraju uz pri vytvoreni SPRING CONTEXT. 
		AnnotationConfigApplicationContext						Context=new AnnotationConfigApplicationContext(CMultipleBeansPrimaryConfiguration.class);

		System.out.println("CONTEXT CREATED !");

		CMultipleBeansPrimaryParent								BeanParent=Context.getBean(CMultipleBeansPrimaryParent.class);
		
		System.out.format("BeanParent.Value [%s] !\n",BeanParent.getValue());
		
		// !!!!! Vrati NOT NULL, pretoze BEANS SU WIRED.
		if (BeanParent.getChild()==null)
		{
			System.out.format("BeanParent.Child [%s] !\n",BeanParent.getChild());
		}
		else
		{
			System.out.format("BeanParent.Child.Value [%s] !\n",BeanParent.getChild().getValue());
		}

		// !!! Vytvara sa BEAN podla NAME a TYPE.
		CMultipleBeansPrimaryChild								BeanChild=Context.getBean("OtherChild",CMultipleBeansPrimaryChild.class);
		
		System.out.format("BeanChild.Value [%s] !\n",BeanChild.getValue());
		
		Context.close();
		
		CHelpers.PrintLineSeparator();
	}
//----------------------------------------------------------------------------------------------------------------------
	public static void TestMultipleBeansFieldQualifier()
	{
		CHelpers.PrintLineSeparator();
		
		System.out.println("CONTEXT CREATING !");

		// !!! Instancie SPRING BEANS sa vytvaraju uz pri vytvoreni SPRING CONTEXT. 
		AnnotationConfigApplicationContext						Context=new AnnotationConfigApplicationContext(CMultipleBeansFieldQualifierConfiguration.class);

		System.out.println("CONTEXT CREATED !");

		CMultipleBeansFieldQualifierParent						BeanParent=Context.getBean(CMultipleBeansFieldQualifierParent.class);
		
		System.out.format("BeanParent.Value [%s] !\n",BeanParent.getValue());
		
		// !!!!! Vrati NOT NULL, pretoze BEANS SU WIRED.
		if (BeanParent.getChild()==null)
		{
			System.out.format("BeanParent.Child [%s] !\n",BeanParent.getChild());
		}
		else
		{
			System.out.format("BeanParent.Child.Value [%s] !\n",BeanParent.getChild().getValue());
		}

		// !!! Vytvara sa BEAN podla NAME a TYPE.
		CMultipleBeansFieldQualifierChild						BeanChild=Context.getBean("OtherChild",CMultipleBeansFieldQualifierChild.class);
		
		System.out.format("BeanChild.Value [%s] !\n",BeanChild.getValue());
		
		Context.close();
		
		CHelpers.PrintLineSeparator();
	}
//----------------------------------------------------------------------------------------------------------------------
	public static void TestMultipleBeansConstructorParameterQualifier()
	{
		CHelpers.PrintLineSeparator();
		
		System.out.println("CONTEXT CREATING !");

		// !!! Instancie SPRING BEANS sa vytvaraju uz pri vytvoreni SPRING CONTEXT. 
		AnnotationConfigApplicationContext						Context=new AnnotationConfigApplicationContext(CMultipleBeansConstructorParameterQualifierConfiguration.class);

		System.out.println("CONTEXT CREATED !");

		CMultipleBeansConstructorParameterQualifierParent		BeanParent=Context.getBean(CMultipleBeansConstructorParameterQualifierParent.class);
		
		System.out.format("BeanParent.Value [%s] !\n",BeanParent.getValue());
		
		// !!!!! Vrati NOT NULL, pretoze BEANS SU WIRED.
		if (BeanParent.getChild()==null)
		{
			System.out.format("BeanParent.Child [%s] !\n",BeanParent.getChild());
		}
		else
		{
			System.out.format("BeanParent.Child.Value [%s] !\n",BeanParent.getChild().getValue());
		}

		// !!! Vytvara sa BEAN podla NAME a TYPE.
		CMultipleBeansConstructorParameterQualifierChild		BeanChild=Context.getBean("OtherChild",CMultipleBeansConstructorParameterQualifierChild.class);
		
		System.out.format("BeanChild.Value [%s] !\n",BeanChild.getValue());
		
		Context.close();
		
		CHelpers.PrintLineSeparator();
	}
//----------------------------------------------------------------------------------------------------------------------
	public static void TestMultipleBeansSetterQualifier()
	{
		CHelpers.PrintLineSeparator();

		System.out.println("CONTEXT CREATING !");

		// !!! Instancie SPRING BEANS sa vytvaraju uz pri vytvoreni SPRING CONTEXT. 
		AnnotationConfigApplicationContext						Context=new AnnotationConfigApplicationContext(CMultipleBeansSetterQualifierConfiguration.class);

		System.out.println("CONTEXT CREATED !");

		CMultipleBeansSetterQualifierParent						BeanParent=Context.getBean(CMultipleBeansSetterQualifierParent.class);
		
		System.out.format("BeanParent.Value [%s] !\n",BeanParent.getValue());
		
		// !!!!! Vrati NOT NULL, pretoze BEANS SU WIRED.
		if (BeanParent.getChild()==null)
		{
			System.out.format("BeanParent.Child [%s] !\n",BeanParent.getChild());
		}
		else
		{
			System.out.format("BeanParent.Child.Value [%s] !\n",BeanParent.getChild().getValue());
		}

		// !!! Vytvara sa BEAN podla NAME a TYPE.
		CMultipleBeansSetterQualifierChild						BeanChild=Context.getBean("OtherChild",CMultipleBeansSetterQualifierChild.class);
		
		System.out.format("BeanChild.Value [%s] !\n",BeanChild.getValue());
		
		Context.close();
		
		CHelpers.PrintLineSeparator();
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	public static void main(String[] args)
	{
		//TestNotWiredBeans();
		//TestWiredBeans1();
		//TestWiredBeans2();
		//TestAutoWiredBeans();
		//TestDependencyInjectionFieldBeans();
		//TestDependencyInjectionConstructorBeans();
		//TestDependencyInjectionSetterBeans();
		//TestCircularDependenciesBeans();
		//TestMultipleBeansFieldName();
		//TestMultipleBeansConstructorParameterName();
		//TestMultipleBeansSetterName();
		//TestMultipleBeansPrimary();
		//TestMultipleBeansFieldQualifier();
		//TestMultipleBeansConstructorParameterQualifier();
		TestMultipleBeansSetterQualifier();
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------