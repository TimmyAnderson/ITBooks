package my.example.LifecycleEventsInterfaces;
//----------------------------------------------------------------------------------------------------------------------
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
//----------------------------------------------------------------------------------------------------------------------
@Configuration
public class CLifecycleEventsInterfacesFactory
{
//----------------------------------------------------------------------------------------------------------------------
	@Bean
	public CLifecycleEventsInterfacesBean2 MyBean2()
	{
		CLifecycleEventsInterfacesBean2							bean=new CLifecycleEventsInterfacesBean2();

		return(bean);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------