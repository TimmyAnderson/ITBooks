package my.example.Components;

import java.util.Arrays;
import java.util.List;

import org.springframework.beans.BeansException;
import org.springframework.boot.Banner;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.boot.builder.SpringApplicationBuilder;
import org.springframework.context.ConfigurableApplicationContext;

import my.example.Components.InsidePackage.CComponentWithCustomAnnotation;
import my.example.Components.InsidePackage.CInsidePackageComponent;
import my.example.Components.InsidePackage.CMyController;
import my.example.Components.InsidePackage.CMyRepository;
import my.example.Components.InsidePackage.CMyService;
import my.example.OutsidePackage.COutsidePackageComponent;
import my.example.Package1.CNonComponentPackage1Class;
import my.example.Package1.CPackage1Class;
import my.example.Package1.Inner.CPackageInner1Class;
import my.example.Package2.CPackage2Class;
import my.example.Package2.Inner.CPackageInner2Class;
import my.example.Package3.CPackage3Class;
import my.example.Package3.Inner.CPackageInner3Class;
//----------------------------------------------------------------------------------------------------------------------
@SpringBootApplication
public class ComponentsApplication
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
		SpringApplication.run(ComponentsApplication.class,args);
		
		System.out.println("METHOD END.");
	}
//----------------------------------------------------------------------------------------------------------------------
	private static void StartContainerByConstructor(String[] args)
	{
		System.out.println("METHOD START.");

		// !!! PARAMETER obsahuje TYPE CONFIGURATION CLASS.
		SpringApplication										springApplication=new SpringApplication(ComponentsApplication.class);
		
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
		SpringApplicationBuilder								springApplicationBuilde=new SpringApplicationBuilder(ComponentsApplication.class);

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
		SpringApplication										springApplication=new SpringApplication(ComponentsApplication.class);
		
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
			configurableApplicationContext.getBean(ComponentsApplication.class);

			System.out.printf("BEAN [%s] FOUND.\n","ComponentsApplication");
		}
		catch(BeansException E)
		{
			System.out.printf("BEAN [%s] NOT FOUND.\n","ComponentsApplication");
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
	private static void TestAddBeansByAnnotationComponent(String[] args)
	{
		PrintSeparator();

		System.out.println("METHOD START.");
		
		SpringApplication										springApplication=new SpringApplication(ComponentsApplication.class);

		springApplication.setBannerMode(Banner.Mode.OFF);
		springApplication.setLogStartupInfo(false);
		
		ConfigurableApplicationContext							configurableApplicationContext=springApplication.run(args);

		PrintSeparator();
		
		try
		{
			CMainPackageComponent								component=configurableApplicationContext.getBean(CMainPackageComponent.class);

			System.out.printf("BEAN [%s] FOUND.\n","CMainPackageComponent");	
			
			component.Print();
		}
		catch(BeansException E)
		{
			System.out.printf("BEAN [%s] NOT FOUND.\n","CMainPackageComponent");	
		}

		PrintSeparator();
		
		try
		{
			CInsidePackageComponent								component=configurableApplicationContext.getBean(CInsidePackageComponent.class);

			System.out.printf("BEAN [%s] FOUND.\n","CInsidePackageComponent");	
			
			component.Print();
		}
		catch(BeansException E)
		{
			System.out.printf("BEAN [%s] NOT FOUND.\n","CInsidePackageComponent");	
		}

		PrintSeparator();
		
		try
		{
			COutsidePackageComponent							component=configurableApplicationContext.getBean(COutsidePackageComponent.class);

			System.out.printf("BEAN [%s] FOUND.\n","COutsidePackageComponent");
			
			component.Print();
		}
		catch(BeansException E)
		{
			System.out.printf("BEAN [%s] NOT FOUND.\n","COutsidePackageComponent");	
		}

		PrintSeparator();
		
		System.out.println("METHOD END.");
		
		PrintSeparator();
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	private static void TestAddBeansByOtherAndCustomAnnotations(String[] args)
	{
		PrintSeparator();

		System.out.println("METHOD START.");
		
		SpringApplication										springApplication=new SpringApplication(ComponentsApplication.class);

		springApplication.setBannerMode(Banner.Mode.OFF);
		springApplication.setLogStartupInfo(false);
		
		ConfigurableApplicationContext							configurableApplicationContext=springApplication.run(args);

		PrintSeparator();
		
		try
		{
			CMyController										component=configurableApplicationContext.getBean(CMyController.class);

			System.out.printf("BEAN [%s] FOUND.\n","CMyController");	
			
			component.Print();
		}
		catch(BeansException E)
		{
			System.out.printf("BEAN [%s] NOT FOUND.\n","CMyController");	
		}

		PrintSeparator();
		
		try
		{
			CMyService											component=configurableApplicationContext.getBean(CMyService.class);

			System.out.printf("BEAN [%s] FOUND.\n","CMyService");
			
			component.Print();
		}
		catch(BeansException E)
		{
			System.out.printf("BEAN [%s] NOT FOUND.\n","CMyService");	
		}

		PrintSeparator();
		
		try
		{
			CMyRepository										component=configurableApplicationContext.getBean(CMyRepository.class);

			System.out.printf("BEAN [%s] FOUND.\n","CMyRepository");	
			
			component.Print();
		}
		catch(BeansException E)
		{
			System.out.printf("BEAN [%s] NOT FOUND.\n","CMyRepository");	
		}

		PrintSeparator();
		
		try
		{
			CComponentWithCustomAnnotation						component=configurableApplicationContext.getBean(CComponentWithCustomAnnotation.class);

			System.out.printf("BEAN [%s] FOUND.\n","CComponentWithCustomAnnotation");	
			
			component.Print();
		}
		catch(BeansException E)
		{
			System.out.printf("BEAN [%s] NOT FOUND.\n","CComponentWithCustomAnnotation");
		}
		
		PrintSeparator();
		
		System.out.println("METHOD END.");
		
		PrintSeparator();
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	private static void TestCustomMainConfigurationEmpty(String[] args)
	{
		PrintSeparator();

		System.out.println("METHOD START.");
		
		// !!!!! START CONFIGURATION NEMUSI byt oznacena pomocou ANNOTATION [@Configuration], alebo pomocou ANNOTATION [@Component]. Je to preto, lebo START CONFIGURATION je zasielana priamo do SPING BOOT bud do CONSTRUCTOR CLASS [SpringApplication], alebo do METHODS [SpringApplication.run()]. A tym padom JAVA AUTOMATICKY poklada START CONFIGURATION CLASS za CONFIGURATION CLASS, aj ked NIE je oznacena pomocou ANNOTATION [@Configuration], alebo pomocou ANNOTATION [@Component].
		SpringApplication										springApplication=new SpringApplication(CMyCustomMainConfigurationEmpty.class);
		
		springApplication.setBannerMode(Banner.Mode.OFF);
		springApplication.setLogStartupInfo(false);
		
		ConfigurableApplicationContext							configurableApplicationContext=springApplication.run(args);

		PrintSeparator();
		
		try
		{
			// !!!!! BEAN NIE JE najdeny, pretoze CUSTOM CONFIGURATION CLASS [CMyCustomMainConfigurationEmpty] NEMA aplikovanu ANNOTATION [@ComponentScan].
			CMyService											component=configurableApplicationContext.getBean(CMyService.class);

			System.out.printf("BEAN [%s] FOUND.\n","CMyService");
			
			component.Print();
		}
		catch(BeansException E)
		{
			System.out.printf("BEAN [%s] NOT FOUND.\n","CMyService");	
		}
		
		PrintSeparator();
		
		System.out.println("METHOD END.");
		
		PrintSeparator();
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	private static void TestCustomMainConfigurationWithComponentScan(String[] args)
	{
		PrintSeparator();

		System.out.println("METHOD START.");

		// !!!!! START CONFIGURATION NEMUSI byt oznacena pomocou ANNOTATION [@Configuration], alebo pomocou ANNOTATION [@Component]. Je to preto, lebo START CONFIGURATION je zasielana priamo do SPING BOOT bud do CONSTRUCTOR CLASS [SpringApplication], alebo do METHODS [SpringApplication.run()]. A tym padom JAVA AUTOMATICKY poklada START CONFIGURATION CLASS za CONFIGURATION CLASS, aj ked NIE je oznacena pomocou ANNOTATION [@Configuration], alebo pomocou ANNOTATION [@Component].
		SpringApplication										springApplication=new SpringApplication(CMyCustomMainConfigurationWithComponentScan.class);
		
		springApplication.setBannerMode(Banner.Mode.OFF);
		springApplication.setLogStartupInfo(false);
		
		ConfigurableApplicationContext							configurableApplicationContext=springApplication.run(args);

		PrintSeparator();
		
		try
		{
			// !!!!! BEAN je najdeny, pretoze CUSTOM CONFIGURATION CLASS [CMyCustomMainConfigurationWithComponentScan] MA aplikovanu ANNOTATION [@ComponentScan], ktora vykonava SCAN vsetkych BEANS v CURRENT PACKAGE a vsetkych CHILD PACKAGES..
			CMyService											component=configurableApplicationContext.getBean(CMyService.class);

			System.out.printf("BEAN [%s] FOUND.\n","CMyService");
			
			component.Print();
		}
		catch(BeansException E)
		{
			System.out.printf("BEAN [%s] NOT FOUND.\n","CMyService");	
		}
		
		PrintSeparator();
		
		System.out.println("METHOD END.");
		
		PrintSeparator();
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	private static void TestComponentScanBasePackages1(String[] args)
	{
		PrintSeparator();

		System.out.println("METHOD START.");

		PrintSeparator();

		SpringApplication										springApplication=new SpringApplication(CMyCustomMainConfigurationBasePackages1.class);
		
		springApplication.setBannerMode(Banner.Mode.OFF);
		springApplication.setLogStartupInfo(false);
		
		ConfigurableApplicationContext							configurableApplicationContext=springApplication.run(args);

		PrintSeparator();
	
		try
		{
			CPackage1Class										component=configurableApplicationContext.getBean(CPackage1Class.class);

			System.out.printf("BEAN [%s] FOUND.\n",CPackage1Class.class.getSimpleName());
			
			component.Print();
		}
		catch(BeansException E)
		{
			System.out.printf("BEAN [%s] NOT FOUND.\n",CPackage1Class.class.getSimpleName());	
		}

		PrintSeparator();
		
		try
		{
			CPackageInner1Class									component=configurableApplicationContext.getBean(CPackageInner1Class.class);

			System.out.printf("BEAN [%s] FOUND.\n",CPackageInner1Class.class.getSimpleName());
			
			component.Print();
		}
		catch(BeansException E)
		{
			System.out.printf("BEAN [%s] NOT FOUND.\n",CPackageInner1Class.class.getSimpleName());	
		}

		PrintSeparator();
		
		try
		{
			CPackage2Class										component=configurableApplicationContext.getBean(CPackage2Class.class);

			System.out.printf("BEAN [%s] FOUND.\n",CPackage2Class.class.getSimpleName());
			
			component.Print();
		}
		catch(BeansException E)
		{
			System.out.printf("BEAN [%s] NOT FOUND.\n",CPackage2Class.class.getSimpleName());	
		}

		PrintSeparator();
		
		try
		{
			CPackageInner2Class									component=configurableApplicationContext.getBean(CPackageInner2Class.class);

			System.out.printf("BEAN [%s] FOUND.\n",CPackageInner2Class.class.getSimpleName());
			
			component.Print();
		}
		catch(BeansException E)
		{
			System.out.printf("BEAN [%s] NOT FOUND.\n",CPackageInner2Class.class.getSimpleName());	
		}

		PrintSeparator();
		
		try
		{
			CPackage3Class										component=configurableApplicationContext.getBean(CPackage3Class.class);

			System.out.printf("BEAN [%s] FOUND.\n",CPackage3Class.class.getSimpleName());
			
			component.Print();
		}
		catch(BeansException E)
		{
			System.out.printf("BEAN [%s] NOT FOUND.\n",CPackage3Class.class.getSimpleName());	
		}

		PrintSeparator();
		
		try
		{
			CPackageInner3Class									component=configurableApplicationContext.getBean(CPackageInner3Class.class);

			System.out.printf("BEAN [%s] FOUND.\n",CPackageInner3Class.class.getSimpleName());
			
			component.Print();
		}
		catch(BeansException E)
		{
			System.out.printf("BEAN [%s] NOT FOUND.\n",CPackageInner3Class.class.getSimpleName());	
		}
		
		PrintSeparator();

		System.out.println("METHOD END.");
		
		PrintSeparator();
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	private static void TestComponentScanBasePackages2(String[] args)
	{
		PrintSeparator();

		System.out.println("METHOD START.");

		PrintSeparator();

		SpringApplication										springApplication=new SpringApplication(CMyCustomMainConfigurationBasePackages2.class);
		
		springApplication.setBannerMode(Banner.Mode.OFF);
		springApplication.setLogStartupInfo(false);
		
		ConfigurableApplicationContext							configurableApplicationContext=springApplication.run(args);

		PrintSeparator();
	
		try
		{
			CPackage1Class										component=configurableApplicationContext.getBean(CPackage1Class.class);

			System.out.printf("BEAN [%s] FOUND.\n",CPackage1Class.class.getSimpleName());
			
			component.Print();
		}
		catch(BeansException E)
		{
			System.out.printf("BEAN [%s] NOT FOUND.\n",CPackage1Class.class.getSimpleName());	
		}

		PrintSeparator();
		
		try
		{
			CPackageInner1Class									component=configurableApplicationContext.getBean(CPackageInner1Class.class);

			System.out.printf("BEAN [%s] FOUND.\n",CPackageInner1Class.class.getSimpleName());
			
			component.Print();
		}
		catch(BeansException E)
		{
			System.out.printf("BEAN [%s] NOT FOUND.\n",CPackageInner1Class.class.getSimpleName());	
		}

		PrintSeparator();
		
		try
		{
			CPackage2Class										component=configurableApplicationContext.getBean(CPackage2Class.class);

			System.out.printf("BEAN [%s] FOUND.\n",CPackage2Class.class.getSimpleName());
			
			component.Print();
		}
		catch(BeansException E)
		{
			System.out.printf("BEAN [%s] NOT FOUND.\n",CPackage2Class.class.getSimpleName());	
		}

		PrintSeparator();
		
		try
		{
			CPackageInner2Class									component=configurableApplicationContext.getBean(CPackageInner2Class.class);

			System.out.printf("BEAN [%s] FOUND.\n",CPackageInner2Class.class.getSimpleName());
			
			component.Print();
		}
		catch(BeansException E)
		{
			System.out.printf("BEAN [%s] NOT FOUND.\n",CPackageInner2Class.class.getSimpleName());	
		}

		PrintSeparator();
		
		try
		{
			CPackage3Class										component=configurableApplicationContext.getBean(CPackage3Class.class);

			System.out.printf("BEAN [%s] FOUND.\n",CPackage3Class.class.getSimpleName());
			
			component.Print();
		}
		catch(BeansException E)
		{
			System.out.printf("BEAN [%s] NOT FOUND.\n",CPackage3Class.class.getSimpleName());	
		}

		PrintSeparator();
		
		try
		{
			CPackageInner3Class									component=configurableApplicationContext.getBean(CPackageInner3Class.class);

			System.out.printf("BEAN [%s] FOUND.\n",CPackageInner3Class.class.getSimpleName());
			
			component.Print();
		}
		catch(BeansException E)
		{
			System.out.printf("BEAN [%s] NOT FOUND.\n",CPackageInner3Class.class.getSimpleName());	
		}
		
		PrintSeparator();

		System.out.println("METHOD END.");
		
		PrintSeparator();
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	private static void TestComponentScanBasePackageClasses(String[] args)
	{
		PrintSeparator();

		System.out.println("METHOD START.");

		PrintSeparator();

		SpringApplication										springApplication=new SpringApplication(CMyCustomMainConfigurationBasePackageClasses.class);
		
		springApplication.setBannerMode(Banner.Mode.OFF);
		springApplication.setLogStartupInfo(false);
		
		ConfigurableApplicationContext							configurableApplicationContext=springApplication.run(args);

		PrintSeparator();
	
		try
		{
			CPackage1Class										component=configurableApplicationContext.getBean(CPackage1Class.class);

			System.out.printf("BEAN [%s] FOUND.\n",CPackage1Class.class.getSimpleName());
			
			component.Print();
		}
		catch(BeansException E)
		{
			System.out.printf("BEAN [%s] NOT FOUND.\n",CPackage1Class.class.getSimpleName());	
		}

		PrintSeparator();
		
		try
		{
			CPackageInner1Class									component=configurableApplicationContext.getBean(CPackageInner1Class.class);

			System.out.printf("BEAN [%s] FOUND.\n",CPackageInner1Class.class.getSimpleName());
			
			component.Print();
		}
		catch(BeansException E)
		{
			System.out.printf("BEAN [%s] NOT FOUND.\n",CPackageInner1Class.class.getSimpleName());	
		}

		PrintSeparator();
		
		try
		{
			CPackage2Class										component=configurableApplicationContext.getBean(CPackage2Class.class);

			System.out.printf("BEAN [%s] FOUND.\n",CPackage2Class.class.getSimpleName());
			
			component.Print();
		}
		catch(BeansException E)
		{
			System.out.printf("BEAN [%s] NOT FOUND.\n",CPackage2Class.class.getSimpleName());	
		}

		PrintSeparator();
		
		try
		{
			CPackageInner2Class									component=configurableApplicationContext.getBean(CPackageInner2Class.class);

			System.out.printf("BEAN [%s] FOUND.\n",CPackageInner2Class.class.getSimpleName());
			
			component.Print();
		}
		catch(BeansException E)
		{
			System.out.printf("BEAN [%s] NOT FOUND.\n",CPackageInner2Class.class.getSimpleName());	
		}

		PrintSeparator();
		
		try
		{
			CPackage3Class										component=configurableApplicationContext.getBean(CPackage3Class.class);

			System.out.printf("BEAN [%s] FOUND.\n",CPackage3Class.class.getSimpleName());
			
			component.Print();
		}
		catch(BeansException E)
		{
			System.out.printf("BEAN [%s] NOT FOUND.\n",CPackage3Class.class.getSimpleName());	
		}

		PrintSeparator();
		
		try
		{
			CPackageInner3Class									component=configurableApplicationContext.getBean(CPackageInner3Class.class);

			System.out.printf("BEAN [%s] FOUND.\n",CPackageInner3Class.class.getSimpleName());
			
			component.Print();
		}
		catch(BeansException E)
		{
			System.out.printf("BEAN [%s] NOT FOUND.\n",CPackageInner3Class.class.getSimpleName());	
		}
		
		PrintSeparator();

		System.out.println("METHOD END.");
		
		PrintSeparator();
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	private static void TestComponentScanIncludeFilters(String[] args)
	{
		PrintSeparator();

		System.out.println("METHOD START.");

		PrintSeparator();

		SpringApplication										springApplication=new SpringApplication(CMyCustomMainConfigurationIncludeFilters.class);
		
		springApplication.setBannerMode(Banner.Mode.OFF);
		springApplication.setLogStartupInfo(false);
		
		ConfigurableApplicationContext							configurableApplicationContext=springApplication.run(args);

		PrintSeparator();
	
		try
		{
			CPackage1Class										component=configurableApplicationContext.getBean(CPackage1Class.class);

			System.out.printf("BEAN [%s] FOUND.\n",CPackage1Class.class.getSimpleName());
			
			component.Print();
		}
		catch(BeansException E)
		{
			System.out.printf("BEAN [%s] NOT FOUND.\n",CPackage1Class.class.getSimpleName());	
		}

		PrintSeparator();
		
		try
		{
			// !!!!! BEAN NIE JE NAJDENY, pretoze NESPLNA FILTER CONDITIONS.
			CPackageInner1Class									component=configurableApplicationContext.getBean(CPackageInner1Class.class);

			System.out.printf("BEAN [%s] FOUND.\n",CPackageInner1Class.class.getSimpleName());
			
			component.Print();
		}
		catch(BeansException E)
		{
			System.out.printf("BEAN [%s] NOT FOUND.\n",CPackageInner1Class.class.getSimpleName());	
		}

		PrintSeparator();

		try
		{
			// !!!!! CLASS NIE je oznacena pomocou ANNOTATION [@Component], ale aj tak je zavedena ako BEAN, pretoze je explicitne vymenovana v ELEMENT [includeFilters].
			CNonComponentPackage1Class									component=configurableApplicationContext.getBean(CNonComponentPackage1Class.class);

			System.out.printf("BEAN [%s] FOUND.\n",CNonComponentPackage1Class.class.getSimpleName());
			
			component.Print();
		}
		catch(BeansException E)
		{
			System.out.printf("BEAN [%s] NOT FOUND.\n",CNonComponentPackage1Class.class.getSimpleName());	
		}
		
		PrintSeparator();
		
		try
		{
			CPackage2Class										component=configurableApplicationContext.getBean(CPackage2Class.class);

			System.out.printf("BEAN [%s] FOUND.\n",CPackage2Class.class.getSimpleName());
			
			component.Print();
		}
		catch(BeansException E)
		{
			System.out.printf("BEAN [%s] NOT FOUND.\n",CPackage2Class.class.getSimpleName());	
		}

		PrintSeparator();
		
		try
		{
			// !!!!! BEAN NIE JE NAJDENY, pretoze NESPLNA FILTER CONDITIONS.
			CPackageInner2Class									component=configurableApplicationContext.getBean(CPackageInner2Class.class);

			System.out.printf("BEAN [%s] FOUND.\n",CPackageInner2Class.class.getSimpleName());
			
			component.Print();
		}
		catch(BeansException E)
		{
			System.out.printf("BEAN [%s] NOT FOUND.\n",CPackageInner2Class.class.getSimpleName());	
		}

		PrintSeparator();
		
		try
		{
			// !!!!! BEAN NIE JE NAJDENY, pretoze PACKAGE [my.example.Package3] NIE je vobec prehladavany.
			CPackage3Class										component=configurableApplicationContext.getBean(CPackage3Class.class);

			System.out.printf("BEAN [%s] FOUND.\n",CPackage3Class.class.getSimpleName());
			
			component.Print();
		}
		catch(BeansException E)
		{
			System.out.printf("BEAN [%s] NOT FOUND.\n",CPackage3Class.class.getSimpleName());	
		}

		PrintSeparator();
		
		try
		{
			// !!!!! BEAN NIE JE NAJDENY, pretoze PACKAGE [my.example.Package3] NIE je vobec prehladavany.
			CPackageInner3Class									component=configurableApplicationContext.getBean(CPackageInner3Class.class);

			System.out.printf("BEAN [%s] FOUND.\n",CPackageInner3Class.class.getSimpleName());
			
			component.Print();
		}
		catch(BeansException E)
		{
			System.out.printf("BEAN [%s] NOT FOUND.\n",CPackageInner3Class.class.getSimpleName());	
		}
		
		PrintSeparator();

		System.out.println("METHOD END.");
		
		PrintSeparator();
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	private static void TestComponentScanExcludeFilters(String[] args)
	{
		PrintSeparator();

		System.out.println("METHOD START.");

		PrintSeparator();

		SpringApplication										springApplication=new SpringApplication(CMyCustomMainConfigurationExcludeFilters.class);
		
		springApplication.setBannerMode(Banner.Mode.OFF);
		springApplication.setLogStartupInfo(false);
		
		ConfigurableApplicationContext							configurableApplicationContext=springApplication.run(args);

		PrintSeparator();
	
		try
		{
			CPackage1Class										component=configurableApplicationContext.getBean(CPackage1Class.class);

			System.out.printf("BEAN [%s] FOUND.\n",CPackage1Class.class.getSimpleName());
			
			component.Print();
		}
		catch(BeansException E)
		{
			System.out.printf("BEAN [%s] NOT FOUND.\n",CPackage1Class.class.getSimpleName());	
		}

		PrintSeparator();
		
		try
		{
			// !!!!! BEAN NIE je NAJDENY, pretoze EXCLUDE FILTER vyradzuje CLASSES, ktore su oznacene pomocou ANNOTATION [@IMyComponentScanAnnotation] a tato CLASS je touto ANNOTATION oznacena. 
			CPackageInner1Class									component=configurableApplicationContext.getBean(CPackageInner1Class.class);

			System.out.printf("BEAN [%s] FOUND.\n",CPackageInner1Class.class.getSimpleName());
			
			component.Print();
		}
		catch(BeansException E)
		{
			System.out.printf("BEAN [%s] NOT FOUND.\n",CPackageInner1Class.class.getSimpleName());	
		}

		PrintSeparator();

		try
		{
			// !!!!! BEAN NIE JE NAJDENY, pretoze nan NIE je aplikovana ANNONTATION [@Component], ani ziadna z jej CHILD ANNOTATIONS.
			CNonComponentPackage1Class									component=configurableApplicationContext.getBean(CNonComponentPackage1Class.class);

			System.out.printf("BEAN [%s] FOUND.\n",CNonComponentPackage1Class.class.getSimpleName());
			
			component.Print();
		}
		catch(BeansException E)
		{
			System.out.printf("BEAN [%s] NOT FOUND.\n",CNonComponentPackage1Class.class.getSimpleName());	
		}
		
		PrintSeparator();
		
		try
		{
			// !!!!! BEAN NIE je NAJDENY, pretoze EXCLUDE FILTER vyradzuje CLASSES, ktore su oznacene pomocou ANNOTATION [@IMyComponentScanAnnotation] a tato CLASS je touto ANNOTATION oznacena. 
			CPackage2Class										component=configurableApplicationContext.getBean(CPackage2Class.class);

			System.out.printf("BEAN [%s] FOUND.\n",CPackage2Class.class.getSimpleName());
			
			component.Print();
		}
		catch(BeansException E)
		{
			System.out.printf("BEAN [%s] NOT FOUND.\n",CPackage2Class.class.getSimpleName());	
		}

		PrintSeparator();
		
		try
		{
			CPackageInner2Class									component=configurableApplicationContext.getBean(CPackageInner2Class.class);

			System.out.printf("BEAN [%s] FOUND.\n",CPackageInner2Class.class.getSimpleName());
			
			component.Print();
		}
		catch(BeansException E)
		{
			System.out.printf("BEAN [%s] NOT FOUND.\n",CPackageInner2Class.class.getSimpleName());	
		}

		PrintSeparator();
		
		try
		{
			// !!!!! BEAN NIE JE NAJDENY, pretoze PACKAGE [my.example.Package3] NIE je vobec prehladavany.
			CPackage3Class										component=configurableApplicationContext.getBean(CPackage3Class.class);

			System.out.printf("BEAN [%s] FOUND.\n",CPackage3Class.class.getSimpleName());
			
			component.Print();
		}
		catch(BeansException E)
		{
			System.out.printf("BEAN [%s] NOT FOUND.\n",CPackage3Class.class.getSimpleName());	
		}

		PrintSeparator();
		
		try
		{
			// !!!!! BEAN NIE JE NAJDENY, pretoze PACKAGE [my.example.Package3] NIE je vobec prehladavany.
			CPackageInner3Class									component=configurableApplicationContext.getBean(CPackageInner3Class.class);

			System.out.printf("BEAN [%s] FOUND.\n",CPackageInner3Class.class.getSimpleName());
			
			component.Print();
		}
		catch(BeansException E)
		{
			System.out.printf("BEAN [%s] NOT FOUND.\n",CPackageInner3Class.class.getSimpleName());	
		}
		
		PrintSeparator();

		System.out.println("METHOD END.");
		
		PrintSeparator();
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	private static void TestComponentScanCustomFilters(String[] args)
	{
		PrintSeparator();

		System.out.println("METHOD START.");

		PrintSeparator();

		SpringApplication										springApplication=new SpringApplication(CMyCustomMainConfigurationCustomFilter.class);
		
		springApplication.setBannerMode(Banner.Mode.OFF);
		springApplication.setLogStartupInfo(false);
		
		ConfigurableApplicationContext							configurableApplicationContext=springApplication.run(args);

		PrintSeparator();
	
		try
		{
			// !!!!! BEAN NIE je najdeny, lebo CLASS NAME NEOBSAHUJE VALUE [2Class], ktoru vyzaduje CUSTOM FILTER. 
			CPackage1Class										component=configurableApplicationContext.getBean(CPackage1Class.class);

			System.out.printf("BEAN [%s] FOUND.\n",CPackage1Class.class.getSimpleName());
			
			component.Print();
		}
		catch(BeansException E)
		{
			System.out.printf("BEAN [%s] NOT FOUND.\n",CPackage1Class.class.getSimpleName());	
		}

		PrintSeparator();
		
		try
		{
			// !!!!! BEAN NIE je najdeny, lebo CLASS NAME NEOBSAHUJE VALUE [2Class], ktoru vyzaduje CUSTOM FILTER. 
			CPackageInner1Class									component=configurableApplicationContext.getBean(CPackageInner1Class.class);

			System.out.printf("BEAN [%s] FOUND.\n",CPackageInner1Class.class.getSimpleName());
			
			component.Print();
		}
		catch(BeansException E)
		{
			System.out.printf("BEAN [%s] NOT FOUND.\n",CPackageInner1Class.class.getSimpleName());	
		}

		PrintSeparator();

		try
		{
			// !!!!! BEAN NIE je najdeny, lebo CLASS NAME NEOBSAHUJE VALUE [2Class], ktoru vyzaduje CUSTOM FILTER. 
			CNonComponentPackage1Class									component=configurableApplicationContext.getBean(CNonComponentPackage1Class.class);

			System.out.printf("BEAN [%s] FOUND.\n",CNonComponentPackage1Class.class.getSimpleName());
			
			component.Print();
		}
		catch(BeansException E)
		{
			System.out.printf("BEAN [%s] NOT FOUND.\n",CNonComponentPackage1Class.class.getSimpleName());	
		}
		
		PrintSeparator();
		
		try
		{
			// !!!!! BEAN je najdeny, lebo CLASS NAME obsahuje VALUE [2Class], ktoru vyzaduje CUSTOM FILTER. 
			CPackage2Class										component=configurableApplicationContext.getBean(CPackage2Class.class);

			System.out.printf("BEAN [%s] FOUND.\n",CPackage2Class.class.getSimpleName());
			
			component.Print();
		}
		catch(BeansException E)
		{
			System.out.printf("BEAN [%s] NOT FOUND.\n",CPackage2Class.class.getSimpleName());	
		}

		PrintSeparator();
		
		try
		{
			// !!!!! BEAN je najdeny, lebo CLASS NAME obsahuje VALUE [2Class], ktoru vyzaduje CUSTOM FILTER. 
			CPackageInner2Class									component=configurableApplicationContext.getBean(CPackageInner2Class.class);

			System.out.printf("BEAN [%s] FOUND.\n",CPackageInner2Class.class.getSimpleName());
			
			component.Print();
		}
		catch(BeansException E)
		{
			System.out.printf("BEAN [%s] NOT FOUND.\n",CPackageInner2Class.class.getSimpleName());	
		}

		PrintSeparator();
		
		try
		{
			// !!!!! BEAN NIE JE NAJDENY, pretoze PACKAGE [my.example.Package3] NIE je vobec prehladavany.
			CPackage3Class										component=configurableApplicationContext.getBean(CPackage3Class.class);

			System.out.printf("BEAN [%s] FOUND.\n",CPackage3Class.class.getSimpleName());
			
			component.Print();
		}
		catch(BeansException E)
		{
			System.out.printf("BEAN [%s] NOT FOUND.\n",CPackage3Class.class.getSimpleName());	
		}

		PrintSeparator();
		
		try
		{
			// !!!!! BEAN NIE JE NAJDENY, pretoze PACKAGE [my.example.Package3] NIE je vobec prehladavany.
			CPackageInner3Class									component=configurableApplicationContext.getBean(CPackageInner3Class.class);

			System.out.printf("BEAN [%s] FOUND.\n",CPackageInner3Class.class.getSimpleName());
			
			component.Print();
		}
		catch(BeansException E)
		{
			System.out.printf("BEAN [%s] NOT FOUND.\n",CPackageInner3Class.class.getSimpleName());	
		}
		
		PrintSeparator();

		System.out.println("METHOD END.");
		
		PrintSeparator();
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
		//TestConfigurableApplicationContext(args);
		//TestAddBeansByAnnotationComponent(args);
		//TestAddBeansByOtherAndCustomAnnotations(args);
		//TestCustomMainConfigurationEmpty(args);
		//TestCustomMainConfigurationWithComponentScan(args);
		//TestComponentScanBasePackages1(args);
		//TestComponentScanBasePackages2(args);
		//TestComponentScanBasePackageClasses(args);
		//TestComponentScanIncludeFilters(args);
		//TestComponentScanExcludeFilters(args);
		TestComponentScanCustomFilters(args);
		
		System.out.println("MAIN END.");
		
		PrintSeparator();
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------