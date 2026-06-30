package my.example.InheritanceBeans;
//----------------------------------------------------------------------------------------------------------------------
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
//----------------------------------------------------------------------------------------------------------------------
@Configuration
public class CInheritanceBeansFactoryDerivedClass extends CInheritanceBeansFactoryBaseClass implements IInheritanceBeansFactoryInterface
{
//----------------------------------------------------------------------------------------------------------------------
	@Bean
	public CInheritanceBeansBean3 CreateBean3()
	{
		CInheritanceBeansBean3									bean=new CInheritanceBeansBean3();
		
		return(bean);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------