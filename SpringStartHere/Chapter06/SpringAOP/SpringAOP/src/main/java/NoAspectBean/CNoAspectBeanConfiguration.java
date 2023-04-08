//----------------------------------------------------------------------------------------------------------------------
package NoAspectBean;
//----------------------------------------------------------------------------------------------------------------------
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.ComponentScan;
import org.springframework.context.annotation.Configuration;
//----------------------------------------------------------------------------------------------------------------------
@Configuration
@ComponentScan(basePackageClasses={CNoAspectBeanBean1.class})
public class CNoAspectBeanConfiguration
{
//----------------------------------------------------------------------------------------------------------------------
	@Bean
	public CNoAspectBeanBean2 CreateBean2()
	{
		CNoAspectBeanBean2										Bean=new CNoAspectBeanBean2();
		
		return(Bean);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------