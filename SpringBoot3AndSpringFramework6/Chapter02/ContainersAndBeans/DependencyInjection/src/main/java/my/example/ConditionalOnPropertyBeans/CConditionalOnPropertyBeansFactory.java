package my.example.ConditionalOnPropertyBeans;
//----------------------------------------------------------------------------------------------------------------------
import org.springframework.boot.autoconfigure.condition.ConditionalOnProperty;

import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
//----------------------------------------------------------------------------------------------------------------------
@Configuration
public class CConditionalOnPropertyBeansFactory
{
//----------------------------------------------------------------------------------------------------------------------
	@Bean
	// !!! Aplikuje sa CONDITION.
	@ConditionalOnProperty(name="MyProperty",havingValue="AAA")
	public CConditionalOnPropertyBeansBean3 MyBean3()
	{
		CConditionalOnPropertyBeansBean3						bean=new CConditionalOnPropertyBeansBean3();
		
		return(bean);
	}
//----------------------------------------------------------------------------------------------------------------------
	@Bean
	// !!! Aplikuje sa CONDITION.
	@ConditionalOnProperty(name="MyProperty",havingValue="BBB")
	public CConditionalOnPropertyBeansBean4 MyBean4()
	{
		CConditionalOnPropertyBeansBean4						bean=new CConditionalOnPropertyBeansBean4();
		
		return(bean);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------