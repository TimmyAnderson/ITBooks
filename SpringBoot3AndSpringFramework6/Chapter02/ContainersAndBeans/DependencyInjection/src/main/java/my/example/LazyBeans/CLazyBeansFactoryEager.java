package my.example.LazyBeans;
//----------------------------------------------------------------------------------------------------------------------
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
import org.springframework.context.annotation.Lazy;
//----------------------------------------------------------------------------------------------------------------------
@Configuration
public class CLazyBeansFactoryEager
{
//----------------------------------------------------------------------------------------------------------------------
	@Lazy(true)
	@Bean
	public CLazyBeansBean3 MyBean3()
	{
		CLazyBeansBean3											bean=new CLazyBeansBean3();
		
		return(bean);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------