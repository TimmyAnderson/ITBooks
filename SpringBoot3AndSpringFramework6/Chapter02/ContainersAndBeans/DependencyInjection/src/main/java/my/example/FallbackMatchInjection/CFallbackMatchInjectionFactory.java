package my.example.FallbackMatchInjection;
//----------------------------------------------------------------------------------------------------------------------
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
//----------------------------------------------------------------------------------------------------------------------
@Configuration
public class CFallbackMatchInjectionFactory
{
//----------------------------------------------------------------------------------------------------------------------
	@Bean
	public CFallbackMatchInjectionBean3 MyBean3()
	{
		CFallbackMatchInjectionBean3							bean=new CFallbackMatchInjectionBean3();
		
		return(bean);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------