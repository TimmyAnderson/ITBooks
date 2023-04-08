//----------------------------------------------------------------------------------------------------------------------
package WriteParametersAspect;
//----------------------------------------------------------------------------------------------------------------------
import org.springframework.context.annotation.ComponentScan;
import org.springframework.context.annotation.Configuration;
import org.springframework.context.annotation.EnableAspectJAutoProxy;
//----------------------------------------------------------------------------------------------------------------------
@Configuration
@ComponentScan(basePackageClasses={CWriteParametersAspectBean.class,CWriteParametersAspectAspect.class})
@EnableAspectJAutoProxy
public class CWriteParametersAspectConfiguration
{
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------