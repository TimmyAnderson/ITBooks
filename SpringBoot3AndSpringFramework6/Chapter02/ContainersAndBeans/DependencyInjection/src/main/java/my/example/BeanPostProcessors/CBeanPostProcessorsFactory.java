package my.example.BeanPostProcessors;
//----------------------------------------------------------------------------------------------------------------------
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
//----------------------------------------------------------------------------------------------------------------------
@Configuration
public class CBeanPostProcessorsFactory
{
//----------------------------------------------------------------------------------------------------------------------
	// !!!!!! BEAN POST PROCESSOR BEANS by mali byt zaregistrovane pomocou STATIC FACTORY METHODS.
	@Bean
	static public CBeanPostProcessorsPostProcessor2 myPostProcessorBean2()
	{
		CBeanPostProcessorsPostProcessor2						bean=new CBeanPostProcessorsPostProcessor2();
		
		return(bean);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------