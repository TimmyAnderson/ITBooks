//----------------------------------------------------------------------------------------------------------------------
package main;
//----------------------------------------------------------------------------------------------------------------------
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
//----------------------------------------------------------------------------------------------------------------------
@Configuration
public class CProjectConfiguration3
{
//----------------------------------------------------------------------------------------------------------------------
	@Bean
	// !!!!! Instancia BEAN 'CAutoWiredBeanChild' je vytvorena SPRING FRAMEWORK pomocou DEPENDENCY INJECTION.
	public CAutoWiredBeanParent CreateAutoWiredBeanParent(CAutoWiredBeanChild BeanChild)	
	{
		System.out.println("CreateAutoWiredBeanParent() CALLED !");
		
		CAutoWiredBeanParent									Bean=new CAutoWiredBeanParent();
		
		Bean.setValue("Hello AUTO WIRED PARENT !!!");

		// !!! Vykona sa WIRING PARENT a CHILD BEAN.
		Bean.setChild(BeanChild);
		
		return(Bean);
	}
//----------------------------------------------------------------------------------------------------------------------
	@Bean
	public CAutoWiredBeanChild CreateAutoWiredBeanChild()
	{
		System.out.println("CreateAutoWiredBeanChild() CALLED !");
	
		CAutoWiredBeanChild										Bean=new CAutoWiredBeanChild();
		
		Bean.setValue("Hello AUTO WIRED CHILD !!!");
		
		return(Bean);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------