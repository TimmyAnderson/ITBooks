//----------------------------------------------------------------------------------------------------------------------
package MyLogAspect;
//----------------------------------------------------------------------------------------------------------------------
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.ComponentScan;
import org.springframework.context.annotation.Configuration;
import org.springframework.context.annotation.EnableAspectJAutoProxy;
//----------------------------------------------------------------------------------------------------------------------
@Configuration
@ComponentScan(basePackageClasses={CMyLogAspectBean.class,CMyLogAspectAspect1.class})
@EnableAspectJAutoProxy
public class CMyLogAspectConfiguration
{
//----------------------------------------------------------------------------------------------------------------------
	// !!! METHOD vytvara BEAN, ktory reprezentuje ASPECT.
	@Bean
	public CMyLogAspectAspect2 CreateAspect()
	{
		CMyLogAspectAspect2										Aspect=new CMyLogAspectAspect2();
		
		return(Aspect); 
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------