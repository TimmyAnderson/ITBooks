//----------------------------------------------------------------------------------------------------------------------
package SpringServiceRepository;
//----------------------------------------------------------------------------------------------------------------------
import org.springframework.context.annotation.ComponentScan;
import org.springframework.context.annotation.Configuration;
//----------------------------------------------------------------------------------------------------------------------
@Configuration
// !!!!! Vykona sa SCAN konkretnych CLASSES, namiesto SCAN celych PACKAGES. Tento sposob je VYHODNEJSI, lebo je TYPE SAFE.
@ComponentScan(basePackageClasses={CSpringServiceRepositoryPrintA1.class,CSpringServiceRepositoryPrintB1.class,CSpringServiceRepositoryPrinter1.class,CSpringServiceRepositoryPrinter2.class}) 
public class CSpringServiceRepositoryConfiguration
{
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------