//----------------------------------------------------------------------------------------------------------------------
package MultipleBeansFieldName;
//----------------------------------------------------------------------------------------------------------------------
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
//----------------------------------------------------------------------------------------------------------------------
@Configuration
public class CMultipleBeansFieldNameConfiguration
{
//----------------------------------------------------------------------------------------------------------------------
	// !!!!! Vytvara sa 1. instancia BEAN 'CMultipleBeansFieldNameChild'.
	// !!!!! NAZOV BEAN sa zhoduje s nazvom FIELD v BEAN 'CMultipleBeansFieldNameParent'.  
	@Bean(name="MChild")
	public CMultipleBeansFieldNameChild CreateChildBean1()	
	{
		CMultipleBeansFieldNameChild							Bean=new CMultipleBeansFieldNameChild();
		
		Bean.setValue("CHILD BEAN 1 !!!");

		return(Bean);
	}
//----------------------------------------------------------------------------------------------------------------------
	// !!!!! Vytvara sa 2. instancia BEAN 'CMultipleBeansFieldNameChild'.
	@Bean(name="OtherChild")
	public CMultipleBeansFieldNameChild CreateChildBean2()	
	{
		CMultipleBeansFieldNameChild							Bean=new CMultipleBeansFieldNameChild();
		
		Bean.setValue("CHILD BEAN 2 !!!");

		return(Bean);
	}
//----------------------------------------------------------------------------------------------------------------------
	@Bean
	public CMultipleBeansFieldNameParent CreateParentBean()
	{
		CMultipleBeansFieldNameParent							Bean=new CMultipleBeansFieldNameParent();
		
		Bean.setValue("PARENT BEAN !!!");
		
		return(Bean);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------