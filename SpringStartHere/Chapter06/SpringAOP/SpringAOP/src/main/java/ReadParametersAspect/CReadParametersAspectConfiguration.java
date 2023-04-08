//----------------------------------------------------------------------------------------------------------------------
package ReadParametersAspect;
//----------------------------------------------------------------------------------------------------------------------
import org.springframework.context.annotation.ComponentScan;
import org.springframework.context.annotation.Configuration;
import org.springframework.context.annotation.EnableAspectJAutoProxy;
//----------------------------------------------------------------------------------------------------------------------
@Configuration
@ComponentScan(basePackageClasses={CReadParametersAspectBean.class,CReadParametersAspectAspect.class})
@EnableAspectJAutoProxy
public class CReadParametersAspectConfiguration
{
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------