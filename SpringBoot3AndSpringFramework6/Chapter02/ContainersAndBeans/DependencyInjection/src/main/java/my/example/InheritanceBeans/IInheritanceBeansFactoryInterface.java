package my.example.InheritanceBeans;
//----------------------------------------------------------------------------------------------------------------------
import org.springframework.context.annotation.Bean;
//----------------------------------------------------------------------------------------------------------------------
public interface IInheritanceBeansFactoryInterface
{
//----------------------------------------------------------------------------------------------------------------------
	// !!! BEANS definovane ako DEFAULT METHODS v INTERFACES su INHERITED do DERIVED CLASS.
	@Bean
	default CInheritanceBeansBean2 CreateBean2()
	{
		CInheritanceBeansBean2									bean=new CInheritanceBeansBean2();
		
		return(bean);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------