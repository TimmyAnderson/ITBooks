//----------------------------------------------------------------------------------------------------------------------
package AspectAfter;
//----------------------------------------------------------------------------------------------------------------------
import org.springframework.context.annotation.ComponentScan;
import org.springframework.context.annotation.Configuration;
import org.springframework.context.annotation.EnableAspectJAutoProxy;
//----------------------------------------------------------------------------------------------------------------------
@Configuration
@ComponentScan(basePackageClasses={CAspectAfterBean.class,CAspectAfterAspect.class})
@EnableAspectJAutoProxy
public class CAspectAfterConfiguration
{
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------