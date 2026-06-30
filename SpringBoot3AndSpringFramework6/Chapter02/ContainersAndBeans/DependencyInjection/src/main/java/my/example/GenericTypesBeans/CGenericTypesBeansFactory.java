package my.example.GenericTypesBeans;
//----------------------------------------------------------------------------------------------------------------------
import java.util.UUID;

import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
import org.springframework.context.annotation.Primary;
//----------------------------------------------------------------------------------------------------------------------
@Configuration
public class CGenericTypesBeansFactory
{
//----------------------------------------------------------------------------------------------------------------------
	@Bean
	public CGenericTypesBeansBean<String> MyBean1()
	{
		CGenericTypesBeansBean<String>							bean=new CGenericTypesBeansBean<String>(UUID.randomUUID().toString(),"Timmy");
		
		return(bean);
	}
//----------------------------------------------------------------------------------------------------------------------
	@Bean
	public CGenericTypesBeansBean<Integer> MyBean2()
	{
		CGenericTypesBeansBean<Integer>							bean=new CGenericTypesBeansBean<Integer>(UUID.randomUUID().toString(),12);
		
		return(bean);
	}
//----------------------------------------------------------------------------------------------------------------------
	@Bean
	@Primary
	public Boolean MyGenericParameterBean1()
	{
		Boolean													bean=true;
		
		return(bean);
	}
//----------------------------------------------------------------------------------------------------------------------
	@Bean
	public Double MyGenericParameterBean2()
	{
		Double													bean=123.456;
		
		return(bean);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------