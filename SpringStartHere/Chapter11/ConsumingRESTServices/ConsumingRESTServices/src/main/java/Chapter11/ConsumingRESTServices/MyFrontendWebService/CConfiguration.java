package Chapter11.ConsumingRESTServices.MyFrontendWebService;
//----------------------------------------------------------------------------------------------------------------------
import org.springframework.cloud.openfeign.EnableFeignClients;
import org.springframework.context.annotation.Configuration;
//----------------------------------------------------------------------------------------------------------------------
@Configuration
// !!! ANNOTATION [@EnableFeignClients] definuje, ktore INTERFACES definuju WEB CLIENT OPEN FEIGN.
@EnableFeignClients(basePackageClasses={IWebClientOpenFeignInterface.class})
public class CConfiguration
{
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------