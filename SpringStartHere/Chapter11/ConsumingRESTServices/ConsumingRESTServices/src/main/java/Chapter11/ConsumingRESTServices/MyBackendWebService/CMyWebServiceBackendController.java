package Chapter11.ConsumingRESTServices.MyBackendWebService;
//----------------------------------------------------------------------------------------------------------------------
import java.util.UUID;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.util.LinkedMultiValueMap;
import org.springframework.util.MultiValueMap;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestHeader;
import org.springframework.web.bind.annotation.RestController;
import Chapter11.ConsumingRESTServices.Helpers.CHelpers;
//----------------------------------------------------------------------------------------------------------------------
// !!!!! CONTROLLER implementuje BACKEND SERVICE, ktory je volany z FRONTEND SERVICE pomocou JAVA WEB CLIENT REST TEMPLATE.
@RestController
public class CMyWebServiceBackendController
{
//----------------------------------------------------------------------------------------------------------------------
	// !!! REST SERVICE, ktory sa bude volat z ineho WEB SERVICE.
	// CURL [curl -v -X POST localhost:8080/MyWebServiceBackendPost -H "Content-Type: application/json" -H "MyHeader1: 123" -H "MyHeader2: 456" -d "{\"value1\":\"Jenny\",\"value2\":\"Thompson\"}"].
	@PostMapping("/MyWebServiceBackendPost")
	public ResponseEntity<CMyWebServiceBackendResponse> MyWebServiceBackendPost(@RequestHeader String MyHeader1, @RequestHeader String MyHeader2, @RequestBody CMyWebServiceBackendRequest Request) throws InterruptedException
	{
		System.out.format("TIME [%s] - THREAD [%s] - BACKEND SERVICE STARTED !\n",CHelpers.GetTime(),Thread.currentThread().getId());

		String													BackendID=UUID.randomUUID().toString();
		String													FirstName=Request.getValue1().toUpperCase();
		String													LastName=Request.getValue2().toUpperCase();
		CMyWebServiceBackendResponse							ResponseBody=new CMyWebServiceBackendResponse(BackendID,FirstName,LastName);
		MultiValueMap<String,String>							ResponseHeaders=new LinkedMultiValueMap<String,String>();
		
		ResponseHeaders.add("MyHeader1",MyHeader1);
		ResponseHeaders.add("MyHeader2",MyHeader2);
		
		HttpStatus												ResponseStatus=HttpStatus.OK;
		ResponseEntity<CMyWebServiceBackendResponse>			Response=new ResponseEntity<CMyWebServiceBackendResponse>(ResponseBody,ResponseHeaders,ResponseStatus);

		// !!! Umyselne sa spravi kratky THREAD SLEEP.
		Thread.sleep(500);

		System.out.format("TIME [%s] - THREAD [%s] - BACKEND SERVICE FINISHED !\n",CHelpers.GetTime(),Thread.currentThread().getId());
		
		return(Response);
	}	
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------