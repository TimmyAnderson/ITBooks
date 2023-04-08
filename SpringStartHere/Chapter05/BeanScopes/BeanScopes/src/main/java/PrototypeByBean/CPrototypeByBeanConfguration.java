//----------------------------------------------------------------------------------------------------------------------
package PrototypeByBean;
//----------------------------------------------------------------------------------------------------------------------
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
import org.springframework.context.annotation.Scope;
import org.springframework.beans.factory.config.BeanDefinition;
//----------------------------------------------------------------------------------------------------------------------
@Configuration
public class CPrototypeByBeanConfguration
{
//----------------------------------------------------------------------------------------------------------------------
	@Bean(name="BEAN_1")
	// !!! BEAN je oznaceny ako PROROTYPE SCOPE BEAN.
	@Scope(BeanDefinition.SCOPE_PROTOTYPE) 
	public CPrototypeByBeanBean CreateBean1()
	{
		CPrototypeByBeanBean									Bean=new CPrototypeByBeanBean("BEAN 1"); 
	
		return(Bean);	
	}
//----------------------------------------------------------------------------------------------------------------------
	@Bean(name="BEAN_2")
	// !!! BEAN je oznaceny ako PROROTYPE SCOPE BEAN.
	@Scope(BeanDefinition.SCOPE_PROTOTYPE) 
	public CPrototypeByBeanBean CreateBean2()
	{
		CPrototypeByBeanBean									Bean=new CPrototypeByBeanBean("BEAN 2"); 

		return(Bean);	
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------