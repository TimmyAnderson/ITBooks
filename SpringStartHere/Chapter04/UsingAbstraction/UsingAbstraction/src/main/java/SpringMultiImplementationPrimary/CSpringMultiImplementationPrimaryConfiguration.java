//----------------------------------------------------------------------------------------------------------------------
package SpringMultiImplementationPrimary;
//----------------------------------------------------------------------------------------------------------------------
import org.springframework.context.annotation.ComponentScan;
import org.springframework.context.annotation.Configuration;
//----------------------------------------------------------------------------------------------------------------------
@Configuration
// !!!!! Vykona sa SCAN konkretnych CLASSES, namiesto SCAN celych PACKAGES. Tento sposob je VYHODNEJSI, lebo je TYPE SAFE.
@ComponentScan(basePackageClasses={CSpringMultiImplementationPrimaryPrintA1.class,CSpringMultiImplementationPrimaryPrintB1.class,CSpringMultiImplementationPrimaryPrinter.class}) 
public class CSpringMultiImplementationPrimaryConfiguration
{
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------