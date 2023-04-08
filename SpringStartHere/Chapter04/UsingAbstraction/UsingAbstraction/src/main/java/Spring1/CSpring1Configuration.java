//----------------------------------------------------------------------------------------------------------------------
package Spring1;
//----------------------------------------------------------------------------------------------------------------------
import org.springframework.context.annotation.ComponentScan;
import org.springframework.context.annotation.Configuration;
//----------------------------------------------------------------------------------------------------------------------
@Configuration
// !!!!! Vykona sa SCAN konkretnych CLASSES, namiesto SCAN celych PACKAGES. Tento sposob je VYHODNEJSI, lebo je TYPE SAFE.
@ComponentScan(basePackageClasses={CSpring1PrintA1.class,CSpring1PrintB1.class,CSpring1Printer.class}) 
public class CSpring1Configuration
{
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------