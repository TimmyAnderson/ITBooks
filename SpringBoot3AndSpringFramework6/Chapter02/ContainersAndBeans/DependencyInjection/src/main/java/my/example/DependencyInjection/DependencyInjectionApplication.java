package my.example.DependencyInjection;
//----------------------------------------------------------------------------------------------------------------------
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import org.springframework.boot.autoconfigure.EnableAutoConfiguration;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.boot.autoconfigure.context.MessageSourceAutoConfiguration;
import org.springframework.boot.builder.SpringApplicationBuilder;
import org.springframework.beans.BeansException;
import org.springframework.beans.factory.BeanFactory;
import org.springframework.beans.factory.ListableBeanFactory;
import org.springframework.beans.factory.config.ConfigurableListableBeanFactory;
import org.springframework.boot.Banner;
import org.springframework.boot.SpringApplication;

import org.springframework.context.ConfigurableApplicationContext;
import org.springframework.context.annotation.AnnotationConfigApplicationContext;
import org.springframework.context.expression.BeanFactoryResolver;
import org.springframework.expression.EvaluationException;
import org.springframework.expression.Expression;
import org.springframework.expression.ExpressionParser;
import org.springframework.expression.ParseException;
import org.springframework.expression.spel.standard.SpelExpressionParser;
import org.springframework.expression.spel.support.StandardEvaluationContext;

import my.example.AutoConfigurationBeans.CAutoConfigurationBeansComponent;
import my.example.BaseTypesBeans.CBaseTypesBeansComponent;
import my.example.BeanInitializationProblem.CBeanInitializationProblemComponent;
import my.example.BeanInjectionPoints.CBeanInjectionPointsComponent;
import my.example.BeanNamesConflict.CBeanNamesConflictBean;
import my.example.BeanPostProcessors.CBeanPostProcessorsComponent;
import my.example.BeanPostProcessors.CBeanPostProcessorsPostProcessor3;
import my.example.BeanPostProcessors.CBeanPostProcessorsPostProcessor4;
import my.example.BeanQualifiers.CBeanQualifiersTestClass;
import my.example.BeansFactoryMethods.CBeansFactoryMethodsBean1;
import my.example.BeansFactoryMethods.CBeansFactoryMethodsBean2;
import my.example.BeansFactoryMethods.CBeansFactoryMethodsBeanWithDependencies;
import my.example.CacheableBeans.CCacheableBeansComponent;
import my.example.CollectionBeans.CCollectionBeansComponent;
import my.example.ConditionalBeans.CConditionalBeansComponent;
import my.example.ConditionalOnExpressionBeans.CConditionalOnExpressionBeansComponent;
import my.example.ConditionalOnMissingBeanBeans.CConditionalOnMissingBeanBeansComponent;
import my.example.ConditionalOnPropertyBeans.CConditionalOnPropertyBeansComponent;
import my.example.CyclicDependencies.CCyclicDependenciesLazyBean1;
import my.example.CyclicDependencies.CCyclicDependenciesLazyBean2;
import my.example.CyclicDependencies.CCyclicDependenciesLazyComponent;
import my.example.CyclicDependencies.CCyclicDependenciesSettersComponent;
import my.example.DependsOnBeans.CDependsOnBeansComponent;
import my.example.FallbackMatchInjection.CFallbackMatchInjectionComponent;
import my.example.GenericTypesBeans.CGenericTypesBeansTestBean;
import my.example.HierarchicalContexts.Child1.CHierarchicalContextsChild1Component;
import my.example.HierarchicalContexts.Child1.CHierarchicalContextsChild1Configuration;
import my.example.HierarchicalContexts.Child2.CHierarchicalContextsChild2Component;
import my.example.HierarchicalContexts.Child2.CHierarchicalContextsChild2Configuration;
import my.example.HierarchicalContexts.Parent.CHierarchicalContextsParentComponent;
import my.example.HierarchicalContexts.Parent.CHierarchicalContextsParentConfiguration;
import my.example.ImportConfigurations1.CImportConfigurations1Bean;
import my.example.ImportConfigurations1.CImportConfigurations1Component;
import my.example.ImportConfigurations2.CImportConfigurations2Bean;
import my.example.ImportConfigurations2.CImportConfigurations2Component;
import my.example.ImportConfigurations3.CImportConfigurations3Bean;
import my.example.ImportConfigurations3.CImportConfigurations3Component;
import my.example.InheritanceAutowired.CInheritanceAutowiredComponentDerived;
import my.example.InheritanceBeans.CInheritanceBeansComponent;
import my.example.InheritanceComponents.CInheritanceComponentsComponent;
import my.example.InjectionTypes.CInjectionTypesConstructorInjection;
import my.example.InjectionTypes.CInjectionTypesConstructorInjectionNotAutowired;
import my.example.InjectionTypes.CInjectionTypesFieldInjection;
import my.example.InjectionTypes.CInjectionTypesMultipleDependencies;
import my.example.InjectionTypes.CInjectionTypesPrivateMembers;
import my.example.InjectionTypes.CInjectionTypesSetterInjection;
import my.example.LazyBeans.CLazyBeansEagerComponent;
import my.example.LazyBeans.CLazyBeansLazyComponent;
import my.example.LifecycleEventsAnnotations.CLifecycleEventsAnnotationsComponent;
import my.example.LifecycleEventsInterfaces.CLifecycleEventsInterfacesComponent;
import my.example.ListableBeanFactory.CListableBeanFactoryBean1;
import my.example.ListableBeanFactory.CListableBeanFactoryBean2;
import my.example.ListableBeanFactory.CListableBeanFactoryBean3;
import my.example.ListableBeanFactory.IListableBeanFactoryAnnotation2;
import my.example.ListableBeanFactory.IListableBeanFactoryInterface;
import my.example.ManualRegisteringBeans.CManualRegisteringBeansComponent;
import my.example.MissingBeans.CMissingBeansComponent;
import my.example.MultipleSameTypeBeans.CMultipleSameTypeBeansBean;
import my.example.NamedBeans.CNamedBeansBean;
import my.example.NamedBeans.CNamedBeansComponentCustomName;
import my.example.NamedBeans.CNamedBeansComponentDefaultName;
import my.example.NonBeansInjection.CNonBeansInjectionComponent;
import my.example.ObjectProviders.CObjectProvidersComponent;
import my.example.OptionalBeans.COptionalBeansComponent;
import my.example.OrderedBeans.COrderedBeansComponent;
import my.example.PrimaryBeans.CPrimaryBeansComponent;
import my.example.ProxyTypes.CProxyTypesComponentBean;
import my.example.ProxyTypes.CProxyTypesRandomValueBean1;
import my.example.ProxyTypes.CProxyTypesRandomValueBean2;
import my.example.ProxyTypes.CProxyTypesRandomValueBean3;
import my.example.ProxyTypes.CProxyTypesRandomValueNoProxyBean1;
import my.example.ProxyTypes.CProxyTypesRandomValueNoProxyBean2;
import my.example.ResourceAnnotations.CResourceAnnotationsComponent;
import my.example.ScheduledBeans.CScheduledBeansComponent;
import my.example.StaticFactoryMethods.CStaticFactoryMethodsComponent;
import my.example.VariousBeans.CVariousBeansFactoryComponent;
//----------------------------------------------------------------------------------------------------------------------
@SpringBootApplication
// !!! ANNOTATION [@EnableAutoConfiguration] umoznuje zablokovat niektore AUTOCONFIGURATION BEANS.
@EnableAutoConfiguration(exclude={MessageSourceAutoConfiguration.class}) 
public class DependencyInjectionApplication
{
//----------------------------------------------------------------------------------------------------------------------
	private static void PrintSeparator()
	{
		System.out.println("--------------------------------------------------------------------------------");
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	private static void TestInjectionTypes(String[] args)
	{
		PrintSeparator();

		System.out.println("METHOD START.");

		PrintSeparator();

		SpringApplication										springApplication=new SpringApplication(CInjectionTypesConfiguration.class);
		
		springApplication.setBannerMode(Banner.Mode.OFF);
		springApplication.setLogStartupInfo(false);
		
		ConfigurableApplicationContext							configurableApplicationContext=springApplication.run(args);

		PrintSeparator();
		
		try
		{
			CInjectionTypesConstructorInjection					component=configurableApplicationContext.getBean(CInjectionTypesConstructorInjection.class);

			System.out.printf("BEAN [%s] FOUND.\n",CInjectionTypesConstructorInjection.class.getSimpleName());
			
			component.Test();
		}
		catch(BeansException E)
		{
			System.out.printf("BEAN [%s] NOT FOUND.\n",CInjectionTypesConstructorInjection.class.getSimpleName());	
		}

		PrintSeparator();
		
		try
		{
			CInjectionTypesConstructorInjectionNotAutowired		component=configurableApplicationContext.getBean(CInjectionTypesConstructorInjectionNotAutowired.class);

			System.out.printf("BEAN [%s] FOUND.\n",CInjectionTypesConstructorInjectionNotAutowired.class.getSimpleName());
			
			component.Test();
		}
		catch(BeansException E)
		{
			System.out.printf("BEAN [%s] NOT FOUND.\n",CInjectionTypesConstructorInjectionNotAutowired.class.getSimpleName());	
		}
		
		PrintSeparator();
		
		try
		{
			CInjectionTypesSetterInjection						component=configurableApplicationContext.getBean(CInjectionTypesSetterInjection.class);

			System.out.printf("BEAN [%s] FOUND.\n",CInjectionTypesSetterInjection.class.getSimpleName());
			
			component.Test();
		}
		catch(BeansException E)
		{
			System.out.printf("BEAN [%s] NOT FOUND.\n",CInjectionTypesSetterInjection.class.getSimpleName());	
		}

		PrintSeparator();
		
		try
		{
			CInjectionTypesFieldInjection						component=configurableApplicationContext.getBean(CInjectionTypesFieldInjection.class);

			System.out.printf("BEAN [%s] FOUND.\n",CInjectionTypesFieldInjection.class.getSimpleName());
			
			component.Test();
			
			component.TestStatic();
		}
		catch(BeansException E)
		{
			System.out.printf("BEAN [%s] NOT FOUND.\n",CInjectionTypesFieldInjection.class.getSimpleName());	
		}
		
		PrintSeparator();
		
		try
		{
			CInjectionTypesPrivateMembers						component=configurableApplicationContext.getBean(CInjectionTypesPrivateMembers.class);

			System.out.printf("BEAN [%s] FOUND.\n",CInjectionTypesPrivateMembers.class.getSimpleName());
			
			component.Test();
		}
		catch(BeansException E)
		{
			System.out.printf("BEAN [%s] NOT FOUND.\n",CInjectionTypesPrivateMembers.class.getSimpleName());	
		}
		
		PrintSeparator();
		
		try
		{
			CInjectionTypesMultipleDependencies					component=configurableApplicationContext.getBean(CInjectionTypesMultipleDependencies.class);

			System.out.printf("BEAN [%s] FOUND.\n",CInjectionTypesMultipleDependencies.class.getSimpleName());
			
			component.Test();
		}
		catch(BeansException E)
		{
			System.out.printf("BEAN [%s] NOT FOUND.\n",CInjectionTypesMultipleDependencies.class.getSimpleName());	
		}
		
		PrintSeparator();

		System.out.println("METHOD END.");
		
		PrintSeparator();
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	private static void TestMissingBeans(String[] args)
	{
		PrintSeparator();

		System.out.println("METHOD START.");

		PrintSeparator();

		SpringApplication										springApplication=new SpringApplication(CMissingBeansConfiguration.class);
		
		springApplication.setBannerMode(Banner.Mode.OFF);
		springApplication.setLogStartupInfo(false);

		// !!!!! PROGRAM sa NESPUSTI, pretoze BEAN [CMissingBeansNotBean] NEBOL RESOLVED pri DEPENDENCY INJECTION.
		ConfigurableApplicationContext							configurableApplicationContext=springApplication.run(args);

		PrintSeparator();
		
		try
		{
			CMissingBeansComponent								component=configurableApplicationContext.getBean(CMissingBeansComponent.class);

			System.out.printf("BEAN [%s] FOUND.\n",CMissingBeansComponent.class.getSimpleName());
			
			component.Test();
		}
		catch(BeansException E)
		{
			System.out.printf("BEAN [%s] NOT FOUND.\n",CMissingBeansComponent.class.getSimpleName());	
		}
		
		PrintSeparator();

		System.out.println("METHOD END.");
		
		PrintSeparator();
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	private static void TestOptionalBeans(String[] args)
	{
		PrintSeparator();

		System.out.println("METHOD START.");

		PrintSeparator();

		SpringApplication										springApplication=new SpringApplication(COptionalBeansConfiguration.class);
		
		springApplication.setBannerMode(Banner.Mode.OFF);
		springApplication.setLogStartupInfo(false);

		ConfigurableApplicationContext							configurableApplicationContext=springApplication.run(args);

		PrintSeparator();
		
		try
		{
			COptionalBeansComponent								component=configurableApplicationContext.getBean(COptionalBeansComponent.class);

			System.out.printf("BEAN [%s] FOUND.\n",COptionalBeansComponent.class.getSimpleName());
			
			component.Test();
		}
		catch(BeansException E)
		{
			System.out.printf("BEAN [%s] NOT FOUND.\n",COptionalBeansComponent.class.getSimpleName());	
		}
		
		PrintSeparator();

		System.out.println("METHOD END.");
		
		PrintSeparator();
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	private static void TestCyclicDependencies(String[] args)
	{
		PrintSeparator();

		System.out.println("METHOD START.");

		PrintSeparator();

		SpringApplication										springApplication=new SpringApplication(CCyclicDependenciesConfiguration.class);
		
		// !!!!! PROGRAM MUSI mat nastavenu PROPERTY [allowCircularReferences] na VALUE [true].
		springApplication.setAllowCircularReferences(true);
		
		springApplication.setBannerMode(Banner.Mode.OFF);
		springApplication.setLogStartupInfo(false);

		ConfigurableApplicationContext							configurableApplicationContext=springApplication.run(args);

		PrintSeparator();
		
		try
		{
			CCyclicDependenciesSettersComponent					component=configurableApplicationContext.getBean(CCyclicDependenciesSettersComponent.class);

			System.out.printf("BEAN [%s] FOUND.\n",CCyclicDependenciesSettersComponent.class.getSimpleName());
			
			component.Test();
		}
		catch(BeansException E)
		{
			System.out.printf("BEAN [%s] NOT FOUND.\n",CCyclicDependenciesSettersComponent.class.getSimpleName());	
		}

		PrintSeparator();
		
		try
		{
			// !!!!! BEAN NIE JE NAJDENY.
			CCyclicDependenciesLazyComponent					component=configurableApplicationContext.getBean(CCyclicDependenciesLazyComponent.class);

			System.out.printf("BEAN [%s] FOUND.\n",CCyclicDependenciesLazyComponent.class.getSimpleName());
			
			component.Test();
		}
		catch(BeansException E)
		{
			System.out.printf("BEAN [%s] NOT FOUND. EXCEPTION [%s].\n",CCyclicDependenciesLazyComponent.class.getSimpleName(),E.getMessage());	
		}

		PrintSeparator();
		
		try
		{
			// !!!!! BEAN NIE JE NAJDENY.
			CCyclicDependenciesLazyBean1						component=configurableApplicationContext.getBean(CCyclicDependenciesLazyBean1.class);

			System.out.printf("BEAN [%s] FOUND.\n",CCyclicDependenciesLazyBean1.class.getSimpleName());
			
			System.out.printf("FROM BEAN [%s].\n",component.Print());
		}
		catch(BeansException E)
		{
			System.out.printf("BEAN [%s] NOT FOUND. EXCEPTION [%s].\n",CCyclicDependenciesLazyBean1.class.getSimpleName(),E.getMessage());	
		}

		PrintSeparator();
		
		try
		{
			// !!!!! BEAN NIE JE NAJDENY.
			CCyclicDependenciesLazyBean2						component=configurableApplicationContext.getBean(CCyclicDependenciesLazyBean2.class);

			System.out.printf("BEAN [%s] FOUND.\n",CCyclicDependenciesLazyBean2.class.getSimpleName());
			
			System.out.printf("FROM BEAN [%s].\n",component.Print());
		}
		catch(BeansException E)
		{
			System.out.printf("BEAN [%s] NOT FOUND. EXCEPTION [%s].\n",CCyclicDependenciesLazyBean2.class.getSimpleName(),E.getMessage());	
		}
		
		PrintSeparator();

		System.out.println("METHOD END.");
		
		PrintSeparator();
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	private static void TestNonBeansInjection(String[] args)
	{
		PrintSeparator();

		System.out.println("METHOD START.");

		PrintSeparator();

		SpringApplication										springApplication=new SpringApplication(CNonBeansInjectionConfiguration.class);
		
		springApplication.setBannerMode(Banner.Mode.OFF);
		springApplication.setLogStartupInfo(false);

		ConfigurableApplicationContext							configurableApplicationContext=springApplication.run(args);

		PrintSeparator();
		
		try
		{
			CNonBeansInjectionComponent							component=configurableApplicationContext.getBean(CNonBeansInjectionComponent.class);

			System.out.printf("BEAN [%s] FOUND.\n",CNonBeansInjectionComponent.class.getSimpleName());
			
			component.Test();
		}
		catch(BeansException E)
		{
			System.out.printf("BEAN [%s] NOT FOUND.\n",CNonBeansInjectionComponent.class.getSimpleName());	
		}
		
		PrintSeparator();

		System.out.println("METHOD END.");
		
		PrintSeparator();
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	private static void TestBeanFactory(String[] args)
	{
		PrintSeparator();

		System.out.println("METHOD START.");

		PrintSeparator();

		SpringApplication										springApplication=new SpringApplication(CBeansFactoryMethodsConfiguration.class);
		
		springApplication.setBannerMode(Banner.Mode.OFF);
		springApplication.setLogStartupInfo(false);

		ConfigurableApplicationContext							configurableApplicationContext=springApplication.run(args);

		PrintSeparator();
		
		try
		{
			CBeansFactoryMethodsBean1							component=configurableApplicationContext.getBean(CBeansFactoryMethodsBean1.class);

			System.out.printf("BEAN [%s] FOUND.\n",CBeansFactoryMethodsBean1.class.getSimpleName());
			
			component.Print();
		}
		catch(BeansException E)
		{
			System.out.printf("BEAN [%s] NOT FOUND.\n",CBeansFactoryMethodsBean1.class.getSimpleName());	
		}

		PrintSeparator();
		
		try
		{
			CBeansFactoryMethodsBean2							component=configurableApplicationContext.getBean(CBeansFactoryMethodsBean2.class);

			System.out.printf("BEAN [%s] FOUND.\n",CBeansFactoryMethodsBean2.class.getSimpleName());
			
			component.Print();
		}
		catch(BeansException E)
		{
			System.out.printf("BEAN [%s] NOT FOUND.\n",CBeansFactoryMethodsBean2.class.getSimpleName());	
		}

		PrintSeparator();
		
		try
		{
			CBeansFactoryMethodsBeanWithDependencies			component=configurableApplicationContext.getBean(CBeansFactoryMethodsBeanWithDependencies.class);

			System.out.printf("BEAN [%s] FOUND.\n",CBeansFactoryMethodsBeanWithDependencies.class.getSimpleName());
			
			component.Print();
		}
		catch(BeansException E)
		{
			System.out.printf("BEAN [%s] NOT FOUND.\n",CBeansFactoryMethodsBeanWithDependencies.class.getSimpleName());	
		}
		
		PrintSeparator();

		System.out.println("METHOD END.");
		
		PrintSeparator();
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	private static void TestVariousBeans(String[] args)
	{
		PrintSeparator();

		System.out.println("METHOD START.");

		PrintSeparator();

		SpringApplication										springApplication=new SpringApplication(CVariousBeansConfiguration.class);
		
		springApplication.setBannerMode(Banner.Mode.OFF);
		springApplication.setLogStartupInfo(false);

		ConfigurableApplicationContext							configurableApplicationContext=springApplication.run(args);

		PrintSeparator();
		
		try
		{
			CVariousBeansFactoryComponent						component=configurableApplicationContext.getBean(CVariousBeansFactoryComponent.class);
			
			component.Test();
		}
		catch(BeansException E)
		{
			System.out.printf("BEAN [%s] NOT FOUND.\n",CVariousBeansFactoryComponent.class.getSimpleName());	
		}

		PrintSeparator();
		
		try
		{
			String												component=configurableApplicationContext.getBean(String.class);
			
			System.out.printf("BEAN VALUE [%s].\n",component);
		}
		catch(BeansException E)
		{
			System.out.printf("BEAN [%s] NOT FOUND.\n",String.class.getSimpleName());	
		}

		PrintSeparator();
		
		try
		{
			String[]											component=configurableApplicationContext.getBean(String[].class);

			for(int Index=0;Index<component.length;Index++)
			{
				String											value=component[Index];
				
				System.out.printf("BEAN VALUE [%s].\n",value);
			}
		}
		catch(BeansException E)
		{
			System.out.printf("BEAN [%s] NOT FOUND.\n",String[].class.getSimpleName());	
		}

		PrintSeparator();
		
		try
		{
			List<String>										component=(List<String>) configurableApplicationContext.getBean(List.class);
			
			for(int Index=0;Index<component.size();Index++)
			{
				String											value=component.get(Index);
				
				System.out.printf("BEAN VALUE [%s].\n",value);
			}
		}
		catch(BeansException E)
		{
			System.out.printf("BEAN [%s] NOT FOUND.\n","List<String>");	
		}
		
		PrintSeparator();

		System.out.println("METHOD END.");
		
		PrintSeparator();
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	private static void TestMultipleSameTypeBeans(String[] args)
	{
		PrintSeparator();

		System.out.println("METHOD START.");

		PrintSeparator();

		SpringApplication										springApplication=new SpringApplication(CMultipleSameTypeBeansConfiguration.class);
		
		springApplication.setBannerMode(Banner.Mode.OFF);
		springApplication.setLogStartupInfo(false);

		ConfigurableApplicationContext							configurableApplicationContext=springApplication.run(args);

		String[]												allBeanNames=configurableApplicationContext.getBeanDefinitionNames();
		
		for(String beanName : allBeanNames)
		{
			System.out.printf("BEAN [%s].\n",beanName);
		}
		
		PrintSeparator();
		
		try
		{
			CMultipleSameTypeBeansBean							component=(CMultipleSameTypeBeansBean) configurableApplicationContext.getBean("MyBean1");
			
			component.Test();
		}
		catch(BeansException E)
		{
			System.out.printf("BEAN [%s] NOT FOUND. EXCEPTION [%s].\n","MyBean1",E.getMessage());	
		}

		PrintSeparator();
		
		try
		{
			CMultipleSameTypeBeansBean							component=(CMultipleSameTypeBeansBean) configurableApplicationContext.getBean("MyBean2");
			
			component.Test();
		}
		catch(BeansException E)
		{
			System.out.printf("BEAN [%s] NOT FOUND. EXCEPTION [%s].\n","MyBean2",E.getMessage());
		}

		PrintSeparator();

		System.out.println("METHOD END.");
		
		PrintSeparator();
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	private static void TestBeanNamesConflict(String[] args)
	{
		PrintSeparator();

		System.out.println("METHOD START.");

		PrintSeparator();

		SpringApplication										springApplication=new SpringApplication(CBeanNamesConflictConfiguration.class);
		
		springApplication.setBannerMode(Banner.Mode.OFF);
		springApplication.setLogStartupInfo(false);

		ConfigurableApplicationContext							configurableApplicationContext=springApplication.run(args);

		String[]												allBeanNames=configurableApplicationContext.getBeanDefinitionNames();
		
		for(String beanName : allBeanNames)
		{
			System.out.printf("BEAN [%s].\n",beanName);
		}
		
		PrintSeparator();
		
		try
		{
			CBeanNamesConflictBean								component=(CBeanNamesConflictBean) configurableApplicationContext.getBean("MyBean");
			
			component.Test();
		}
		catch(BeansException E)
		{
			System.out.printf("BEAN [%s] NOT FOUND. EXCEPTION [%s].\n","MyBean",E.getMessage());
		}

		PrintSeparator();

		System.out.println("METHOD END.");
		
		PrintSeparator();
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	private static void TestProxyTypes(String[] args)
	{
		PrintSeparator();

		System.out.println("METHOD START.");

		PrintSeparator();

		SpringApplication										springApplication=new SpringApplication(CProxyTypesConfiguration.class);
		
		springApplication.setBannerMode(Banner.Mode.OFF);
		springApplication.setLogStartupInfo(false);

		ConfigurableApplicationContext							configurableApplicationContext=springApplication.run(args);

		PrintSeparator();
		
		try
		{
			CProxyTypesRandomValueBean1							component=configurableApplicationContext.getBean(CProxyTypesRandomValueBean1.class);
			
			component.Test();
		}
		catch(BeansException E)
		{
			System.out.printf("BEAN [%s] NOT FOUND.\n",CProxyTypesRandomValueBean1.class.getSimpleName());	
		}
		
		PrintSeparator();
		
		try
		{
			CProxyTypesRandomValueBean2							component=configurableApplicationContext.getBean(CProxyTypesRandomValueBean2.class);
			
			component.Test();
		}
		catch(BeansException E)
		{
			System.out.printf("BEAN [%s] NOT FOUND.\n",CProxyTypesRandomValueBean2.class.getSimpleName());	
		}
		
		PrintSeparator();
		
		try
		{
			CProxyTypesRandomValueBean3							component=configurableApplicationContext.getBean(CProxyTypesRandomValueBean3.class);
			
			component.Test();
		}
		catch(BeansException E)
		{
			System.out.printf("BEAN [%s] NOT FOUND.\n",CProxyTypesRandomValueBean3.class.getSimpleName());	
		}
		
		PrintSeparator();
		
		try
		{
			CProxyTypesComponentBean							component=configurableApplicationContext.getBean(CProxyTypesComponentBean.class);
			
			component.Test();
		}
		catch(BeansException E)
		{
			System.out.printf("BEAN [%s] NOT FOUND.\n",CProxyTypesComponentBean.class.getSimpleName());	
		}

		PrintSeparator();
		
		try
		{
			CProxyTypesRandomValueNoProxyBean1					component=configurableApplicationContext.getBean(CProxyTypesRandomValueNoProxyBean1.class);
			
			component.Test();
		}
		catch(BeansException E)
		{
			System.out.printf("BEAN [%s] NOT FOUND.\n",CProxyTypesRandomValueNoProxyBean1.class.getSimpleName());	
		}
		
		PrintSeparator();
		
		try
		{
			CProxyTypesRandomValueNoProxyBean2					component=configurableApplicationContext.getBean(CProxyTypesRandomValueNoProxyBean2.class);
			
			component.Test();
		}
		catch(BeansException E)
		{
			System.out.printf("BEAN [%s] NOT FOUND.\n",CProxyTypesRandomValueNoProxyBean2.class.getSimpleName());	
		}

		PrintSeparator();

		System.out.println("METHOD END.");
		
		PrintSeparator();
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	private static void TestBeanInjectionPoints(String[] args)
	{
		PrintSeparator();

		System.out.println("METHOD START.");

		PrintSeparator();

		SpringApplication										springApplication=new SpringApplication(CBeanInjectionPointsConfiguration.class);
		
		springApplication.setBannerMode(Banner.Mode.OFF);
		springApplication.setLogStartupInfo(false);

		ConfigurableApplicationContext							configurableApplicationContext=springApplication.run(args);

		PrintSeparator();
		
		try
		{
			CBeanInjectionPointsComponent						component=configurableApplicationContext.getBean(CBeanInjectionPointsComponent.class);
			
			component.Test();
		}
		catch(BeansException E)
		{
			System.out.printf("BEAN [%s] NOT FOUND.\n",CBeanInjectionPointsComponent.class.getSimpleName());	
		}

		PrintSeparator();

		System.out.println("METHOD END.");
		
		PrintSeparator();
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	private static void TestStaticFactoryMethods(String[] args)
	{
		PrintSeparator();

		System.out.println("METHOD START.");

		PrintSeparator();

		SpringApplication										springApplication=new SpringApplication(CStaticFactoryMethodsConfiguration.class);
		
		springApplication.setBannerMode(Banner.Mode.OFF);
		springApplication.setLogStartupInfo(false);

		ConfigurableApplicationContext							configurableApplicationContext=springApplication.run(args);

		PrintSeparator();
		
		try
		{
			CStaticFactoryMethodsComponent						component=configurableApplicationContext.getBean(CStaticFactoryMethodsComponent.class);
			
			component.Test();
		}
		catch(BeansException E)
		{
			System.out.printf("BEAN [%s] NOT FOUND.\n",CStaticFactoryMethodsComponent.class.getSimpleName());	
		}

		PrintSeparator();

		System.out.println("METHOD END.");
		
		PrintSeparator();
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	private static void TestImportConfigurations(String[] args)
	{
		PrintSeparator();

		System.out.println("METHOD START.");

		PrintSeparator();

		SpringApplication										springApplication=new SpringApplication(CImportConfigurationsConfiguration.class);
		
		springApplication.setBannerMode(Banner.Mode.OFF);
		springApplication.setLogStartupInfo(false);

		ConfigurableApplicationContext							configurableApplicationContext=springApplication.run(args);

		PrintSeparator();
		
		try
		{
			CImportConfigurations1Bean							component=configurableApplicationContext.getBean(CImportConfigurations1Bean.class);
			
			component.Test();
		}
		catch(BeansException E)
		{
			System.out.printf("BEAN [%s] NOT FOUND.\n",CImportConfigurations1Bean.class.getSimpleName());	
		}

		PrintSeparator();
		
		try
		{
			CImportConfigurations1Component						component=configurableApplicationContext.getBean(CImportConfigurations1Component.class);
			
			component.Test();
		}
		catch(BeansException E)
		{
			System.out.printf("BEAN [%s] NOT FOUND.\n",CImportConfigurations1Component.class.getSimpleName());	
		}

		PrintSeparator();
		
		try
		{
			CImportConfigurations2Bean							component=configurableApplicationContext.getBean(CImportConfigurations2Bean.class);
			
			component.Test();
		}
		catch(BeansException E)
		{
			System.out.printf("BEAN [%s] NOT FOUND.\n",CImportConfigurations2Bean.class.getSimpleName());	
		}

		PrintSeparator();
		
		try
		{
			CImportConfigurations2Component						component=configurableApplicationContext.getBean(CImportConfigurations2Component.class);
			
			component.Test();
		}
		catch(BeansException E)
		{
			System.out.printf("BEAN [%s] NOT FOUND.\n",CImportConfigurations2Component.class.getSimpleName());
		}

		PrintSeparator();
		
		try
		{
			CImportConfigurations3Bean							component=configurableApplicationContext.getBean(CImportConfigurations3Bean.class);
			
			component.Test();
		}
		catch(BeansException E)
		{
			System.out.printf("BEAN [%s] NOT FOUND.\n",CImportConfigurations3Bean.class.getSimpleName());
		}

		PrintSeparator();
		
		try
		{
			CImportConfigurations3Component						component=configurableApplicationContext.getBean(CImportConfigurations3Component.class);
			
			component.Test();
		}
		catch(BeansException E)
		{
			System.out.printf("BEAN [%s] NOT FOUND.\n",CImportConfigurations3Component.class.getSimpleName());	
		}

		PrintSeparator();

		System.out.println("METHOD END.");
		
		PrintSeparator();
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	private static void TestNamedBeans(String[] args)
	{
		PrintSeparator();

		System.out.println("METHOD START.");

		PrintSeparator();

		SpringApplication										springApplication=new SpringApplication(CNamedBeansConfiguration.class);
		
		springApplication.setBannerMode(Banner.Mode.OFF);
		springApplication.setLogStartupInfo(false);

		ConfigurableApplicationContext							configurableApplicationContext=springApplication.run(args);

		PrintSeparator();
		
		try
		{
			// !!! COMPONENT sa ziskava pomocou DEFAULT NAME.
			CNamedBeansComponentDefaultName						component=(CNamedBeansComponentDefaultName) configurableApplicationContext.getBean("CNamedBeansComponentDefaultName");
			
			component.Test();
		}
		catch(BeansException E)
		{
			System.out.printf("BEAN [%s] NOT FOUND.\n","CNamedBeansComponentDefaultName");	
		}

		PrintSeparator();
		
		try
		{
			// !!! COMPONENT sa ziskava pomocou CUSTOM NAME.
			CNamedBeansComponentCustomName						component=(CNamedBeansComponentCustomName) configurableApplicationContext.getBean("MyCustomComponent");
			
			component.Test();
		}
		catch(BeansException E)
		{
			System.out.printf("BEAN [%s] NOT FOUND.\n","MyCustomComponent");	
		}

		PrintSeparator();
		
		try
		{
			// !!! BEAN sa ziskava pomocou DEFAULT NAME.
			CNamedBeansBean										component=(CNamedBeansBean) configurableApplicationContext.getBean("MyBeanDefaultName");
			
			component.Test();
		}
		catch(BeansException E)
		{
			System.out.printf("BEAN [%s] NOT FOUND.\n","MyBeanDefaultName");	
		}

		PrintSeparator();
		
		try
		{
			// !!! BEAN sa ziskava pomocou CUSTOM NAME.
			CNamedBeansBean										component=(CNamedBeansBean) configurableApplicationContext.getBean("MyCustomBean1");
			
			component.Test();
		}
		catch(BeansException E)
		{
			System.out.printf("BEAN [%s] NOT FOUND.\n","MyCustomBean1");	
		}

		PrintSeparator();
		
		try
		{
			// !!! BEAN sa ziskava pomocou CUSTOM ALIAS NAME.
			CNamedBeansBean										component=(CNamedBeansBean) configurableApplicationContext.getBean("MyCustomBean2");
			
			component.Test();
		}
		catch(BeansException E)
		{
			System.out.printf("BEAN [%s] NOT FOUND.\n","MyCustomBean2");	
		}

		PrintSeparator();

		System.out.println("METHOD END.");
		
		PrintSeparator();
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	private static void TestBaseTypesBeans(String[] args)
	{
		PrintSeparator();

		System.out.println("METHOD START.");

		PrintSeparator();

		SpringApplication										springApplication=new SpringApplication(CBaseTypesBeansConfiguration.class);
		
		springApplication.setBannerMode(Banner.Mode.OFF);
		springApplication.setLogStartupInfo(false);

		ConfigurableApplicationContext							configurableApplicationContext=springApplication.run(args);

		PrintSeparator();
		
		try
		{
			CBaseTypesBeansComponent							component=configurableApplicationContext.getBean(CBaseTypesBeansComponent.class);
			
			component.Test();
		}
		catch(BeansException E)
		{
			System.out.printf("BEAN [%s] NOT FOUND.\n",CBaseTypesBeansComponent.class.getSimpleName());	
		}

		PrintSeparator();

		System.out.println("METHOD END.");
		
		PrintSeparator();
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	private static void TestGenericTypesBeans(String[] args)
	{
		PrintSeparator();

		System.out.println("METHOD START.");

		PrintSeparator();

		SpringApplication										springApplication=new SpringApplication(CGenericTypesBeansConfiguration.class);
		
		springApplication.setBannerMode(Banner.Mode.OFF);
		springApplication.setLogStartupInfo(false);

		ConfigurableApplicationContext							configurableApplicationContext=springApplication.run(args);

		PrintSeparator();
		
		try
		{
			CGenericTypesBeansTestBean							component=configurableApplicationContext.getBean(CGenericTypesBeansTestBean.class);
			
			component.Test();
		}
		catch(BeansException E)
		{
			System.out.printf("BEAN [%s] NOT FOUND.\n",CGenericTypesBeansTestBean.class.getSimpleName());	
		}

		PrintSeparator();

		System.out.println("METHOD END.");
		
		PrintSeparator();
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	private static void TestPrimaryBeansTestBeanQualifiers(String[] args)
	{
		PrintSeparator();

		System.out.println("METHOD START.");

		PrintSeparator();

		SpringApplication										springApplication=new SpringApplication(CBeanQualifiersConfiguration.class);
		
		springApplication.setBannerMode(Banner.Mode.OFF);
		springApplication.setLogStartupInfo(false);

		ConfigurableApplicationContext							configurableApplicationContext=springApplication.run(args);

		PrintSeparator();
		
		try
		{
			CBeanQualifiersTestClass							component=configurableApplicationContext.getBean(CBeanQualifiersTestClass.class);
			
			component.Test();
		}
		catch(BeansException E)
		{
			System.out.printf("BEAN [%s] NOT FOUND.\n",CBeanQualifiersTestClass.class.getSimpleName());	
		}

		PrintSeparator();

		System.out.println("METHOD END.");
		
		PrintSeparator();
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	private static void TestPrimaryBeans(String[] args)
	{
		PrintSeparator();

		System.out.println("METHOD START.");

		PrintSeparator();

		SpringApplication										springApplication=new SpringApplication(CPrimaryBeansConfiguration.class);
		
		springApplication.setBannerMode(Banner.Mode.OFF);
		springApplication.setLogStartupInfo(false);

		ConfigurableApplicationContext							configurableApplicationContext=springApplication.run(args);

		PrintSeparator();
		
		try
		{
			CPrimaryBeansComponent								component=configurableApplicationContext.getBean(CPrimaryBeansComponent.class);
			
			component.Test();
		}
		catch(BeansException E)
		{
			System.out.printf("BEAN [%s] NOT FOUND.\n",CPrimaryBeansComponent.class.getSimpleName());	
		}

		PrintSeparator();

		System.out.println("METHOD END.");
		
		PrintSeparator();
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	private static void TestCollectionBeans(String[] args)
	{
		PrintSeparator();

		System.out.println("METHOD START.");

		PrintSeparator();

		SpringApplication										springApplication=new SpringApplication(CCollectionBeansConfiguration.class);
		
		springApplication.setBannerMode(Banner.Mode.OFF);
		springApplication.setLogStartupInfo(false);

		ConfigurableApplicationContext							configurableApplicationContext=springApplication.run(args);

		PrintSeparator();
		
		try
		{
			CCollectionBeansComponent							component=configurableApplicationContext.getBean(CCollectionBeansComponent.class);
			
			component.Test();
		}
		catch(BeansException E)
		{
			System.out.printf("BEAN [%s] NOT FOUND.\n",CCollectionBeansComponent.class.getSimpleName());	
		}

		PrintSeparator();

		System.out.println("METHOD END.");
		
		PrintSeparator();
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	private static void TestFallbackMatchInjection(String[] args)
	{
		PrintSeparator();

		System.out.println("METHOD START.");

		PrintSeparator();

		SpringApplication										springApplication=new SpringApplication(CFallbackMatchInjectionConfiguration.class);
		
		springApplication.setBannerMode(Banner.Mode.OFF);
		springApplication.setLogStartupInfo(false);

		ConfigurableApplicationContext							configurableApplicationContext=springApplication.run(args);

		PrintSeparator();
		
		try
		{
			CFallbackMatchInjectionComponent					component=configurableApplicationContext.getBean(CFallbackMatchInjectionComponent.class);
			
			component.Test();
		}
		catch(BeansException E)
		{
			System.out.printf("BEAN [%s] NOT FOUND.\n",CFallbackMatchInjectionComponent.class.getSimpleName());	
		}

		PrintSeparator();

		System.out.println("METHOD END.");
		
		PrintSeparator();
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	private static void TestResourceAnnotations(String[] args)
	{
		PrintSeparator();

		System.out.println("METHOD START.");

		PrintSeparator();

		SpringApplication										springApplication=new SpringApplication(CResourceAnnotationsConfiguration.class);
		
		springApplication.setBannerMode(Banner.Mode.OFF);
		springApplication.setLogStartupInfo(false);

		ConfigurableApplicationContext							configurableApplicationContext=springApplication.run(args);

		PrintSeparator();
		
		try
		{
			CResourceAnnotationsComponent						component=configurableApplicationContext.getBean(CResourceAnnotationsComponent.class);
			
			component.Test();
		}
		catch(BeansException E)
		{
			System.out.printf("BEAN [%s] NOT FOUND.\n",CResourceAnnotationsComponent.class.getSimpleName());	
		}

		PrintSeparator();

		System.out.println("METHOD END.");
		
		PrintSeparator();
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	private static void TestObjectProviders(String[] args)
	{
		PrintSeparator();

		System.out.println("METHOD START.");

		PrintSeparator();

		SpringApplication										springApplication=new SpringApplication(CObjectProvidersConfiguration.class);
		
		springApplication.setBannerMode(Banner.Mode.OFF);
		springApplication.setLogStartupInfo(false);

		ConfigurableApplicationContext							configurableApplicationContext=springApplication.run(args);

		PrintSeparator();
		
		try
		{
			CObjectProvidersComponent							component=configurableApplicationContext.getBean(CObjectProvidersComponent.class);
			
			component.Test();
		}
		catch(BeansException E)
		{
			System.out.printf("BEAN [%s] NOT FOUND.\n",CObjectProvidersComponent.class.getSimpleName());
		}

		PrintSeparator();

		System.out.println("METHOD END.");
		
		PrintSeparator();
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	private static void TestOrderedBeans(String[] args)
	{
		PrintSeparator();

		System.out.println("METHOD START.");

		PrintSeparator();

		SpringApplication										springApplication=new SpringApplication(COrderedBeansConfiguration.class);
		
		springApplication.setBannerMode(Banner.Mode.OFF);
		springApplication.setLogStartupInfo(false);

		ConfigurableApplicationContext							configurableApplicationContext=springApplication.run(args);

		PrintSeparator();
		
		try
		{
			COrderedBeansComponent								component=configurableApplicationContext.getBean(COrderedBeansComponent.class);
			
			component.Test();
		}
		catch(BeansException E)
		{
			System.out.printf("BEAN [%s] NOT FOUND.\n",COrderedBeansComponent.class.getSimpleName());
		}

		PrintSeparator();

		System.out.println("METHOD END.");
		
		PrintSeparator();
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	private static void TestInheritanceBeans(String[] args)
	{
		PrintSeparator();

		System.out.println("METHOD START.");

		PrintSeparator();

		SpringApplication										springApplication=new SpringApplication(CInheritanceBeansConfiguration.class);
		
		springApplication.setBannerMode(Banner.Mode.OFF);
		springApplication.setLogStartupInfo(false);

		ConfigurableApplicationContext							configurableApplicationContext=springApplication.run(args);

		PrintSeparator();
		
		try
		{
			CInheritanceBeansComponent							component=configurableApplicationContext.getBean(CInheritanceBeansComponent.class);
			
			component.Test();
		}
		catch(BeansException E)
		{
			System.out.printf("BEAN [%s] NOT FOUND.\n",CInheritanceBeansComponent.class.getSimpleName());
		}

		PrintSeparator();

		System.out.println("METHOD END.");
		
		PrintSeparator();
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	private static void TestInheritanceComponents(String[] args)
	{
		PrintSeparator();

		System.out.println("METHOD START.");

		PrintSeparator();

		SpringApplication										springApplication=new SpringApplication(CInheritanceComponentsConfiguration.class);
		
		springApplication.setBannerMode(Banner.Mode.OFF);
		springApplication.setLogStartupInfo(false);

		ConfigurableApplicationContext							configurableApplicationContext=springApplication.run(args);

		PrintSeparator();
		
		try
		{
			CInheritanceComponentsComponent						component=configurableApplicationContext.getBean(CInheritanceComponentsComponent.class);
			
			component.Test();
		}
		catch(BeansException E)
		{
			System.out.printf("BEAN [%s] NOT FOUND.\n",CInheritanceComponentsComponent.class.getSimpleName());
		}

		PrintSeparator();

		System.out.println("METHOD END.");
		
		PrintSeparator();
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	private static void TestInheritanceAutowired(String[] args)
	{
		PrintSeparator();

		System.out.println("METHOD START.");

		PrintSeparator();

		SpringApplication										springApplication=new SpringApplication(CInheritanceAutowiredConfiguration.class);
		
		springApplication.setBannerMode(Banner.Mode.OFF);
		springApplication.setLogStartupInfo(false);

		ConfigurableApplicationContext							configurableApplicationContext=springApplication.run(args);

		PrintSeparator();
		
		try
		{
			CInheritanceAutowiredComponentDerived				component=configurableApplicationContext.getBean(CInheritanceAutowiredComponentDerived.class);
			
			component.Test();
		}
		catch(BeansException E)
		{
			System.out.printf("BEAN [%s] NOT FOUND.\n",CInheritanceAutowiredComponentDerived.class.getSimpleName());
		}

		PrintSeparator();

		System.out.println("METHOD END.");
		
		PrintSeparator();
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	private static void TestDependsOnBeans(String[] args)
	{
		PrintSeparator();

		System.out.println("METHOD START.");

		PrintSeparator();

		SpringApplication										springApplication=new SpringApplication(CDependsOnBeansConfiguration.class);
		
		springApplication.setBannerMode(Banner.Mode.OFF);
		springApplication.setLogStartupInfo(false);

		ConfigurableApplicationContext							configurableApplicationContext=springApplication.run(args);

		PrintSeparator();
		
		try
		{
			CDependsOnBeansComponent							component=configurableApplicationContext.getBean(CDependsOnBeansComponent.class);
			
			component.Test();
		}
		catch(BeansException E)
		{
			System.out.printf("BEAN [%s] NOT FOUND.\n",CDependsOnBeansComponent.class.getSimpleName());
		}

		PrintSeparator();

		System.out.println("METHOD END.");
		
		PrintSeparator();
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	private static void TestLazyBeans(String[] args)
	{
		PrintSeparator();

		System.out.println("METHOD START.");

		PrintSeparator();

		SpringApplication										springApplication=new SpringApplication(CLazyBeansConfiguration.class);
		
		springApplication.setBannerMode(Banner.Mode.OFF);
		springApplication.setLogStartupInfo(false);

		// !!!!! Ako DEFAULT sa nastavi EAGER LOADING.
		springApplication.setLazyInitialization(false);
		
		ConfigurableApplicationContext							configurableApplicationContext=springApplication.run(args);
		
		PrintSeparator();
		
		try
		{
			CLazyBeansLazyComponent								component=configurableApplicationContext.getBean(CLazyBeansLazyComponent.class);
			
			component.Test();
		}
		catch(BeansException E)
		{
			System.out.printf("BEAN [%s] NOT FOUND.\n",CLazyBeansLazyComponent.class.getSimpleName());
		}
		
		PrintSeparator();
		
		try
		{
			CLazyBeansEagerComponent							component=configurableApplicationContext.getBean(CLazyBeansEagerComponent.class);
			
			component.Test();
		}
		catch(BeansException E)
		{
			System.out.printf("BEAN [%s] NOT FOUND.\n",CLazyBeansEagerComponent.class.getSimpleName());
		}

		PrintSeparator();

		System.out.println("METHOD END.");
		
		PrintSeparator();
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	private static void TestBeanInitializationProblem(String[] args)
	{
		PrintSeparator();

		System.out.println("METHOD START.");

		PrintSeparator();

		SpringApplication										springApplication=new SpringApplication(CBeanInitializationProblemConfiguration.class);
		
		springApplication.setBannerMode(Banner.Mode.OFF);
		springApplication.setLogStartupInfo(false);

		// !!!!! Ako DEFAULT sa nastavi EAGER LOADING.
		springApplication.setLazyInitialization(false);
		
		ConfigurableApplicationContext							configurableApplicationContext=springApplication.run(args);
		
		PrintSeparator();
		
		try
		{
			CBeanInitializationProblemComponent					component=configurableApplicationContext.getBean(CBeanInitializationProblemComponent.class);
			
			component.Test();
		}
		catch(BeansException E)
		{
			System.out.printf("BEAN [%s] NOT FOUND.\n",CBeanInitializationProblemComponent.class.getSimpleName());
		}

		PrintSeparator();

		System.out.println("METHOD END.");
		
		PrintSeparator();
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	private static void TestLifecycleEventsAnnotations(String[] args)
	{
		PrintSeparator();

		System.out.println("METHOD START.");

		PrintSeparator();

		SpringApplication										springApplication=new SpringApplication(CLifecycleEventsAnnotationsConfiguration.class);
		
		springApplication.setBannerMode(Banner.Mode.OFF);
		springApplication.setLogStartupInfo(false);
		
		ConfigurableApplicationContext							configurableApplicationContext=springApplication.run(args);
		
		PrintSeparator();
		
		try
		{
			CLifecycleEventsAnnotationsComponent				component=configurableApplicationContext.getBean(CLifecycleEventsAnnotationsComponent.class);
			
			component.Test();
		}
		catch(BeansException E)
		{
			System.out.printf("BEAN [%s] NOT FOUND.\n",CLifecycleEventsAnnotationsComponent.class.getSimpleName());
		}

		PrintSeparator();

		System.out.printf("SPRING CONTAINER is CLOSING.\n");

		// !!!!! Uvolnia sa vsetky BEANS.
		configurableApplicationContext.close();

		System.out.printf("SPRING CONTAINER is CLOSED.\n");
		
		PrintSeparator();
		
		System.out.println("METHOD END.");
		
		PrintSeparator();
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	private static void TestLifecycleEventsInterfaces(String[] args)
	{
		PrintSeparator();

		System.out.println("METHOD START.");

		PrintSeparator();

		SpringApplication										springApplication=new SpringApplication(CLifecycleEventsInterfacesConfiguration.class);
		
		springApplication.setBannerMode(Banner.Mode.OFF);
		springApplication.setLogStartupInfo(false);
		
		ConfigurableApplicationContext							configurableApplicationContext=springApplication.run(args);
		
		PrintSeparator();
		
		try
		{
			CLifecycleEventsInterfacesComponent					component=configurableApplicationContext.getBean(CLifecycleEventsInterfacesComponent.class);
			
			component.Test();
		}
		catch(BeansException E)
		{
			System.out.printf("BEAN [%s] NOT FOUND.\n",CLifecycleEventsInterfacesComponent.class.getSimpleName());
		}

		PrintSeparator();

		System.out.printf("SPRING CONTAINER is CLOSING.\n");

		// !!!!! Uvolnia sa vsetky BEANS.
		configurableApplicationContext.close();

		System.out.printf("SPRING CONTAINER is CLOSED.\n");
		
		PrintSeparator();
		
		System.out.println("METHOD END.");
		
		PrintSeparator();
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	private static void TestManualRegisteringBeans(String[] args)
	{
		PrintSeparator();

		System.out.println("METHOD START.");

		PrintSeparator();

		SpringApplication										springApplication=new SpringApplication(CManualRegisteringBeansConfiguration.class);
		
		springApplication.setBannerMode(Banner.Mode.OFF);
		springApplication.setLogStartupInfo(false);
		
		ConfigurableApplicationContext							configurableApplicationContext=springApplication.run(args);
		
		PrintSeparator();
		
		try
		{
			CManualRegisteringBeansComponent					component=configurableApplicationContext.getBean(CManualRegisteringBeansComponent.class);
			
			component.Test();
		}
		catch(BeansException E)
		{
			System.out.printf("BEAN [%s] NOT FOUND.\n",CManualRegisteringBeansComponent.class.getSimpleName());
		}

		PrintSeparator();
		
		System.out.println("METHOD END.");
		
		PrintSeparator();
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	private static void TestBeanPostProcessors(String[] args)
	{
		PrintSeparator();

		System.out.println("METHOD START.");

		PrintSeparator();

		// !!! MANUALNE sa vytvori SPRING CONTAINER.
		try (AnnotationConfigApplicationContext context=new AnnotationConfigApplicationContext())
		{
			ConfigurableListableBeanFactory						beanFactory=context.getBeanFactory();

			// !!!!! Vytvori sa instancia CUSTOM BEAN POST PROCESSOR.
			CBeanPostProcessorsPostProcessor3					beanPostProcessor3=new CBeanPostProcessorsPostProcessor3();
			
			// !!!!! MANUALNE sa zaregistruje CUSTOM BEAN POST PROCESSOR.
			// !!!!! Manualne zaregistrovany BEAN POST PROCESSOR sa APLIKUJE aj na INTERNAL SPRING FRAMEWORK BEANS.
			beanFactory.addBeanPostProcessor(beanPostProcessor3);

			// !!! MANUALNE sa zaregistruje MAIN CONFIGURATION CLASS.
			context.register(CBeanPostProcessorsConfiguration.class);

			// !!!!! Vytvori sa instancia CUSTOM BEAN POST PROCESSOR.
			// !!!!! Manualne zaregistrovany BEAN POST PROCESSOR sa APLIKUJE aj na INTERNAL SPRING FRAMEWORK BEANS.
			CBeanPostProcessorsPostProcessor4					beanPostProcessor4=new CBeanPostProcessorsPostProcessor4();

			// !!!!! MANUALNE sa zaregistruje CUSTOM BEAN POST PROCESSOR.
			beanFactory.addBeanPostProcessor(beanPostProcessor4);
			
			context.refresh();
			
			PrintSeparator();
			
			try
			{
				CBeanPostProcessorsComponent					component=context.getBean(CBeanPostProcessorsComponent.class);
				
				component.Test();
			}
			catch(BeansException E)
			{
				System.out.printf("BEAN [%s] NOT FOUND.\n",CBeanPostProcessorsComponent.class.getSimpleName());
			}
		}
		
		PrintSeparator();
		
		System.out.println("METHOD END.");
		
		PrintSeparator();
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	private static void TestListableBeanFactory(String[] args)
	{
		PrintSeparator();

		System.out.println("METHOD START.");

		PrintSeparator();

		SpringApplication										springApplication=new SpringApplication(CListableBeanFactoryConfiguration.class);
		
		springApplication.setBannerMode(Banner.Mode.OFF);
		springApplication.setLogStartupInfo(false);
		
		ConfigurableApplicationContext							configurableApplicationContext=springApplication.run(args);
	
		ConfigurableListableBeanFactory							typedBeanFactory=configurableApplicationContext.getBeanFactory();
		BeanFactory												beanFactory=typedBeanFactory;
		ListableBeanFactory										listableBeanFactory=configurableApplicationContext;

		PrintSeparator();
	
		try
		{
			Map<String,IListableBeanFactoryInterface>			map=listableBeanFactory.getBeansOfType(IListableBeanFactoryInterface.class);

			for(String beanName : map.keySet())
			{
				IListableBeanFactoryInterface					bean=map.get(beanName);
				
				System.out.printf("KEY [%s] VALUE [%s].\n",beanName,bean);
			}
		}
		catch(BeansException E)
		{
			System.out.printf("BEAN NOT FOUND.\n");
		}

		PrintSeparator();
	
		try
		{
			Map<String,Object>									map=listableBeanFactory.getBeansWithAnnotation(IListableBeanFactoryAnnotation2.class);

			for(String beanName : map.keySet())
			{
				Object											bean=map.get(beanName);
				
				System.out.printf("KEY [%s] VALUE [%s].\n",beanName,bean);
			}
		}
		catch(BeansException E)
		{
			System.out.printf("BEAN NOT FOUND.\n");
		}
		
		PrintSeparator();
		
		try
		{
			// !!! METHOD [] je sucast INTERFACE [].
			CListableBeanFactoryBean1							bean=beanFactory.getBean(CListableBeanFactoryBean1.class);
			String												text=bean.GetText();
			
			System.out.printf("BEAN [%s].\n",text);
		}
		catch(BeansException E)
		{
			System.out.printf("BEAN [%s] NOT FOUND.\n",CListableBeanFactoryBean1.class.getSimpleName());
		}

		PrintSeparator();
		
		try
		{
			CListableBeanFactoryBean2							bean=beanFactory.getBean(CListableBeanFactoryBean2.class);
			String												text=bean.GetText();
			
			System.out.printf("BEAN [%s].\n",text);
		}
		catch(BeansException E)
		{
			System.out.printf("BEAN [%s] NOT FOUND.\n",CListableBeanFactoryBean2.class.getSimpleName());
		}

		PrintSeparator();
		
		try
		{
			CListableBeanFactoryBean3							bean=beanFactory.getBean(CListableBeanFactoryBean3.class);
			String												text=bean.GetText();
			
			System.out.printf("BEAN [%s].\n",text);
		}
		catch(BeansException E)
		{
			System.out.printf("BEAN [%s] NOT FOUND.\n",CListableBeanFactoryBean3.class.getSimpleName());
		}
		
		PrintSeparator();
		
		System.out.println("METHOD END.");
		
		PrintSeparator();
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	private static void TestHierarchicalContexts(String[] args)
	{
		PrintSeparator();

		System.out.println("METHOD START.");

		PrintSeparator();

		// !!! CLASS reprezentuje APPLICATION BUILDER, z ktoreho sa NEVYTVORI APPLICATION, iba sa pouzije na vytvorenie inych APPLICATION BUILDER.
		SpringApplicationBuilder								applicationBuilderBase=new SpringApplicationBuilder();
		
		// !!!!! Ak by sa pre APPLICATION BUILDER zavolala METHOD [], APPLICATION BUILDER by mal pridelenu CONFIGURATION a sluzil by ako PARENT APPLICATION BUILDER. 
		//applicationBuilderBase.sources(CHierarchicalContextsParentConfiguration.class);
		
		// !!! Pomocou METHOD [SpringApplicationBuilder parent(Class<?>... sources)] sa vytvori CLASS, ktora reprezentuje APPLICATION BUILDER pre PARENT CONTEXT.
		SpringApplicationBuilder								applicationBuilderParent=applicationBuilderBase.parent(CHierarchicalContextsParentConfiguration.class);
		
		// !!! Pomocou METHOD [SpringApplicationBuilder SpringApplicationBuilder.child(Class<?>... sources)] sa vytvori CLASS, ktora reprezentuje APPLICATION BUILDER pre CHILD 1 CONTEXT.
		SpringApplicationBuilder								applicationBuilderChild1=applicationBuilderParent.child(CHierarchicalContextsChild1Configuration.class);
		
		// !!! Pomocou METHOD [SpringApplicationBuilder SpringApplicationBuilder.sibling(Class<?>... sources)] sa vytvori CLASS, ktora reprezentuje APPLICATION BUILDER pre CHILD 2 CONTEXT.
		SpringApplicationBuilder								applicationBuilderChild2=applicationBuilderChild1.sibling(CHierarchicalContextsChild2Configuration.class);
		
		// !!! Vytvori sa instancia CLASS [SpringApplication] pre PARENT CONTEXT.
		SpringApplication										springApplicationParent=applicationBuilderParent.build();
		
		// !!! Vytvori sa instancia CLASS [SpringApplication] pre CHILD 1 CONTEXT.
		SpringApplication										springApplicationChild1=applicationBuilderChild1.build();

		// !!! Vytvori sa instancia CLASS [SpringApplication] pre CHILD 2 CONTEXT.
		SpringApplication										springApplicationChild2=applicationBuilderChild2.build();

		// !!!!! Vytvori sa PARENT CONTEXT. 
		ConfigurableApplicationContext							contextParent=springApplicationParent.run(args);

		// !!!!! Vytvori sa CHILD 1 CONTEXT. 
		ConfigurableApplicationContext							contextChild1=springApplicationChild1.run(args);

		// !!!!! Vytvori sa CHILD 2 CONTEXT. 
		ConfigurableApplicationContext							contextChild2=springApplicationChild2.run(args);
		
		PrintSeparator();
		
		try
		{
			CHierarchicalContextsParentComponent				component=contextParent.getBean(CHierarchicalContextsParentComponent.class);
			
			component.Test();
		}
		catch(BeansException E)
		{
			System.out.printf("BEAN [%s] NOT FOUND.\n",CHierarchicalContextsParentComponent.class.getSimpleName());
		}
	
		PrintSeparator();

		try
		{
			CHierarchicalContextsChild1Component				component=contextChild1.getBean(CHierarchicalContextsChild1Component.class);
			
			component.Test();
		}
		catch(BeansException E)
		{
			System.out.printf("BEAN [%s] NOT FOUND.\n",CHierarchicalContextsChild1Component.class.getSimpleName());
		}

		PrintSeparator();
		
		try
		{
			CHierarchicalContextsChild2Component				component=contextChild2.getBean(CHierarchicalContextsChild2Component.class);
			
			component.Test();
		}
		catch(BeansException E)
		{
			System.out.printf("BEAN [%s] NOT FOUND.\n",CHierarchicalContextsChild2Component.class.getSimpleName());
		}
		
		PrintSeparator();
		
		System.out.println("METHOD END.");
		
		PrintSeparator();
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	private static void TestConditionalBeans(String[] args)
	{
		PrintSeparator();

		System.out.println("METHOD START.");

		PrintSeparator();

		SpringApplication										springApplication=new SpringApplication(CConditionalBeansConfiguration.class);
		
		springApplication.setBannerMode(Banner.Mode.OFF);
		springApplication.setLogStartupInfo(false);

		ConfigurableApplicationContext							configurableApplicationContext=springApplication.run(args);

		PrintSeparator();
		
		try
		{
			CConditionalBeansComponent							component=configurableApplicationContext.getBean(CConditionalBeansComponent.class);
			
			component.Test();
		}
		catch(BeansException E)
		{
			System.out.printf("BEAN [%s] NOT FOUND.\n",CConditionalBeansComponent.class.getSimpleName());
		}

		PrintSeparator();

		System.out.println("METHOD END.");
		
		PrintSeparator();
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	private static void TestConditionalOnPropertyBeans(String[] args)
	{
		PrintSeparator();

		System.out.println("METHOD START.");

		PrintSeparator();

		SpringApplication										springApplication=new SpringApplication(CConditionalOnPropertyBeansConfiguration.class);
		
		springApplication.setBannerMode(Banner.Mode.OFF);
		springApplication.setLogStartupInfo(false);

		Map<String,Object>										myProperties=new HashMap<String,Object>();
		
		myProperties.put("MyProperty","AAA");
		
		// !!! Nastavia sa CUSTOM PROPERTIES.
		springApplication.setDefaultProperties(myProperties);
		
		ConfigurableApplicationContext							configurableApplicationContext=springApplication.run(args);

		PrintSeparator();
		
		try
		{
			CConditionalOnPropertyBeansComponent				component=configurableApplicationContext.getBean(CConditionalOnPropertyBeansComponent.class);
			
			component.Test();
		}
		catch(BeansException E)
		{
			System.out.printf("BEAN [%s] NOT FOUND.\n",CConditionalOnPropertyBeansComponent.class.getSimpleName());
		}

		PrintSeparator();

		System.out.println("METHOD END.");
		
		PrintSeparator();
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	private static void TestConditionalOnMissingBean(String[] args)
	{
		PrintSeparator();

		System.out.println("METHOD START.");

		PrintSeparator();

		SpringApplication										springApplication=new SpringApplication(CConditionalOnMissingBeanBeansConfiguration.class);
		
		springApplication.setBannerMode(Banner.Mode.OFF);
		springApplication.setLogStartupInfo(false);
	
		ConfigurableApplicationContext							configurableApplicationContext=springApplication.run(args);

		PrintSeparator();
		
		try
		{
			CConditionalOnMissingBeanBeansComponent				component=configurableApplicationContext.getBean(CConditionalOnMissingBeanBeansComponent.class);
			
			component.Test();
		}
		catch(BeansException E)
		{
			System.out.printf("BEAN [%s] NOT FOUND.\n",CConditionalOnMissingBeanBeansComponent.class.getSimpleName());
		}

		PrintSeparator();

		System.out.println("METHOD END.");
		
		PrintSeparator();
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	private static void TestAutoConfigurationBeans(String[] args)
	{
		PrintSeparator();

		System.out.println("METHOD START.");

		PrintSeparator();

		SpringApplication										springApplication=new SpringApplication(CAutoConfigurationBeansConfiguration.class);
		
		springApplication.setBannerMode(Banner.Mode.OFF);
		springApplication.setLogStartupInfo(false);

		Map<String,Object>										myProperties=new HashMap<String,Object>();
		
		myProperties.put("MyProperty1","AAA");
		myProperties.put("MyProperty2","111");
		
		// !!! Nastavia sa CUSTOM PROPERTIES.
		springApplication.setDefaultProperties(myProperties);
		
		ConfigurableApplicationContext							configurableApplicationContext=springApplication.run(args);

		PrintSeparator();
		
		try
		{
			CAutoConfigurationBeansComponent					component=configurableApplicationContext.getBean(CAutoConfigurationBeansComponent.class);
			
			component.Test();
		}
		catch(BeansException E)
		{
			System.out.printf("BEAN [%s] NOT FOUND.\n",CAutoConfigurationBeansComponent.class.getSimpleName());
		}

		PrintSeparator();

		System.out.println("METHOD END.");
		
		PrintSeparator();
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	private static void TestAutoConfigurationDebugging(String[] args)
	{
		PrintSeparator();

		System.out.println("METHOD START.");

		PrintSeparator();

		SpringApplication										springApplication=new SpringApplication(CAutoConfigurationBeansConfiguration.class);
		
		springApplication.setBannerMode(Banner.Mode.OFF);
		springApplication.setLogStartupInfo(false);

		Map<String,Object>										myProperties=new HashMap<String,Object>();
		
		myProperties.put("MyProperty1","AAA");
		myProperties.put("MyProperty2","111");
		
		// !!! Zapne sa DEBUG LOG pre AUTOCONFIGURATION SPRING MANAGED BEANS.
		myProperties.put("debug","true");
		
		// !!! Nastavia sa CUSTOM PROPERTIES.
		springApplication.setDefaultProperties(myProperties);
		
		ConfigurableApplicationContext							configurableApplicationContext=springApplication.run(args);

		PrintSeparator();
		
		try
		{
			CAutoConfigurationBeansComponent					component=configurableApplicationContext.getBean(CAutoConfigurationBeansComponent.class);
			
			component.Test();
		}
		catch(BeansException E)
		{
			System.out.printf("BEAN [%s] NOT FOUND.\n",CAutoConfigurationBeansComponent.class.getSimpleName());
		}

		PrintSeparator();

		System.out.println("METHOD END.");
		
		PrintSeparator();
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	private static void TestSpringExpressionLanguageExpressions(String[] args)
	{
		PrintSeparator();

		System.out.println("METHOD START.");

		PrintSeparator();

		List<String>											stringExpressions=new ArrayList<String>();
		
		stringExpressions.add("1+2*3 >= 7 and false");
		stringExpressions.add("'Hello '.concat('World').toUpperCase()");
		stringExpressions.add("new java.awt.Point(10,20).location.x");
		stringExpressions.add("{1,2,3,4}.get(0) == 1 ? 'one' : 'else'");
		stringExpressions.add("'12345' matches '\\d+'");
		stringExpressions.add("T(java.lang.Math).random()");
		
		for(String stringExpression : stringExpressions)
		{
			try
			{
				ExpressionParser								parser=new SpelExpressionParser();
				Expression										expression=parser.parseExpression(stringExpression);
				
				Object											result=expression.getValue();
				
				System.out.printf("EXPRESSION [%s] - VALUE [%s].\n",stringExpression,result);
			}
			catch(ParseException e)
			{
				System.out.printf("EXPRESSION [%s] - PARSE EXCEPTION [%s].\n",stringExpression,e.getMessage());
			}
			catch(EvaluationException e)
			{
				System.out.printf("EXPRESSION [%s] - EVALUATION EXCEPTION [%s].\n",stringExpression,e.getMessage());
			}
		}

		PrintSeparator();
		
		{
			String												stringExpression="T(java.lang.Math).random()";
			
			try
			{
				ExpressionParser								parser=new SpelExpressionParser();
				Expression										expression=parser.parseExpression(stringExpression);
				
				Double											result=expression.getValue(Double.class);
				
				System.out.printf("EXPRESSION [%s] - TYPE [%s] VALUE [%s].\n",stringExpression,result.getClass(),result);
			}
			catch(ParseException e)
			{
				System.out.printf("EXPRESSION [%s] - PARSE EXCEPTION [%s].\n",stringExpression,e.getMessage());
			}
			catch(EvaluationException e)
			{
				System.out.printf("EXPRESSION [%s] - EVALUATION EXCEPTION [%s].\n",stringExpression,e.getMessage());
			}
		}
		
		PrintSeparator();

		System.out.println("METHOD END.");
		
		PrintSeparator();
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	private static void TestConditionalOnExpressionBeans(String[] args)
	{
		PrintSeparator();

		System.out.println("METHOD START.");

		PrintSeparator();

		SpringApplication										springApplication=new SpringApplication(CConditionalOnExpressionBeansConfiguration.class);
		
		springApplication.setBannerMode(Banner.Mode.OFF);
		springApplication.setLogStartupInfo(false);
	
		ConfigurableApplicationContext							configurableApplicationContext=springApplication.run(args);

		PrintSeparator();
		
		{
			String												stringExpression="@MyBean3.GetText()";
			
			try
			{
				// !!!!! Pouzitie OPERATOR [@] v SPRING EXPRESSION LANGUAGE EXPRESSION.
				ExpressionParser								parser=new SpelExpressionParser();
				
				Expression										expression=parser.parseExpression(stringExpression);

				BeanFactory										beanFactory=configurableApplicationContext.getBeanFactory();

				BeanFactoryResolver								beanFactoryResolver=new BeanFactoryResolver(beanFactory);
				
				StandardEvaluationContext						context = new StandardEvaluationContext();				
				
				context.setBeanResolver(beanFactoryResolver);    
				
				Object											result=expression.getValue(context);
				
				System.out.printf("EXPRESSION [%s] - TYPE [%s] VALUE [%s].\n",stringExpression,result.getClass(),result);
			}
			catch(ParseException e)
			{
				System.out.printf("EXPRESSION [%s] - PARSE EXCEPTION [%s].\n",stringExpression,e.getMessage());
			}
			catch(EvaluationException e)
			{
				System.out.printf("EXPRESSION [%s] - EVALUATION EXCEPTION [%s].\n",stringExpression,e.getMessage());
			}
		}
		
		PrintSeparator();
		
		try
		{
			CConditionalOnExpressionBeansComponent				component=configurableApplicationContext.getBean(CConditionalOnExpressionBeansComponent.class);
			
			component.Test();
		}
		catch(BeansException E)
		{
			System.out.printf("BEAN [%s] NOT FOUND.\n",CConditionalOnExpressionBeansComponent.class.getSimpleName());
		}

		PrintSeparator();

		System.out.println("METHOD END.");
		
		PrintSeparator();
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	private static void TestCachable(String[] args)
	{
		PrintSeparator();

		System.out.println("METHOD START.");

		PrintSeparator();

		SpringApplication										springApplication=new SpringApplication(CCacheableBeansConfiguration.class);
		
		springApplication.setBannerMode(Banner.Mode.OFF);
		springApplication.setLogStartupInfo(false);
	
		ConfigurableApplicationContext							configurableApplicationContext=springApplication.run(args);

		PrintSeparator();
		
		try
		{
			CCacheableBeansComponent							component=configurableApplicationContext.getBean(CCacheableBeansComponent.class);
			
			component.Test();
		}
		catch(BeansException E)
		{
			System.out.printf("BEAN [%s] NOT FOUND.\n",CCacheableBeansComponent.class.getSimpleName());
		}

		PrintSeparator();

		System.out.println("METHOD END.");
		
		PrintSeparator();
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	private static void TestScheduled(String[] args)
	{
		PrintSeparator();

		System.out.println("METHOD START.");

		PrintSeparator();

		SpringApplication										springApplication=new SpringApplication(CScheduledBeansConfiguration.class);
		
		springApplication.setBannerMode(Banner.Mode.OFF);
		springApplication.setLogStartupInfo(false);
	
		ConfigurableApplicationContext							configurableApplicationContext=springApplication.run(args);

		PrintSeparator();
		
		try
		{
			CScheduledBeansComponent							component=configurableApplicationContext.getBean(CScheduledBeansComponent.class);
			
			component.Test();
		}
		catch(BeansException E)
		{
			System.out.printf("BEAN [%s] NOT FOUND.\n",CScheduledBeansComponent.class.getSimpleName());
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

		//TestInjectionTypes(args);
		//TestMissingBeans(args);
		//TestOptionalBeans(args);
		//TestCyclicDependencies(args);
		//TestNonBeansInjection(args);
		//TestBeanFactory(args);
		//TestVariousBeans(args);
		//TestMultipleSameTypeBeans(args);
		//TestBeanNamesConflict(args);
		//TestProxyTypes(args);
		//TestBeanInjectionPoints(args);
		//TestStaticFactoryMethods(args);
		//TestImportConfigurations(args);
		//TestNamedBeans(args);
		//TestBaseTypesBeans(args);
		//TestGenericTypesBeans(args);
		//TestBeanQualifiers(args);
		//TestPrimaryBeans(args);
		//TestCollectionBeans(args);
		//TestFallbackMatchInjection(args);
		//TestResourceAnnotations(args);
		//TestObjectProviders(args);
		//TestOrderedBeans(args);
		//TestInheritanceBeans(args);
		//TestInheritanceComponents(args);
		//TestInheritanceAutowired(args);
		//TestDependsOnBeans(args);
		//TestLazyBeans(args);
		//TestBeanInitializationProblem(args);
		//TestLifecycleEventsAnnotations(args);
		//TestLifecycleEventsInterfaces(args);
		//TestManualRegisteringBeans(args);
		//TestBeanPostProcessors(args);
		//TestListableBeanFactory(args);
		//TestHierarchicalContexts(args);
		//TestConditionalBeans(args);
		//TestConditionalOnPropertyBeans(args);
		//TestConditionalOnMissingBean(args);
		//TestAutoConfigurationBeans(args);
		//TestAutoConfigurationDebugging(args);
		//TestSpringExpressionLanguageExpressions(args);
		//TestConditionalOnExpressionBeans(args);
		//TestCachable(args);
		TestScheduled(args);
		
		System.out.println("MAIN END.");
		
		PrintSeparator();
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------