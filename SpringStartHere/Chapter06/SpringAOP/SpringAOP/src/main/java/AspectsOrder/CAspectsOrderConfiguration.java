//----------------------------------------------------------------------------------------------------------------------
package AspectsOrder;
//----------------------------------------------------------------------------------------------------------------------
import org.springframework.context.annotation.ComponentScan;
import org.springframework.context.annotation.Configuration;
import org.springframework.context.annotation.EnableAspectJAutoProxy;
//----------------------------------------------------------------------------------------------------------------------
@Configuration
@ComponentScan(basePackageClasses={CAspectsOrderBean.class,CAspectsOrderAspect1.class,CAspectsOrderAspect2.class})
@EnableAspectJAutoProxy
public class CAspectsOrderConfiguration
{
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------