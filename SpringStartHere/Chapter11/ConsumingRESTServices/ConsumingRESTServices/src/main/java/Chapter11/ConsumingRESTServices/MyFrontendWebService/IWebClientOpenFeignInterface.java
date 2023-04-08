package Chapter11.ConsumingRESTServices.MyFrontendWebService;
//----------------------------------------------------------------------------------------------------------------------
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestHeader;
import org.springframework.cloud.openfeign.FeignClient;
import org.springframework.web.bind.annotation.PostMapping;
import feign.Response;
import Chapter11.ConsumingRESTServices.MyBackendWebService.CMyWebServiceBackendRequest;
import Chapter11.ConsumingRESTServices.MyBackendWebService.CMyWebServiceBackendResponse;
//----------------------------------------------------------------------------------------------------------------------
// !!!!! Z tohto INTERFACE SPRING vygeneruje INTERNAL CLASS, ktora vola cez WEB CLIENT OPEN FEIGN WEB SERVICE.
@FeignClient(name="WebClientOpenFeign",url="http://localhost:8080")
public interface IWebClientOpenFeignInterface
{
//----------------------------------------------------------------------------------------------------------------------
	@PostMapping("/MyWebServiceBackendPost")
	CMyWebServiceBackendResponse MyWebServiceBackendPost1(@RequestHeader String MyHeader1, @RequestHeader String MyHeader2, @RequestBody CMyWebServiceBackendRequest Request);
//----------------------------------------------------------------------------------------------------------------------
	@PostMapping("/MyWebServiceBackendPost")
	Response MyWebServiceBackendPost2(@RequestHeader String MyHeader1, @RequestHeader String MyHeader2, @RequestBody CMyWebServiceBackendRequest Request);
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------