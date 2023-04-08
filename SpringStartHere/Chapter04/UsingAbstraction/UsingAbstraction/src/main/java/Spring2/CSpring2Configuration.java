//----------------------------------------------------------------------------------------------------------------------
package Spring2;
//----------------------------------------------------------------------------------------------------------------------
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
//----------------------------------------------------------------------------------------------------------------------
@Configuration
public class CSpring2Configuration
{
//----------------------------------------------------------------------------------------------------------------------
	// !!! METHOD vracia INTERFACE. 
	@Bean
	public ISpring2PrintA CreateBeanSpring2PrintA()
	{
		ISpring2PrintA											Bean=new CSpring2PrintA1();
		
		return(Bean);
	}
//----------------------------------------------------------------------------------------------------------------------
	// !!! METHOD vracia INTERFACE. 
	@Bean
	public ISpring2PrintB CreateBeanSpring2PrintB()
	{
		ISpring2PrintB											Bean=new CSpring2PrintB1();
		
		return(Bean);
	}
//----------------------------------------------------------------------------------------------------------------------
	@Bean
	public CSpring2Printer CreateBeanSpring2Printer()
	{
		CSpring2Printer											Bean=new CSpring2Printer();
		
		return(Bean);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------