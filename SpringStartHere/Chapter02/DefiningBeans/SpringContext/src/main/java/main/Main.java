//----------------------------------------------------------------------------------------------------------------------
package main;
//----------------------------------------------------------------------------------------------------------------------
import java.util.function.Supplier;
import org.springframework.context.annotation.AnnotationConfigApplicationContext;
import Helpers.*;
//----------------------------------------------------------------------------------------------------------------------
public class Main
{
//----------------------------------------------------------------------------------------------------------------------
	public static void TestNoBean()
	{
		CHelpers.PrintLineSeparator();
		
		// !!! CLASS [AnnotationConfigApplicationContext] reprezentuje SPRING CONTEXT, ktory je konfigurovany pomocou ANNOTATIONS.
		AnnotationConfigApplicationContext						Context=new AnnotationConfigApplicationContext();

		// !!! OBJECT NIE JE BEAN, pretoze nebol vytvoreny v SPRING CONTEXT.
		CMyBean1												Bean=new CMyBean1();
		
		Bean.setValue("Some VALUE !");
		
		System.out.format("NO BEAN has VALUE [%s] !\n",Bean.getValue());
		
		Context.close();
		
		CHelpers.PrintLineSeparator();
	}
//----------------------------------------------------------------------------------------------------------------------
	public static void TestBean()
	{
		CHelpers.PrintLineSeparator();
		
		// !!! CLASS [AnnotationConfigApplicationContext] reprezentuje SPRING CONTEXT, ktory je konfigurovany pomocou ANNOTATIONS.
		AnnotationConfigApplicationContext						Context=new AnnotationConfigApplicationContext(CProjectConfiguration.class);

		// !!! OBJECT JE BEAN, pretoze bol vytvoreny v SPRING CONTEXT.
		CMyBean1												Bean=Context.getBean(CMyBean1.class);
		
		System.out.format("BEAN has VALUE [%s] !\n",Bean.getValue());
		
		Context.close();
		
		CHelpers.PrintLineSeparator();
	}
//----------------------------------------------------------------------------------------------------------------------
	public static void TestBeans()
	{
		CHelpers.PrintLineSeparator();
		
		// !!! CLASS [AnnotationConfigApplicationContext] reprezentuje SPRING CONTEXT, ktory je konfigurovany pomocou ANNOTATIONS.
		AnnotationConfigApplicationContext						Context=new AnnotationConfigApplicationContext(CProjectConfiguration.class);

		// !!! OBJECT JE BEAN, pretoze bol vytvoreny v SPRING CONTEXT.
		CMyBean1												Bean1=Context.getBean(CMyBean1.class);
		
		System.out.format("BEAN [CMyBean1] has VALUE [%s] !\n",Bean1.getValue());

		// !!! OBJECT JE BEAN, pretoze bol vytvoreny v SPRING CONTEXT.
		String													Bean2=Context.getBean(String.class);
		
		System.out.format("BEAN [CMyBean1] has VALUE [%s] !\n",Bean2);

		// !!! OBJECT JE BEAN, pretoze bol vytvoreny v SPRING CONTEXT.
		Integer													Bean3=Context.getBean(Integer.class);
		
		System.out.format("BEAN [CMyBean1] has VALUE [%d] !\n",Bean3);
		
		Context.close();
		
		CHelpers.PrintLineSeparator();
	}
//----------------------------------------------------------------------------------------------------------------------
	public static void TestBeansWithSameTypes()
	{
		CHelpers.PrintLineSeparator();
		
		// !!! CLASS [AnnotationConfigApplicationContext] reprezentuje SPRING CONTEXT, ktory je konfigurovany pomocou ANNOTATIONS.
		AnnotationConfigApplicationContext						Context=new AnnotationConfigApplicationContext(CProjectConfiguration.class);

		try
		{
			// !!! OBJECT JE BEAN, pretoze bol vytvoreny v SPRING CONTEXT.
			// !!!!! BEAN sa vytvara IBA podla TYPE. Kedze vsak nebola definovana ziadna DEFAULT METHOD pre vytvaranie BEANS daneho TYPE, dojde k EXCEPTION.
			CMyBean2											DefaultBean=Context.getBean(CMyBean2.class);
			
			System.out.format("DEFAULT BEAN [CMyBean2] has VALUE [%s] !\n",DefaultBean.getValue());
		}
		catch(Exception E)
		{
			System.out.format("EXCEPTION [%s].\n",E.getMessage());
		}
		
		// !!! OBJECT JE BEAN, pretoze bol vytvoreny v SPRING CONTEXT.
		// !!! BEAN sa vytvara na zaklade NAME a TYPE.
		CMyBean2												Bean1=Context.getBean("CreateMyBean21",CMyBean2.class);
		
		System.out.format("BEAN [CMyBean2] has VALUE [%s] !\n",Bean1.getValue());

		// !!! OBJECT JE BEAN, pretoze bol vytvoreny v SPRING CONTEXT.
		// !!! BEAN sa vytvara na zaklade NAME a TYPE.
		CMyBean2												Bean2=Context.getBean("CreateMyBean22",CMyBean2.class);
		
		System.out.format("BEAN [CMyBean2] has VALUE [%s] !\n",Bean2.getValue());

		// !!! OBJECT JE BEAN, pretoze bol vytvoreny v SPRING CONTEXT.
		// !!! BEAN sa vytvara na zaklade NAME a TYPE.
		CMyBean2												Bean3=Context.getBean("CreateMyBean23",CMyBean2.class);
		
		System.out.format("BEAN [CMyBean2] has VALUE [%s] !\n",Bean3.getValue());
		
		Context.close();
		
		CHelpers.PrintLineSeparator();
	}
//----------------------------------------------------------------------------------------------------------------------
	public static void TestBeansWithSameTypesWithDefault()
	{
		CHelpers.PrintLineSeparator();
		
		// !!! CLASS [AnnotationConfigApplicationContext] reprezentuje SPRING CONTEXT, ktory je konfigurovany pomocou ANNOTATIONS.
		AnnotationConfigApplicationContext						Context=new AnnotationConfigApplicationContext(CProjectConfiguration.class);

		try
		{
			// !!! OBJECT JE BEAN, pretoze bol vytvoreny v SPRING CONTEXT.
			// !!!!! BEAN sa vytvara IBA podla TYPE. Kedze vsak BOLA definovana DEFAULT METHOD tak sa BEAN USPESNE VYTVORI.
			CMyBean3											DefaultBean=Context.getBean(CMyBean3.class);
			
			System.out.format("DEFAULT BEAN [CMyBean3] has VALUE [%s] !\n",DefaultBean.getValue());
		}
		catch(Exception E)
		{
			System.out.format("EXCEPTION [%s].\n",E.getMessage());
		}
		
		// !!! OBJECT JE BEAN, pretoze bol vytvoreny v SPRING CONTEXT.
		// !!! BEAN sa vytvara na zaklade NAME a TYPE.
		CMyBean3												Bean1=Context.getBean("CreateMyBean31",CMyBean3.class);
		
		System.out.format("BEAN [CMyBean3] has VALUE [%s] !\n",Bean1.getValue());

		// !!! OBJECT JE BEAN, pretoze bol vytvoreny v SPRING CONTEXT.
		// !!! BEAN sa vytvara na zaklade NAME a TYPE.
		CMyBean3												Bean2=Context.getBean("CreateMyBean32",CMyBean3.class);
		
		System.out.format("BEAN [CMyBean3] has VALUE [%s] !\n",Bean2.getValue());

		// !!! OBJECT JE BEAN, pretoze bol vytvoreny v SPRING CONTEXT.
		// !!! BEAN sa vytvara na zaklade NAME a TYPE.
		CMyBean3												Bean3=Context.getBean("CreateMyBean33",CMyBean3.class);
		
		System.out.format("BEAN [CMyBean3] has VALUE [%s] !\n",Bean3.getValue());
		
		Context.close();
		
		CHelpers.PrintLineSeparator();
	}
//----------------------------------------------------------------------------------------------------------------------
	public static void TestBeansWithSameTypesAndCustomNames()
	{
		CHelpers.PrintLineSeparator();
		
		// !!! CLASS [AnnotationConfigApplicationContext] reprezentuje SPRING CONTEXT, ktory je konfigurovany pomocou ANNOTATIONS.
		AnnotationConfigApplicationContext						Context=new AnnotationConfigApplicationContext(CProjectConfiguration.class);

		// !!! OBJECT JE BEAN, pretoze bol vytvoreny v SPRING CONTEXT.
		// !!! BEAN sa vytvara na zaklade NAME a TYPE.
		CMyBean4												Bean1=Context.getBean("Bean1",CMyBean4.class);
		
		System.out.format("BEAN [CMyBean4] has VALUE [%s] !\n",Bean1.getValue());

		// !!! OBJECT JE BEAN, pretoze bol vytvoreny v SPRING CONTEXT.
		// !!! BEAN sa vytvara na zaklade NAME a TYPE.
		CMyBean4												Bean2=Context.getBean("Bean2",CMyBean4.class);
		
		System.out.format("BEAN [CMyBean4] has VALUE [%s] !\n",Bean2.getValue());

		// !!! OBJECT JE BEAN, pretoze bol vytvoreny v SPRING CONTEXT.
		// !!! BEAN sa vytvara na zaklade NAME a TYPE.
		CMyBean4												Bean3=Context.getBean("Bean3",CMyBean4.class);
		
		System.out.format("BEAN [CMyBean4] has VALUE [%s] !\n",Bean3.getValue());
		
		Context.close();
		
		CHelpers.PrintLineSeparator();
	}
//----------------------------------------------------------------------------------------------------------------------
	public static void TestCreateBeansByStereotypes()
	{
		CHelpers.PrintLineSeparator();
		
		// !!! CLASS [AnnotationConfigApplicationContext] reprezentuje SPRING CONTEXT, ktory je konfigurovany pomocou ANNOTATIONS.
		AnnotationConfigApplicationContext						Context1=new AnnotationConfigApplicationContext(CProjectConfiguration.class);
		AnnotationConfigApplicationContext						Context2=new AnnotationConfigApplicationContext(CProjectConfiguration.class);

		// !!! OBJECT JE BEAN, pretoze bol vytvoreny v SPRING CONTEXT.
		CMyStereotypeBean1										Bean1InContext1=Context1.getBean(CMyStereotypeBean1.class);
		
		// !!! VALUE je NULL, pretoze VALUE zatial nebola nastavena.
		System.out.format("BEAN [Bean1InContext1] has VALUE [%s] !\n",Bean1InContext1.getValue());
		
		Bean1InContext1.setValue("MAIN set in CONTEXT 1 !!!");

		// !!! Vrati nastavenu VALUE.
		System.out.format("BEAN [Bean1InContext1] has VALUE [%s] !\n",Bean1InContext1.getValue());

		// !!!!! SPRING CONTEXT vrati EXISTUJUCU SINGLETON INSTANCIU BEAN TYPE [CMyStereotypeBean1].
		CMyStereotypeBean1										Bean2InContext1=Context1.getBean(CMyStereotypeBean1.class);

		// !!! Vrati nastavenu VALUE.
		System.out.format("BEAN [Bean2InContext1] has VALUE [%s] !\n",Bean2InContext1.getValue());

		// !!! Vykona sa TEST ci obe referencie ukazuju na ten isty OBJECT.
		// !!!!! REFERENCIE ukazuju na TEN ISTY BEAN OBJECT, pretoze BEANS vytvarane pomocou STEREOTYPE ANNOTATIONS su SINGLETONS.
		if (Bean1InContext1==Bean2InContext1)
		{
			System.out.format("BEAN [Bean1InContext1] and BEAN [Bean2InContext1] point to the SAME OBJECT !\n");
		}
		else
		{
			System.out.format("BEAN [Bean1InContext1] and BEAN [Bean2InContext1] point to DIFFERENT OBJECTS !\n");
		}
		
		// !!! OBJECT JE BEAN, pretoze bol vytvoreny v SPRING CONTEXT.
		CMyStereotypeBean1										BeanInContext2=Context2.getBean(CMyStereotypeBean1.class);
		
		// !!! VALUE je NULL, pretoze VALUE zatial nebola nastavena.
		System.out.format("BEAN [BeanInContext2] has VALUE [%s] !\n",BeanInContext2.getValue());
		
		BeanInContext2.setValue("MAIN set in CONTEXT 2 !!!");

		// !!! Vrati nastavenu VALUE.
		System.out.format("BEAN [BeanInContext2] has VALUE [%s] !\n",BeanInContext2.getValue());
		
		// !!! Vykona sa TEST ci obe referencie ukazuju na ten isty OBJECT.
		// !!!!! REFERENCIE ukazuju na INY BEAN OBJECT, pretoze kazdy bol vytvoreny v INOM SPRING CONTEXT.
		if (Bean1InContext1==BeanInContext2)
		{
			System.out.format("BEAN [Bean1InContext1] and BEAN [BeanInContext2] point to the SAME OBJECT !\n");
		}
		else
		{
			System.out.format("BEAN [Bean1InContext1] and BEAN [BeanInContext2] point to DIFFERENT OBJECTS !\n");
		}
		
		Context1.close();
		Context2.close();
		
		CHelpers.PrintLineSeparator();
	}
//----------------------------------------------------------------------------------------------------------------------
	public static void TestCreateBeansWithEventsByStereotypes()
	{
		CHelpers.PrintLineSeparator();
		
		// !!! CLASS [AnnotationConfigApplicationContext] reprezentuje SPRING CONTEXT, ktory je konfigurovany pomocou ANNOTATIONS.
		AnnotationConfigApplicationContext						Context=new AnnotationConfigApplicationContext(CProjectConfiguration.class);

		// !!! OBJECT JE BEAN, pretoze bol vytvoreny v SPRING CONTEXT.
		CMyStereotypeBean2										Bean1=Context.getBean(CMyStereotypeBean2.class);
		
		System.out.format("BEAN [Bean1] has VALUE [%s] !\n",Bean1.getValue());

		// !!! OBJECT JE BEAN, pretoze bol vytvoreny v SPRING CONTEXT.
		// !!!!! Vrati sa EXISTUJUCI SINGLETON OBJECT.
		CMyStereotypeBean2										Bean2=Context.getBean(CMyStereotypeBean2.class);
		
		System.out.format("BEAN [Bean2] has VALUE [%s] !\n",Bean2.getValue());

		System.out.format("CONTEXT is CLOSING !\n");
		
		Context.close();

		System.out.format("CONTEXT is CLOSED !\n");

		CHelpers.PrintLineSeparator();
	}
//----------------------------------------------------------------------------------------------------------------------
	public static void TestCreateBeansProgrammable()
	{
		CHelpers.PrintLineSeparator();
		
		// !!! CLASS [AnnotationConfigApplicationContext] reprezentuje SPRING CONTEXT, ktory je konfigurovany pomocou ANNOTATIONS.
		AnnotationConfigApplicationContext						Context=new AnnotationConfigApplicationContext(CProjectConfiguration.class);

		// !!! Vytvori sa instancia JAVA OBJECT, ktory NIE JE BEAN.
		CMyProgrammableBean										Object1=new CMyProgrammableBean(); 

		Object1.setValue("OBJECT 1");

		System.out.format("OBJECT [Object1] has VALUE [%s] !\n",Object1.getValue());

		// !!! Vytvori sa FACTORY LABMDA EXPRESSION, ktory vrati instanciu JAVA OBJECT.
		Supplier<CMyProgrammableBean>							Supplier1=() -> Object1;

		// !!! JAVA OBJECT sa zaregistruje ako SPRING BEAN.
		Context.registerBean("MyBean1",CMyProgrammableBean.class,Supplier1,P -> P.setPrimary(false));

		// !!! Vrati sa zaregistrovany SPRING BEAN podla NAME a TYPE.
		CMyProgrammableBean										Bean1=Context.getBean("MyBean1",CMyProgrammableBean.class);
		
		System.out.format("BEAN [Bean1] has VALUE [%s] !\n",Bean1.getValue());

		try
		{
			// !!!!! BEAN sa vytvara IBA podla TYPE. Kedze vsak NEBOL zaregistrovany ZIADEN PRIMARY SPRING BEAN, tak dojde k vzniku EXCEPTION. 
			CMyProgrammableBean									DefaultBean1=Context.getBean(CMyProgrammableBean.class);
			
			System.out.format("DEFAULT BEAN [DefaultBean1] has VALUE [%s] !\n",DefaultBean1.getValue());
		}
		catch(Exception E)
		{
			System.out.format("EXCEPTION [%s].\n",E.getMessage());
		}

		// !!! Vytvori sa instancia JAVA OBJECT, ktory NIE JE BEAN.
		CMyProgrammableBean										Object2=new CMyProgrammableBean(); 

		Object2.setValue("OBJECT 2");

		System.out.format("OBJECT [Object2] has VALUE [%s] !\n",Object2.getValue());

		// !!! Vytvori sa FACTORY LABMDA EXPRESSION, ktory vrati instanciu JAVA OBJECT.
		Supplier<CMyProgrammableBean>							Supplier2=() -> Object2;

		// !!! JAVA OBJECT sa zaregistruje ako SPRING BEAN.
		Context.registerBean("MyBean2",CMyProgrammableBean.class,Supplier2,P -> P.setPrimary(true));

		// !!! Vrati sa zaregistrovany SPRING BEAN podla NAME a TYPE.
		CMyProgrammableBean										Bean2=Context.getBean("MyBean2",CMyProgrammableBean.class);
		
		System.out.format("BEAN [Bean2] has VALUE [%s] !\n",Bean2.getValue());

		try
		{
			// !!!!! BEAN sa vytvara IBA podla TYPE. Kedze vsak NEBOL zaregistrovany ZIADEN PRIMARY SPRING BEAN, tak dojde k vzniku EXCEPTION. 
			CMyProgrammableBean									DefaultBean2=Context.getBean(CMyProgrammableBean.class);
			
			System.out.format("DEFAULT BEAN [DefaultBean2] has VALUE [%s] !\n",DefaultBean2.getValue());
		}
		catch(Exception E)
		{
			System.out.format("EXCEPTION [%s].\n",E.getMessage());
		}

		// !!! Vytvori sa instancia JAVA OBJECT, ktory NIE JE BEAN.
		CMyProgrammableBean										Object3=new CMyProgrammableBean(); 

		Object3.setValue("OBJECT 3");

		System.out.format("OBJECT [Object3] has VALUE [%s] !\n",Object3.getValue());

		// !!! Vytvori sa FACTORY LABMDA EXPRESSION, ktory vrati instanciu JAVA OBJECT.
		Supplier<CMyProgrammableBean>							Supplier3=() -> Object3;

		// !!! JAVA OBJECT sa zaregistruje ako SPRING BEAN.
		Context.registerBean("MyBean3",CMyProgrammableBean.class,Supplier3,P -> P.setPrimary(false));

		// !!! Vrati sa zaregistrovany SPRING BEAN podla NAME a TYPE.
		CMyProgrammableBean										Bean3=Context.getBean("MyBean3",CMyProgrammableBean.class);
		
		System.out.format("BEAN [Bean3] has VALUE [%s] !\n",Bean3.getValue());

		try
		{
			// !!!!! BEAN sa vytvara IBA podla TYPE. Kedze vsak NEBOL zaregistrovany ZIADEN PRIMARY SPRING BEAN, tak dojde k vzniku EXCEPTION. 
			CMyProgrammableBean									DefaultBean3=Context.getBean(CMyProgrammableBean.class);
			
			System.out.format("DEFAULT BEAN [DefaultBean3] has VALUE [%s] !\n",DefaultBean3.getValue());
		}
		catch(Exception E)
		{
			System.out.format("EXCEPTION [%s].\n",E.getMessage());
		}
	
		Context.close();

		CHelpers.PrintLineSeparator();
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	public static void main(String[] args)
	{
		//TestNoBean();
		//TestBean();
		//TestBeans();
		//TestBeansWithSameTypes();
		//TestBeansWithSameTypesWithDefault();
		//TestBeansWithSameTypesAndCustomNames();
		//TestCreateBeansByStereotypes();
		//TestCreateBeansWithEventsByStereotypes();
		TestCreateBeansProgrammable();
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------