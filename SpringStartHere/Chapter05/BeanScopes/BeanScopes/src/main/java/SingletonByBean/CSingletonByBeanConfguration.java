//----------------------------------------------------------------------------------------------------------------------
package SingletonByBean;
//----------------------------------------------------------------------------------------------------------------------
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
//----------------------------------------------------------------------------------------------------------------------
@Configuration
public class CSingletonByBeanConfguration
{
//----------------------------------------------------------------------------------------------------------------------
	@Bean(name="BEAN_1")
	public CSingletonByBeanBean CreateBean1()
	{
		CSingletonByBeanBean									Bean=new CSingletonByBeanBean("BEAN 1"); 
	
		return(Bean);	
	}
//----------------------------------------------------------------------------------------------------------------------
	@Bean(name="BEAN_2")
	public CSingletonByBeanBean CreateBean2()
	{
		CSingletonByBeanBean									Bean=new CSingletonByBeanBean("BEAN 2"); 

		return(Bean);	
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------