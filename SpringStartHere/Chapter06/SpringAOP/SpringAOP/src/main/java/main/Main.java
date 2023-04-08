//----------------------------------------------------------------------------------------------------------------------
package main;
//----------------------------------------------------------------------------------------------------------------------
import org.springframework.context.annotation.AnnotationConfigApplicationContext;
import Helpers.*;
import NoAspectBean.*;
import MyLogAspect.*;
import ReadParametersAspect.*;
import WriteParametersAspect.*;
import AspectsOnAnnotations.*;
import AspectBefore.*;
import AspectAfter.*;
import AspectAfterReturning.*;
import AspectAfterThrowing.*;
import AspectsOrder.*;
//----------------------------------------------------------------------------------------------------------------------
public class Main
{
//----------------------------------------------------------------------------------------------------------------------
	public static void TestBeanProxy()
	{
		CHelpers.PrintLineSeparator();

		System.out.println("CONTEXT CREATING !");
		
		AnnotationConfigApplicationContext						Context=new AnnotationConfigApplicationContext(CNoAspectBeanConfiguration.class);

		System.out.println("CONTEXT CREATED !");

		CNoAspectBeanBean1										NoBean1=new CNoAspectBeanBean1(); 

		NoBean1.Print();

		System.out.format("OBJECT [NoBean1] TYPE [%s].\n",NoBean1.getClass().getName());

		CNoAspectBeanBean2										NoBean2=new CNoAspectBeanBean2(); 

		NoBean2.Print();

		System.out.format("OBJECT [NoBean2] TYPE [%s].\n",NoBean2.getClass().getName());

		// !!! Vrati TYPE [CNoAspectBeanBean1] a NIE PROXY TYPE.
		CNoAspectBeanBean1										Bean1=Context.getBean(CNoAspectBeanBean1.class);

		Bean1.Print();

		System.out.format("OBJECT [Bean1] TYPE [%s].\n",Bean1.getClass().getName());

		// !!! Vrati TYPE [CNoAspectBeanBean2] a NIE PROXY TYPE.
		CNoAspectBeanBean2										Bean2=Context.getBean(CNoAspectBeanBean2.class);

		Bean2.Print();

		System.out.format("OBJECT [Bean2] TYPE [%s].\n",Bean2.getClass().getName());

		Context.close();
		
		CHelpers.PrintLineSeparator();
	}
//----------------------------------------------------------------------------------------------------------------------
	public static void TestMyLogAspect()
	{
		CHelpers.PrintLineSeparator();

		System.out.println("CONTEXT CREATING !");
		
		AnnotationConfigApplicationContext						Context=new AnnotationConfigApplicationContext(CMyLogAspectConfiguration.class);

		System.out.println("CONTEXT CREATED !");

		CMyLogAspectMessage										Message=new CMyLogAspectMessage("My TEXT 1.","My TEXT 2."); 

		// !!!!! Po aplikovani ANNOTATION [@Aspect] a ANNOTATION [@Around] vracia SPRING BEAN PROXY OBJECT, a nie skutocny TARGET OBJECT. 
		CMyLogAspectBean										Bean=Context.getBean(CMyLogAspectBean.class);

		// !!!!! Po aplikovani ANNOTATION [@Aspect] a ANNOTATION [@Around] vracia SPRING BEAN PROXY OBJECT, a nie skutocny TARGET OBJECT. 
		System.out.format("OBJECT [Bean] TYPE [%s].\n",Bean.getClass().getName());

		Bean.PrintMessage(Message);

		Context.close();
		
		CHelpers.PrintLineSeparator();
	}
//----------------------------------------------------------------------------------------------------------------------
	public static void TestReadParametersAspect()
	{
		CHelpers.PrintLineSeparator();

		System.out.println("CONTEXT CREATING !");
		
		AnnotationConfigApplicationContext						Context=new AnnotationConfigApplicationContext(CReadParametersAspectConfiguration.class);

		System.out.println("CONTEXT CREATED !");

		CReadParametersAspectMessage							Message=new CReadParametersAspectMessage("My TEXT 1.","My TEXT 2."); 

		// !!!!! Po aplikovani ANNOTATION [@Aspect] a ANNOTATION [@Around] vracia SPRING BEAN PROXY OBJECT, a nie skutocny TARGET OBJECT. 
		CReadParametersAspectBean								Bean=Context.getBean(CReadParametersAspectBean.class);

		// !!!!! Po aplikovani ANNOTATION [@Aspect] a ANNOTATION [@Around] vracia SPRING BEAN PROXY OBJECT, a nie skutocny TARGET OBJECT. 
		System.out.format("OBJECT [Bean] TYPE [%s].\n",Bean.getClass().getName());

		String													ReturnValue=Bean.PrintMessage(Message);
		
		System.out.format("OBJECT [Bean] returns RETURN VALUE [%s].\n",ReturnValue);

		Context.close();
		
		CHelpers.PrintLineSeparator();
	}
//----------------------------------------------------------------------------------------------------------------------
	public static void TestWriteParametersAspect()
	{
		CHelpers.PrintLineSeparator();

		System.out.println("CONTEXT CREATING !");
		
		AnnotationConfigApplicationContext						Context=new AnnotationConfigApplicationContext(CWriteParametersAspectConfiguration.class);

		System.out.println("CONTEXT CREATED !");

		CWriteParametersAspectMessage							Message=new CWriteParametersAspectMessage("My TEXT 1.","My TEXT 2."); 

		// !!!!! Po aplikovani ANNOTATION [@Aspect] a ANNOTATION [@Around] vracia SPRING BEAN PROXY OBJECT, a nie skutocny TARGET OBJECT. 
		CWriteParametersAspectBean								Bean=Context.getBean(CWriteParametersAspectBean.class);

		// !!!!! Po aplikovani ANNOTATION [@Aspect] a ANNOTATION [@Around] vracia SPRING BEAN PROXY OBJECT, a nie skutocny TARGET OBJECT. 
		System.out.format("OBJECT [Bean] TYPE [%s].\n",Bean.getClass().getName());

		String													ReturnValue=Bean.PrintMessage(Message);
		
		System.out.format("OBJECT [Bean] returns RETURN VALUE [%s].\n",ReturnValue);

		Context.close();
		
		CHelpers.PrintLineSeparator();
	}
//----------------------------------------------------------------------------------------------------------------------
	public static void TestAspectsOnAnnotations()
	{
		CHelpers.PrintLineSeparator();

		System.out.println("CONTEXT CREATING !");
		
		AnnotationConfigApplicationContext						Context=new AnnotationConfigApplicationContext(CAspectsOnAnnotationsConfiguration.class);

		System.out.println("CONTEXT CREATED !");

		// !!!!! Po aplikovani ANNOTATION [@Aspect] a ANNOTATION [@Around] vracia SPRING BEAN PROXY OBJECT, a nie skutocny TARGET OBJECT. 
		CAspectsOnAnnotationsBean								Bean=Context.getBean(CAspectsOnAnnotationsBean.class);

		// !!!!! Po aplikovani ANNOTATION [@Aspect] a ANNOTATION [@Around] vracia SPRING BEAN PROXY OBJECT, a nie skutocny TARGET OBJECT. 
		System.out.format("OBJECT [Bean] TYPE [%s].\n",Bean.getClass().getName());

		String													ReturnValue=Bean.PrintMessage("Some text.");
		
		System.out.format("OBJECT [Bean] returns RETURN VALUE [%s].\n",ReturnValue);

		Context.close();
		
		CHelpers.PrintLineSeparator();
	}
//----------------------------------------------------------------------------------------------------------------------
	public static void TestAspectBefore()
	{
		CHelpers.PrintLineSeparator();

		System.out.println("CONTEXT CREATING !");
		
		AnnotationConfigApplicationContext						Context=new AnnotationConfigApplicationContext(CAspectBeforeConfiguration.class);

		System.out.println("CONTEXT CREATED !");

		// !!!!! Po aplikovani ANNOTATION [@Aspect] a ANNOTATION [@Before] vracia SPRING BEAN PROXY OBJECT, a nie skutocny TARGET OBJECT. 
		CAspectBeforeBean										Bean=Context.getBean(CAspectBeforeBean.class);

		System.out.format("OBJECT [Bean] TYPE [%s].\n",Bean.getClass().getName());

		String													ReturnValue=Bean.PrintMessage("Some text.");
		
		System.out.format("OBJECT [Bean] returns RETURN VALUE [%s].\n",ReturnValue);

		Context.close();
		
		CHelpers.PrintLineSeparator();
	}
//----------------------------------------------------------------------------------------------------------------------
	public static void TestAspectAfter()
	{
		CHelpers.PrintLineSeparator();

		System.out.println("CONTEXT CREATING !");
		
		AnnotationConfigApplicationContext						Context=new AnnotationConfigApplicationContext(CAspectAfterConfiguration.class);

		System.out.println("CONTEXT CREATED !");

		// !!!!! Po aplikovani ANNOTATION [@Aspect] a ANNOTATION [@After] vracia SPRING BEAN PROXY OBJECT, a nie skutocny TARGET OBJECT. 
		CAspectAfterBean										Bean=Context.getBean(CAspectAfterBean.class);

		System.out.format("OBJECT [Bean] TYPE [%s].\n",Bean.getClass().getName());

		String													ReturnValue=Bean.PrintMessage("Some text.");
		
		System.out.format("OBJECT [Bean] returns RETURN VALUE [%s].\n",ReturnValue);

		Context.close();
		
		CHelpers.PrintLineSeparator();
	}
//----------------------------------------------------------------------------------------------------------------------
	public static void TestAspectAfterReturning()
	{
		CHelpers.PrintLineSeparator();

		System.out.println("CONTEXT CREATING !");
		
		AnnotationConfigApplicationContext						Context=new AnnotationConfigApplicationContext(CAspectAfterReturningConfiguration.class);

		System.out.println("CONTEXT CREATED !");

		// !!!!! Po aplikovani ANNOTATION [@Aspect] a ANNOTATION [@AfterReturning] vracia SPRING BEAN PROXY OBJECT, a nie skutocny TARGET OBJECT. 
		CAspectAfterReturningBean								Bean=Context.getBean(CAspectAfterReturningBean.class);

		System.out.format("OBJECT [Bean] TYPE [%s].\n",Bean.getClass().getName());

		CHelpers.PrintLineSeparator();

		try
		{
			String												ReturnValue=Bean.PrintMessage("Some text.",false);
		
			System.out.format("OBJECT [Bean] returns RETURN VALUE [%s].\n",ReturnValue);
		}
		catch(Throwable E)
		{
			System.out.format("EXCEPTION [%s].\n",E.getMessage());
		}

		CHelpers.PrintLineSeparator();

		try
		{
			String												ReturnValue=Bean.PrintMessage("Some text.",true);
		
			System.out.format("OBJECT [Bean] returns RETURN VALUE [%s].\n",ReturnValue);
		}
		catch(Throwable E)
		{
			System.out.format("EXCEPTION [%s].\n",E.getMessage());
		}

		Context.close();
		
		CHelpers.PrintLineSeparator();
	}
//----------------------------------------------------------------------------------------------------------------------
	public static void TestAspectAfterThrowing()
	{
		CHelpers.PrintLineSeparator();

		System.out.println("CONTEXT CREATING !");
		
		AnnotationConfigApplicationContext						Context=new AnnotationConfigApplicationContext(CAspectAfterThrowingConfiguration.class);

		System.out.println("CONTEXT CREATED !");

		// !!!!! Po aplikovani ANNOTATION [@Aspect] a ANNOTATION [@AfterThrowing] vracia SPRING BEAN PROXY OBJECT, a nie skutocny TARGET OBJECT. 
		CAspectAfterThrowingBean								Bean=Context.getBean(CAspectAfterThrowingBean.class);

		System.out.format("OBJECT [Bean] TYPE [%s].\n",Bean.getClass().getName());

		CHelpers.PrintLineSeparator();

		try
		{
			String												ReturnValue=Bean.PrintMessage("Some text.",false);
		
			System.out.format("OBJECT [Bean] returns RETURN VALUE [%s].\n",ReturnValue);
		}
		catch(Throwable E)
		{
			System.out.format("EXCEPTION [%s].\n",E.getMessage());
		}

		CHelpers.PrintLineSeparator();

		try
		{
			String												ReturnValue=Bean.PrintMessage("Some text.",true);
		
			System.out.format("OBJECT [Bean] returns RETURN VALUE [%s].\n",ReturnValue);
		}
		catch(Throwable E)
		{
			System.out.format("EXCEPTION [%s].\n",E.getMessage());
		}

		Context.close();
		
		CHelpers.PrintLineSeparator();
	}
//----------------------------------------------------------------------------------------------------------------------
	public static void TestAspectsOrder()
	{
		CHelpers.PrintLineSeparator();

		System.out.println("CONTEXT CREATING !");
		
		AnnotationConfigApplicationContext						Context=new AnnotationConfigApplicationContext(CAspectsOrderConfiguration.class);

		System.out.println("CONTEXT CREATED !");

		// !!!!! Po aplikovani ANNOTATION [@Aspect] a ANNOTATION [@After] vracia SPRING BEAN PROXY OBJECT, a nie skutocny TARGET OBJECT. 
		CAspectsOrderBean										Bean=Context.getBean(CAspectsOrderBean.class);

		System.out.format("OBJECT [Bean] TYPE [%s].\n",Bean.getClass().getName());

		String													ReturnValue=Bean.PrintMessage("Some text.");
		
		System.out.format("OBJECT [Bean] returns RETURN VALUE [%s].\n",ReturnValue);

		Context.close();
		
		CHelpers.PrintLineSeparator();
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	public static void main(String[] args)
	{
		//TestBeanProxy();
		//TestMyLogAspect();
		//TestReadParametersAspect();
		//TestWriteParametersAspect();
		//TestAspectsOnAnnotations();
		//TestAspectBefore();
		//TestAspectAfter();
		//TestAspectAfterReturning();
		//TestAspectAfterThrowing();
		TestAspectsOrder();
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------