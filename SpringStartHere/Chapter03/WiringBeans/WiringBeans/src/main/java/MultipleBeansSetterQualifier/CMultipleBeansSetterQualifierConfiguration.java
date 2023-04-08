//----------------------------------------------------------------------------------------------------------------------
package MultipleBeansSetterQualifier;
//----------------------------------------------------------------------------------------------------------------------
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.ComponentScan;
import org.springframework.context.annotation.Configuration;
//----------------------------------------------------------------------------------------------------------------------
@Configuration
@ComponentScan(basePackages="MultipleBeansSetterQualifier")
public class CMultipleBeansSetterQualifierConfiguration
{
//----------------------------------------------------------------------------------------------------------------------
	// !!!!! Vytvara sa 1. instancia BEAN 'CMultipleBeansSetterQualifierChild'.
	// !!!!! NAZOV BEAN sa zhoduje s nazvom v ANNOTATION [@Qualifier].  
	@Bean(name="MyChild")
	public CMultipleBeansSetterQualifierChild CreateChildBean1()	
	{
		CMultipleBeansSetterQualifierChild						Bean=new CMultipleBeansSetterQualifierChild();
		
		Bean.setValue("CHILD BEAN 1 !!!");

		return(Bean);
	}
//----------------------------------------------------------------------------------------------------------------------
	// !!!!! Vytvara sa 2. instancia BEAN 'CMultipleBeansSetterQualifierChild'.
	@Bean(name="OtherChild")
	public CMultipleBeansSetterQualifierChild CreateChildBean2()	
	{
		CMultipleBeansSetterQualifierChild						Bean=new CMultipleBeansSetterQualifierChild();
		
		Bean.setValue("CHILD BEAN 2 !!!");

		return(Bean);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------