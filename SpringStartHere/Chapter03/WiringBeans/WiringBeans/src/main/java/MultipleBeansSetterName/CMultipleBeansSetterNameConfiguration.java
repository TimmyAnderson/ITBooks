//----------------------------------------------------------------------------------------------------------------------
package MultipleBeansSetterName;
//----------------------------------------------------------------------------------------------------------------------
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.ComponentScan;
import org.springframework.context.annotation.Configuration;
//----------------------------------------------------------------------------------------------------------------------
@Configuration
@ComponentScan(basePackages="MultipleBeansSetterName")
public class CMultipleBeansSetterNameConfiguration
{
//----------------------------------------------------------------------------------------------------------------------
	// !!!!! Vytvara sa 1. instancia BEAN 'CMultipleBeansSetterNameChild'.
	// !!!!! NAZOV BEAN sa zhoduje s nazvom SETTER PARAMETER v BEAN 'CMultipleBeansSetterNameParent'.  
	@Bean(name="ChildParameter")
	public CMultipleBeansSetterNameChild CreateChildBean1()	
	{
		CMultipleBeansSetterNameChild							Bean=new CMultipleBeansSetterNameChild();
		
		Bean.setValue("CHILD BEAN 1 !!!");

		return(Bean);
	}
//----------------------------------------------------------------------------------------------------------------------
	// !!!!! Vytvara sa 2. instancia BEAN 'CMultipleBeansSetterNameChild'.
	@Bean(name="OtherChild")
	public CMultipleBeansSetterNameChild CreateChildBean2()	
	{
		CMultipleBeansSetterNameChild							Bean=new CMultipleBeansSetterNameChild();
		
		Bean.setValue("CHILD BEAN 2 !!!");

		return(Bean);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------