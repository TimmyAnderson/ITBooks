package my.example.ImportConfigurations2;
//----------------------------------------------------------------------------------------------------------------------
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
//----------------------------------------------------------------------------------------------------------------------
@Configuration
public class CImportConfigurations2Factory
{
//----------------------------------------------------------------------------------------------------------------------
	@Bean
	public CImportConfigurations2Bean MyBean2()
	{
		CImportConfigurations2Bean								bean=new CImportConfigurations2Bean();
		
		return(bean);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------