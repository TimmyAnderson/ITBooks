package my.example.InheritanceBeans;
//----------------------------------------------------------------------------------------------------------------------
import org.springframework.context.annotation.Bean;
//----------------------------------------------------------------------------------------------------------------------
public class CInheritanceBeansFactoryBaseClass
{
//----------------------------------------------------------------------------------------------------------------------
	// !!! BEANS definovane ako BASE CLASSES su INHERITED do DERIVED CLASS.
	@Bean
	public CInheritanceBeansBean1 CreateBean1()
	{
		CInheritanceBeansBean1									bean=new CInheritanceBeansBean1();
		
		return(bean);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------