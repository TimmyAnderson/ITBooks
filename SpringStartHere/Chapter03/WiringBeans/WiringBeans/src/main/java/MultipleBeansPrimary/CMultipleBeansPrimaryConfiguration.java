//----------------------------------------------------------------------------------------------------------------------
package MultipleBeansPrimary;
//----------------------------------------------------------------------------------------------------------------------
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.ComponentScan;
import org.springframework.context.annotation.Configuration;
import org.springframework.context.annotation.Primary;
//----------------------------------------------------------------------------------------------------------------------
@Configuration
@ComponentScan(basePackages="MultipleBeansPrimary")
public class CMultipleBeansPrimaryConfiguration
{
//----------------------------------------------------------------------------------------------------------------------
	// !!!!! Vytvara sa 1. instancia BEAN 'CMultipleBeansPrimaryChild'.
	// !!!!! BEAN je oznaceny ako PRIMARY.  
	@Bean
	@Primary
	public CMultipleBeansPrimaryChild CreateChildBean1()
	{
		CMultipleBeansPrimaryChild								Bean=new CMultipleBeansPrimaryChild();
		
		Bean.setValue("CHILD BEAN 1 !!!");

		return(Bean);
	}
//----------------------------------------------------------------------------------------------------------------------
	// !!!!! Vytvara sa 2. instancia BEAN 'CMultipleBeansPrimaryChild'.
	@Bean(name="OtherChild")
	public CMultipleBeansPrimaryChild CreateChildBean2()
	{
		CMultipleBeansPrimaryChild								Bean=new CMultipleBeansPrimaryChild();
		
		Bean.setValue("CHILD BEAN 2 !!!");

		return(Bean);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------