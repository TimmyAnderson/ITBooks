package my.example.ImportConfigurations3;
//----------------------------------------------------------------------------------------------------------------------
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
//----------------------------------------------------------------------------------------------------------------------
@Configuration
public class CImportConfigurations3Factory
{
//----------------------------------------------------------------------------------------------------------------------
	@Bean
	public CImportConfigurations3Bean MyBean3()
	{
		CImportConfigurations3Bean								bean=new CImportConfigurations3Bean();
		
		return(bean);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------