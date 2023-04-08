//----------------------------------------------------------------------------------------------------------------------
package main;
//----------------------------------------------------------------------------------------------------------------------
import org.springframework.context.annotation.AnnotationConfigApplicationContext;
import Helpers.*;
import NoSpring.*;
import Spring1.*;
import Spring2.*;
import SpringMultiImplementationPrimary.*;
import SpringMultiImplementationQualifier.*;
import SpringServiceRepository.*;
//----------------------------------------------------------------------------------------------------------------------
public class Main
{
//----------------------------------------------------------------------------------------------------------------------
	public static void TestNoSpring()
	{
		CHelpers.PrintLineSeparator();

		CNoSpringMessage										Message1=new CNoSpringMessage("HELLO WOLRD 111 !!!"); 
		INoSpringPrintA											PrintA1=new CNoSpringPrintA1();
		INoSpringPrintB											PrintB1=new CNoSpringPrintB1();
		CNoSpringPrinter										Printer1=new CNoSpringPrinter(PrintA1,PrintB1);

		Printer1.PrintMessage(Message1);
		
		CNoSpringMessage										Message2=new CNoSpringMessage("HELLO WOLRD 222 !!!"); 
		INoSpringPrintA											PrintA2=new CNoSpringPrintA2();
		INoSpringPrintB											PrintB2=new CNoSpringPrintB2();
		CNoSpringPrinter										Printer2=new CNoSpringPrinter(PrintA2,PrintB2);
		
		Printer2.PrintMessage(Message2);
		
		CHelpers.PrintLineSeparator();
	}
//----------------------------------------------------------------------------------------------------------------------
	public static void TestSpring1()
	{
		CHelpers.PrintLineSeparator();

		System.out.println("CONTEXT CREATING !");

		// !!! Instancie SPRING BEANS sa vytvaraju uz pri vytvoreni SPRING CONTEXT. 
		AnnotationConfigApplicationContext						Context=new AnnotationConfigApplicationContext(CSpring1Configuration.class);

		System.out.println("CONTEXT CREATED !");

		// !!! Tento OBJECT NIE JE ulozeny v SPRING CONTEXT.
		CSpring1Message											Message=new CSpring1Message("HELLO WOLRD !!!");
		 
		CSpring1Printer											Bean=Context.getBean(CSpring1Printer.class);
		
		Bean.PrintMessage(Message);
		
		Context.close();
		
		CHelpers.PrintLineSeparator();
	}
//----------------------------------------------------------------------------------------------------------------------
	public static void TestSpring2()
	{
		CHelpers.PrintLineSeparator();

		System.out.println("CONTEXT CREATING !");

		// !!! Instancie SPRING BEANS sa vytvaraju uz pri vytvoreni SPRING CONTEXT. 
		AnnotationConfigApplicationContext						Context=new AnnotationConfigApplicationContext(CSpring2Configuration.class);

		System.out.println("CONTEXT CREATED !");

		// !!! Tento OBJECT NIE JE ulozeny v SPRING CONTEXT.
		CSpring2Message											Message=new CSpring2Message("HELLO WOLRD !!!");
		 
		CSpring2Printer											Bean=Context.getBean(CSpring2Printer.class);
		
		Bean.PrintMessage(Message);
		
		Context.close();
		
		CHelpers.PrintLineSeparator();
	}
//----------------------------------------------------------------------------------------------------------------------
	public static void TestSpringMultiImplementationPrimary()
	{
		CHelpers.PrintLineSeparator();

		System.out.println("CONTEXT CREATING !");

		// !!! Instancie SPRING BEANS sa vytvaraju uz pri vytvoreni SPRING CONTEXT. 
		AnnotationConfigApplicationContext						Context=new AnnotationConfigApplicationContext(CSpringMultiImplementationPrimaryConfiguration.class);

		System.out.println("CONTEXT CREATED !");

		// !!! Tento OBJECT NIE JE ulozeny v SPRING CONTEXT.
		CSpringMultiImplementationPrimaryMessage				Message=new CSpringMultiImplementationPrimaryMessage("HELLO WOLRD !!!");
		 
		CSpringMultiImplementationPrimaryPrinter				Bean=Context.getBean(CSpringMultiImplementationPrimaryPrinter.class);
		
		Bean.PrintMessage(Message);
		
		Context.close();
		
		CHelpers.PrintLineSeparator();
	}
//----------------------------------------------------------------------------------------------------------------------
	public static void TestSpringMultiImplementationQualifier()
	{
		CHelpers.PrintLineSeparator();

		System.out.println("CONTEXT CREATING !");

		// !!! Instancie SPRING BEANS sa vytvaraju uz pri vytvoreni SPRING CONTEXT. 
		AnnotationConfigApplicationContext						Context=new AnnotationConfigApplicationContext(CSpringMultiImplementationQualifierConfiguration.class);

		System.out.println("CONTEXT CREATED !");

		// !!! Tento OBJECT NIE JE ulozeny v SPRING CONTEXT.
		CSpringMultiImplementationQualifierMessage				Message1=new CSpringMultiImplementationQualifierMessage("HELLO WOLRD 111 !!!");
		 
		CSpringMultiImplementationQualifierPrinter1				Bean1=Context.getBean(CSpringMultiImplementationQualifierPrinter1.class);
		
		Bean1.PrintMessage(Message1);

		// !!! Tento OBJECT NIE JE ulozeny v SPRING CONTEXT.
		CSpringMultiImplementationQualifierMessage				Message2=new CSpringMultiImplementationQualifierMessage("HELLO WOLRD 222 !!!");
		 
		CSpringMultiImplementationQualifierPrinter2				Bean2=Context.getBean(CSpringMultiImplementationQualifierPrinter2.class);
		
		Bean2.PrintMessage(Message2);
		
		Context.close();
		
		CHelpers.PrintLineSeparator();
	}
//----------------------------------------------------------------------------------------------------------------------
	public static void TestSpringServiceRepository()
	{
		CHelpers.PrintLineSeparator();

		System.out.println("CONTEXT CREATING !");

		// !!! Instancie SPRING BEANS sa vytvaraju uz pri vytvoreni SPRING CONTEXT. 
		AnnotationConfigApplicationContext						Context=new AnnotationConfigApplicationContext(CSpringServiceRepositoryConfiguration.class);

		System.out.println("CONTEXT CREATED !");

		// !!! Tento OBJECT NIE JE ulozeny v SPRING CONTEXT.
		CSpringServiceRepositoryMessage							Message1=new CSpringServiceRepositoryMessage("HELLO WOLRD 111 !!!");
		 
		CSpringServiceRepositoryPrinter1						Bean1=Context.getBean(CSpringServiceRepositoryPrinter1.class);
		
		Bean1.PrintMessage(Message1);

		// !!! Tento OBJECT NIE JE ulozeny v SPRING CONTEXT.
		CSpringServiceRepositoryMessage							Message2=new CSpringServiceRepositoryMessage("HELLO WOLRD 222 !!!");
		 
		CSpringServiceRepositoryPrinter2						Bean2=Context.getBean(CSpringServiceRepositoryPrinter2.class);
		
		Bean2.PrintMessage(Message2);
		
		Context.close();
		
		CHelpers.PrintLineSeparator();
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	public static void main(String[] args)
	{
		//TestNoSpring();
		//TestSpring1();
		//TestSpring2();
		//TestSpringMultiImplementationPrimary();
		//TestSpringMultiImplementationQualifier();
		TestSpringServiceRepository();
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------