package my.example.BeansFactoryMethods;
//----------------------------------------------------------------------------------------------------------------------
import java.util.Optional;

import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
//----------------------------------------------------------------------------------------------------------------------
// !!! FACTORY CLASS MUSI byt oznacena pomocou ANNOTATION [@Configuration].
@Configuration
public class CBeansFactoryMethodsFactory
{
//----------------------------------------------------------------------------------------------------------------------
	// !!! FACTORY METHOD MUSI byt oznacena pomocou ANNOTATION [@Bean].
	// !!!!! FACTORY METHOD MOZE mat PARAMETERS, ktore sa subsituuju pomocou DEPENDENCY INJECTION.
	// !!!!! CLASS [CBeansFactoryMethodsNotBean] NIE je BEAN a je prenasana ako OPTIONAL BEAN.
	@Bean
	public CBeansFactoryMethodsBeanWithDependencies MyBeanWithDependencies(CBeansFactoryMethodsBean1 bean1, CBeansFactoryMethodsBean2 bean2, Optional<CBeansFactoryMethodsNotBean> notBean)
	{
		System.out.printf("!!! BEAN WITH DEPENDENCIES CREATED.\n");

		CBeansFactoryMethodsBeanWithDependencies				bean=new CBeansFactoryMethodsBeanWithDependencies(bean1,bean2,notBean);
		
		return(bean);
	}
//----------------------------------------------------------------------------------------------------------------------
	// !!! FACTORY METHOD MUSI byt oznacena pomocou ANNOTATION [@Bean].
	@Bean
	public CBeansFactoryMethodsBean1 MyBean1()
	{
		System.out.printf("!!! BEAN 1 CREATED.\n");
		
		CBeansFactoryMethodsBean1								bean=new CBeansFactoryMethodsBean1();
		
		return(bean);
	}
//----------------------------------------------------------------------------------------------------------------------
	// !!! FACTORY METHOD MUSI byt oznacena pomocou ANNOTATION [@Bean].
	@Bean
	public CBeansFactoryMethodsBean2 MyBean2()
	{
		System.out.printf("!!! BEAN 2 CREATED.\n");
		
		CBeansFactoryMethodsBean2								bean=new CBeansFactoryMethodsBean2();
		
		return(bean);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------