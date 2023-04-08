//----------------------------------------------------------------------------------------------------------------------
package AspectAfterReturning;
//----------------------------------------------------------------------------------------------------------------------
import org.springframework.context.annotation.ComponentScan;
import org.springframework.context.annotation.Configuration;
import org.springframework.context.annotation.EnableAspectJAutoProxy;
//----------------------------------------------------------------------------------------------------------------------
@Configuration
@ComponentScan(basePackageClasses={CAspectAfterReturningBean.class,CAspectAfterReturningAspect.class})
@EnableAspectJAutoProxy
public class CAspectAfterReturningConfiguration
{
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------