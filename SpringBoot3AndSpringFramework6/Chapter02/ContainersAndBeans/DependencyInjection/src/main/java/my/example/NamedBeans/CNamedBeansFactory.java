package my.example.NamedBeans;
//----------------------------------------------------------------------------------------------------------------------
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
//----------------------------------------------------------------------------------------------------------------------
@Configuration
public class CNamedBeansFactory
{
//----------------------------------------------------------------------------------------------------------------------
	@Bean
	public CNamedBeansBean MyBeanDefaultName()
	{
		CNamedBeansBean											bean=new CNamedBeansBean("DEFAULT NAME");

		return(bean);
	}
//----------------------------------------------------------------------------------------------------------------------
	// !!! BEAN ma CUSTOM NAME a ALIAS.
	@Bean(value={"MyCustomBean1","MyCustomBean2"})
	public CNamedBeansBean MyBeanCustomName()
	{
		CNamedBeansBean											bean=new CNamedBeansBean("CUSTOM NAME");

		return(bean);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------