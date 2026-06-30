package my.example.StaticFactoryMethods;
//----------------------------------------------------------------------------------------------------------------------
import org.springframework.context.annotation.Bean;

import org.springframework.context.annotation.Configuration;
//----------------------------------------------------------------------------------------------------------------------
@Configuration
public class CStaticFactoryMethodsFactory
{
//----------------------------------------------------------------------------------------------------------------------
	// !!! FACTORY METHOD moze byt aj STATIC.
	@Bean
	public static CStaticFactoryMethodsBean MyBean()
	{
		CStaticFactoryMethodsBean								bean=new CStaticFactoryMethodsBean();
		
		return(bean);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------