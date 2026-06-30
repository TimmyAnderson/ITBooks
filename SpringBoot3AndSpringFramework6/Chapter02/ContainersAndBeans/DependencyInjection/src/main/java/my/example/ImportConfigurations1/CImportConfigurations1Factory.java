package my.example.ImportConfigurations1;
//----------------------------------------------------------------------------------------------------------------------
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
import org.springframework.context.annotation.Import;

import my.example.ImportConfigurations2.CImportConfigurations2Component;
import my.example.ImportConfigurations2.CImportConfigurations2Factory;
//----------------------------------------------------------------------------------------------------------------------
@Configuration
// !!!!! Vykona sa IMPORT z inych PACKAGES.
@Import({CImportConfigurations2Component.class,CImportConfigurations2Factory.class,CMyImportSelector.class})
public class CImportConfigurations1Factory
{
//----------------------------------------------------------------------------------------------------------------------
	@Bean
	public CImportConfigurations1Bean MyBean1()
	{
		CImportConfigurations1Bean								bean=new CImportConfigurations1Bean();
		
		return(bean);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------