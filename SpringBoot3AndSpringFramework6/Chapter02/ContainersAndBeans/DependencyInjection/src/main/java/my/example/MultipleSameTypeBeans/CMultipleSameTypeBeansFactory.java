package my.example.MultipleSameTypeBeans;
//----------------------------------------------------------------------------------------------------------------------
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
//----------------------------------------------------------------------------------------------------------------------
@Configuration
public class CMultipleSameTypeBeansFactory
{
//----------------------------------------------------------------------------------------------------------------------
	// !!! BEAN ma NAME [MyBean1].
	@Bean
	public CMultipleSameTypeBeansBean MyBean1()
	{
		CMultipleSameTypeBeansBean								bean=new CMultipleSameTypeBeansBean("111");
		
		return(bean);
	}
//----------------------------------------------------------------------------------------------------------------------
	// !!! BEAN ma NAME [MyBean2].
	@Bean
	public CMultipleSameTypeBeansBean MyBean2()
	{
		CMultipleSameTypeBeansBean								bean=new CMultipleSameTypeBeansBean("222");
		
		return(bean);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------