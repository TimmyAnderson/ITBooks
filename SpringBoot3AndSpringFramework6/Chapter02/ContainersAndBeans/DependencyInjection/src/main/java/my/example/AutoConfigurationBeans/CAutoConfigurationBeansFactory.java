package my.example.AutoConfigurationBeans;
//----------------------------------------------------------------------------------------------------------------------
import org.springframework.boot.autoconfigure.AutoConfiguration;
import org.springframework.boot.autoconfigure.condition.ConditionalOnProperty;

import org.springframework.context.annotation.Bean;
//----------------------------------------------------------------------------------------------------------------------
// !!! Aplikuje sa ANNOTATION [@AutoConfiguration].
@AutoConfiguration
public class CAutoConfigurationBeansFactory
{
//----------------------------------------------------------------------------------------------------------------------
	@Bean
	// !!! Aplikuje sa CONDITIONS. Iba ak su VSETKY splnene, tak je instancia BEAN vytvorena.
	@ConditionalOnProperty(name="MyProperty1",havingValue="AAA")
	@ConditionalOnProperty(name="MyProperty2",havingValue="111")
	public CAutoConfigurationBeansBean3 MyBean3()
	{
		CAutoConfigurationBeansBean3							bean=new CAutoConfigurationBeansBean3();
		
		return(bean);
	}
//----------------------------------------------------------------------------------------------------------------------
	@Bean
	// !!! Aplikuje sa CONDITIONS. Iba ak su VSETKY splnene, tak je instancia BEAN vytvorena.
	@ConditionalOnProperty(name="MyProperty1",havingValue="AAA")
	@ConditionalOnProperty(name="MyProperty2",havingValue="222")
	public CAutoConfigurationBeansBean4 MyBean4()
	{
		CAutoConfigurationBeansBean4							bean=new CAutoConfigurationBeansBean4();
		
		return(bean);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------