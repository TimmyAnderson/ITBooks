//----------------------------------------------------------------------------------------------------------------------
package main;
//----------------------------------------------------------------------------------------------------------------------
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
//----------------------------------------------------------------------------------------------------------------------
@Configuration
public class CProjectConfiguration1
{
//----------------------------------------------------------------------------------------------------------------------
	@Bean
	public CNotWiredBeanParent CreateNotWiredBeanParent()	
	{
		CNotWiredBeanParent										Bean=new CNotWiredBeanParent();
		
		Bean.setValue("Hello NOT WIRED PARENT !!!");
		
		return(Bean);
	}
//----------------------------------------------------------------------------------------------------------------------
	@Bean
	public CNotWiredBeanChild CreateNotWiredBeanChild()	
	{
		CNotWiredBeanChild										Bean=new CNotWiredBeanChild();
		
		Bean.setValue("Hello NOT WIRED CHILD !!!");
		
		return(Bean);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------