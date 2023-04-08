//----------------------------------------------------------------------------------------------------------------------
package MultipleBeansFieldQualifier;
//----------------------------------------------------------------------------------------------------------------------
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
//----------------------------------------------------------------------------------------------------------------------
@Configuration
public class CMultipleBeansFieldQualifierConfiguration
{
//----------------------------------------------------------------------------------------------------------------------
	// !!!!! Vytvara sa 1. instancia BEAN 'CMultipleBeansFieldQualifierChild'.
	// !!!!! NAZOV BEAN sa zhoduje s nazvom v ANNOTATION [@Qualifier].  
	@Bean("MyChild")
	public CMultipleBeansFieldQualifierChild CreateChildBean1()	
	{
		CMultipleBeansFieldQualifierChild						Bean=new CMultipleBeansFieldQualifierChild();
		
		Bean.setValue("CHILD BEAN 1 !!!");

		return(Bean);
	}
//----------------------------------------------------------------------------------------------------------------------
	// !!!!! Vytvara sa 2. instancia BEAN 'CMultipleBeansFieldQualifierChild'.
	@Bean(name="OtherChild")
	public CMultipleBeansFieldQualifierChild CreateChildBean2()	
	{
		CMultipleBeansFieldQualifierChild						Bean=new CMultipleBeansFieldQualifierChild();
		
		Bean.setValue("CHILD BEAN 2 !!!");

		return(Bean);
	}
//----------------------------------------------------------------------------------------------------------------------
	@Bean
	public CMultipleBeansFieldQualifierParent CreateParentBean()
	{
		CMultipleBeansFieldQualifierParent						Bean=new CMultipleBeansFieldQualifierParent();
		
		Bean.setValue("PARENT BEAN !!!");
		
		return(Bean);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------