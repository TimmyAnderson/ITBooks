//----------------------------------------------------------------------------------------------------------------------
package PrototypeBeanInSingletonBean;
//----------------------------------------------------------------------------------------------------------------------
import org.springframework.context.annotation.ComponentScan;
import org.springframework.context.annotation.Configuration;
//----------------------------------------------------------------------------------------------------------------------
@Configuration
@ComponentScan(basePackageClasses={CPrototypeBeanInSingletonBeanSingleton.class,CPrototypeBeanInSingletonBeanPrototype.class})
public class CPrototypeBeanInSingletonBeanConfiguration
{
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------