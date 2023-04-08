//----------------------------------------------------------------------------------------------------------------------
package SingletonByStereotype;
//----------------------------------------------------------------------------------------------------------------------
import org.springframework.context.annotation.ComponentScan;
import org.springframework.context.annotation.Configuration;
//----------------------------------------------------------------------------------------------------------------------
@Configuration
@ComponentScan(basePackageClasses={CSingletonByStereotypeBeanChild.class,CSingletonByStereotypeBeanParent1.class,CSingletonByStereotypeBeanParent2.class})
public class CSingletonByStereotypeConfiguration
{
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------