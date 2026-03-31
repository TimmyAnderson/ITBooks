package my.example.ContainersAndBeans;

import java.util.Arrays;
import java.util.List;

import org.springframework.beans.BeansException;
import org.springframework.boot.Banner;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.boot.builder.SpringApplicationBuilder;
import org.springframework.context.ConfigurableApplicationContext;
//----------------------------------------------------------------------------------------------------------------------
@SpringBootApplication
public class ContainersAndBeansApplication
{
//----------------------------------------------------------------------------------------------------------------------
	private static void PrintSeparator()
	{
		System.out.println("--------------------------------------------------------------------------------");
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	private static void StartContainerByStaticRunMethod(String[] args)
	{
		System.out.println("METHOD START.");
		
		// !!! 1. PARAMETER obsahuje TYPE CONFIGURATION CLASS.
		// !!! 2. PARAMETER obsahuje COMMAND LINE PARAMETERS.
		SpringApplication.run(ContainersAndBeansApplication.class,args);
		
		System.out.println("METHOD END.");
	}
//----------------------------------------------------------------------------------------------------------------------
	private static void StartContainerByConstructor(String[] args)
	{
		System.out.println("METHOD START.");

		// !!! PARAMETER obsahuje TYPE CONFIGURATION CLASS.
		SpringApplication										springApplication=new SpringApplication(ContainersAndBeansApplication.class);
		
		// !!! METHOD nastavi MODE, ktory umoznuje spustanie GUI PROGRAMS.
		springApplication.setHeadless(false);
		
		// !!! Vypne sa zobrazenie BANNER.
		springApplication.setBannerMode(Banner.Mode.OFF);
		
		// !!! Vypnu sa STARTUP LOGS.
		springApplication.setLogStartupInfo(false);
	
		// !!! PARAMETER obsahuje COMMAND LINE PARAMETERS.
		// !!! Spusti sa SPRING CONTAINER.
		springApplication.run(args);
		
		System.out.println("METHOD END.");
	}	
//----------------------------------------------------------------------------------------------------------------------
	private static void StartContainerBySpringApplicationBuilder(String[] args)
	{
		System.out.println("METHOD START.");

		// !!! PARAMETER obsahuje TYPE CONFIGURATION CLASS.
		SpringApplicationBuilder								springApplicationBuilde=new SpringApplicationBuilder(ContainersAndBeansApplication.class);

		// !!! METHOD nastavi MODE, ktory umoznuje spustanie GUI PROGRAMS.
		springApplicationBuilde.headless(false);
		
		// !!! Vypne sa zobrazenie BANNER.
		springApplicationBuilde.bannerMode(Banner.Mode.OFF);
		
		// !!! Vypnu sa STARTUP LOGS.
		springApplicationBuilde.logStartupInfo(false);
		
		System.out.println("METHOD END.");
	}
//----------------------------------------------------------------------------------------------------------------------
	private static void TestConfigurableApplicationContext(String[] args)
	{
		System.out.println("METHOD START.");

		// !!! PARAMETER obsahuje TYPE CONFIGURATION CLASS.
		SpringApplication										springApplication=new SpringApplication(ContainersAndBeansApplication.class);
		
		// !!! METHOD nastavi MODE, ktory umoznuje spustanie GUI PROGRAMS.
		springApplication.setHeadless(false);
		
		// !!! Vypne sa zobrazenie BANNER.
		springApplication.setBannerMode(Banner.Mode.OFF);
		
		// !!! Vypnu sa STARTUP LOGS.
		springApplication.setLogStartupInfo(false);
	
		// !!! PARAMETER obsahuje COMMAND LINE PARAMETERS.
		// !!! Spusti sa SPRING CONTAINER.
		ConfigurableApplicationContext							configurableApplicationContext=springApplication.run(args);

		String[]												beanNames=configurableApplicationContext.getBeanDefinitionNames();
		List<String>											sortedBeanNames=Arrays.stream(beanNames).sorted().toList();
		
		for(String sortedBeanName : sortedBeanNames)
		{
			System.out.printf("BEAN [%s].\n",sortedBeanName);	
		}
		
		System.out.println();
		
		try
		{
			// !!! Ziskanie BEAN pomocou TYPE.
			configurableApplicationContext.getBean(ContainersAndBeansApplication.class);

			System.out.printf("BEAN [%s] FOUND.\n","ContainersAndBeansApplication");	
		}
		catch(BeansException E)
		{
			System.out.printf("BEAN [%s] NOT FOUND.\n","ContainersAndBeansApplication");	
		}

		System.out.println();
		
		try
		{
			// !!! Ziskanie BEAN pomocou NAME.
			configurableApplicationContext.getBean("simpleAsyncTaskSchedulerBuilder");

			System.out.printf("BEAN [%s] FOUND.\n","simpleAsyncTaskSchedulerBuilder");	
		}
		catch(BeansException E)
		{
			System.out.printf("BEAN [%s] NOT FOUND.\n","simpleAsyncTaskSchedulerBuilder");	
		}
		
		System.out.println("METHOD END.");
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	public static void main(String[] args)
	{
		PrintSeparator();
		System.out.println("MAIN START.");
		
		//StartContainerByStaticRunMethod(args);
		//StartContainerByConstructor(args);
		//StartContainerBySpringApplicationBuilder(args);
		TestConfigurableApplicationContext(args);
		
		System.out.println("MAIN END.");
		PrintSeparator();
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------