//----------------------------------------------------------------------------------------------------------------------
package MultipleBeansConstructorParameterName;
//----------------------------------------------------------------------------------------------------------------------
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.ComponentScan;
import org.springframework.context.annotation.Configuration;
//----------------------------------------------------------------------------------------------------------------------
@Configuration
@ComponentScan(basePackages="MultipleBeansConstructorParameterName")
public class CMultipleBeansConstructorParameterNameConfiguration
{
//----------------------------------------------------------------------------------------------------------------------
	// !!!!! Vytvara sa 1. instancia BEAN 'CMultipleBeansConstructorParameterNameChild'.
	// !!!!! NAZOV BEAN sa zhoduje s nazvom CONSTRUCTOR PARAMETER v BEAN 'CMultipleBeansConstructorParameterNameParent'.  
	@Bean(name="Child")
	public CMultipleBeansConstructorParameterNameChild CreateChildBean1()
	{
		CMultipleBeansConstructorParameterNameChild							Bean=new CMultipleBeansConstructorParameterNameChild();
		
		Bean.setValue("CHILD BEAN 1 !!!");

		return(Bean);
	}
//----------------------------------------------------------------------------------------------------------------------
	// !!!!! Vytvara sa 2. instancia BEAN 'CMultipleBeansConstructorParameterNameChild'.
	@Bean(name="OtherChild")
	public CMultipleBeansConstructorParameterNameChild CreateChildBean2()
	{
		CMultipleBeansConstructorParameterNameChild				Bean=new CMultipleBeansConstructorParameterNameChild();
		
		Bean.setValue("CHILD BEAN 2 !!!");

		return(Bean);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------