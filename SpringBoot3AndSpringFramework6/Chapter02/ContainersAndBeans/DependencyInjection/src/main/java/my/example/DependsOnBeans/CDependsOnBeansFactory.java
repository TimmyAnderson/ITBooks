package my.example.DependsOnBeans;
//----------------------------------------------------------------------------------------------------------------------
import org.springframework.context.ConfigurableApplicationContext;

import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
import org.springframework.context.annotation.DependsOn;
//----------------------------------------------------------------------------------------------------------------------
@Configuration
public class CDependsOnBeansFactory
{
//----------------------------------------------------------------------------------------------------------------------
	@Bean
	// !!!!! EXPLICITNE sa vytvori DEPENDENCY na inom BEAN.
	@DependsOn("MyDependentBean2")
	public CDependsOnBeansBean2 MyBean2(ConfigurableApplicationContext context)
	{
		CDependsOnBeansBean2									bean=new CDependsOnBeansBean2(context);
		
		return(bean);
	}
//----------------------------------------------------------------------------------------------------------------------
	@Bean
	public CDependsOnBeansBean4 MyBean4(ConfigurableApplicationContext context)
	{
		CDependsOnBeansBean4									bean=new CDependsOnBeansBean4(context);
		
		return(bean);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	@Bean
	public CDependsOnBeansDependentBean1 MyDependentBean1()
	{
		CDependsOnBeansDependentBean1							bean=new CDependsOnBeansDependentBean1();
		
		return(bean);
	}
//----------------------------------------------------------------------------------------------------------------------
	@Bean
	public CDependsOnBeansDependentBean2 MyDependentBean2()
	{
		CDependsOnBeansDependentBean2							bean=new CDependsOnBeansDependentBean2();
		
		return(bean);
	}
//----------------------------------------------------------------------------------------------------------------------
	@Bean
	public CDependsOnBeansDependentBean3 MyDependentBean3()
	{
		CDependsOnBeansDependentBean3							bean=new CDependsOnBeansDependentBean3();
		
		return(bean);
	}
//----------------------------------------------------------------------------------------------------------------------
	@Bean
	public CDependsOnBeansDependentBean4 MyDependentBean4()
	{
		CDependsOnBeansDependentBean4							bean=new CDependsOnBeansDependentBean4();
		
		return(bean);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------