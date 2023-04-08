//----------------------------------------------------------------------------------------------------------------------
package AspectsOnAnnotations;
//----------------------------------------------------------------------------------------------------------------------
import org.springframework.context.annotation.ComponentScan;
import org.springframework.context.annotation.Configuration;
import org.springframework.context.annotation.EnableAspectJAutoProxy;
//----------------------------------------------------------------------------------------------------------------------
@Configuration
@ComponentScan(basePackageClasses={CAspectsOnAnnotationsBean.class,CAspectsOnAnnotationsAspect.class})
@EnableAspectJAutoProxy
public class CAspectsOnAnnotationsConfiguration
{
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------