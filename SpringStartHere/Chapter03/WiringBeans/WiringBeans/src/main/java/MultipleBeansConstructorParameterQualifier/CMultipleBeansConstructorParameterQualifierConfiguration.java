//----------------------------------------------------------------------------------------------------------------------
package MultipleBeansConstructorParameterQualifier;
//----------------------------------------------------------------------------------------------------------------------
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.ComponentScan;
import org.springframework.context.annotation.Configuration;
//----------------------------------------------------------------------------------------------------------------------
@Configuration
@ComponentScan(basePackages="MultipleBeansConstructorParameterQualifier")
public class CMultipleBeansConstructorParameterQualifierConfiguration
{
//----------------------------------------------------------------------------------------------------------------------
	// !!!!! Vytvara sa 1. instancia BEAN 'CMultipleBeansConstructorParameterQualifierChild'.
	// !!!!! NAZOV BEAN sa zhoduje s nazvom v CONSTRUCTOR PARAMETER ANNOTATION [@Qualifier] v BEAN 'CMultipleBeansConstructorParameterNameParent'.
	@Bean(name="MyChild")
	public CMultipleBeansConstructorParameterQualifierChild CreateChildBean1()
	{
		CMultipleBeansConstructorParameterQualifierChild		Bean=new CMultipleBeansConstructorParameterQualifierChild();
		
		Bean.setValue("CHILD BEAN 1 !!!");

		return(Bean);
	}
//----------------------------------------------------------------------------------------------------------------------
	// !!!!! Vytvara sa 2. instancia BEAN 'CMultipleBeansConstructorParameterQualifierChild'.
	@Bean(name="OtherChild")
	public CMultipleBeansConstructorParameterQualifierChild CreateChildBean2()
	{
		CMultipleBeansConstructorParameterQualifierChild		Bean=new CMultipleBeansConstructorParameterQualifierChild();
		
		Bean.setValue("CHILD BEAN 2 !!!");

		return(Bean);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------