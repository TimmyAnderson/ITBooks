//----------------------------------------------------------------------------------------------------------------------
package SpringMultiImplementationQualifier;
//----------------------------------------------------------------------------------------------------------------------
import org.springframework.context.annotation.ComponentScan;
import org.springframework.context.annotation.Configuration;
//----------------------------------------------------------------------------------------------------------------------
@Configuration
// !!!!! Vykona sa SCAN konkretnych CLASSES, namiesto SCAN celych PACKAGES. Tento sposob je VYHODNEJSI, lebo je TYPE SAFE.
@ComponentScan(basePackageClasses={CSpringMultiImplementationQualifierPrintA1.class,CSpringMultiImplementationQualifierPrintB1.class,CSpringMultiImplementationQualifierPrinter1.class,CSpringMultiImplementationQualifierPrinter2.class}) 
public class CSpringMultiImplementationQualifierConfiguration
{
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------