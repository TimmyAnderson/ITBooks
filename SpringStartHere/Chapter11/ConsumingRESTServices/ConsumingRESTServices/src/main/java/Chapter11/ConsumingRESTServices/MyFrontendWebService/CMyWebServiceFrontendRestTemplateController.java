package Chapter11.ConsumingRESTServices.MyFrontendWebService;
//----------------------------------------------------------------------------------------------------------------------
import java.util.Collection;
import java.util.Optional;
import java.util.UUID;
import org.springframework.http.HttpEntity;
import org.springframework.http.HttpHeaders;
import org.springframework.http.HttpMethod;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.util.LinkedMultiValueMap;
import org.springframework.util.MultiValueMap;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RestController;
import org.springframework.web.client.RestTemplate;
import Chapter11.ConsumingRESTServices.MyBackendWebService.CMyWebServiceBackendRequest;
import Chapter11.ConsumingRESTServices.MyBackendWebService.CMyWebServiceBackendResponse;
//----------------------------------------------------------------------------------------------------------------------
// !!!!! CONTROLLER implementuje FRONTEND SERVICE, ktory vola BACHEND SERVICE pomocou JAVA WEB CLIENT REST TEMPLATE.
@RestController
public class CMyWebServiceFrontendRestTemplateController
{
//----------------------------------------------------------------------------------------------------------------------
	private static String GetHeader(String HeaderName, HttpHeaders BackendHeaders)
	{
		Collection<String>										Values=BackendHeaders.get(HeaderName);

		if (Values!=null && Values.isEmpty()==false)
		{
			Optional<String>									Value=Values.stream().findFirst();
			
			if (Value.isPresent()==true)
			{
				return(Value.get());
			}
		}

		return("");
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	// CURL [curl -v -X POST localhost:8080/MyWebServiceFrontendRestTemplatePost -H "Content-Type: application/json" -d "{\"value1\":\"Jenny\",\"value2\":\"Thompson\"}"].
	@PostMapping("/MyWebServiceFrontendRestTemplatePost")
	public ResponseEntity<CMyWebServiceFrontendResponse2> MyWebServiceFrontendRestTemplatePost(@RequestBody CMyWebServiceFrontendRequest Request)
	{
		String													MyHeader1="CCC " + UUID.randomUUID().toString();
		String													MyHeader2="DDD " + UUID.randomUUID().toString();
		CMyWebServiceBackendRequest								BackendRequest=new CMyWebServiceBackendRequest(Request.getValue1(),Request.getValue2());
		
		// URL MUSI obsahovat PROTOCOL.
		String													RequestURL="http://localhost:8080/MyWebServiceBackendPost";
		HttpMethod												RequestHttpMethod=HttpMethod.POST;
		HttpHeaders												RequestHttpHeaders=new HttpHeaders();
		
		RequestHttpHeaders.add("MyHeader1",MyHeader1);
		RequestHttpHeaders.add("MyHeader2",MyHeader2);
		
		HttpEntity<CMyWebServiceBackendRequest>					RequestHttpEntity=new HttpEntity<CMyWebServiceBackendRequest>(BackendRequest,RequestHttpHeaders);
		RestTemplate											WebClientRestTemplate=new RestTemplate();
				
		// !!! Posledny PARAMETER je TYPE HTTP RESPONSE BODY.
		ResponseEntity<CMyWebServiceBackendResponse>			BackendResponse=WebClientRestTemplate.exchange(RequestURL,RequestHttpMethod,RequestHttpEntity,CMyWebServiceBackendResponse.class);
		HttpHeaders												ResponseHttpHeaders=BackendResponse.getHeaders();
		CMyWebServiceBackendResponse							BackendResponseBody=BackendResponse.getBody();

		String													FrontendID=UUID.randomUUID().toString();
		String													BackendResponseMyHeader1=GetHeader("MyHeader1",ResponseHttpHeaders);
		String													BackendResponseMyHeader2=GetHeader("MyHeader2",ResponseHttpHeaders);
		String													BackendID=BackendResponseBody.getBackendID();
		String													Value1=BackendResponseBody.getValue1();
		String													Value2=BackendResponseBody.getValue2();
		CMyWebServiceFrontendResponse2							ResponseBody=new CMyWebServiceFrontendResponse2(FrontendID,BackendResponseMyHeader1,BackendResponseMyHeader2,BackendID,Value1,Value2);
		MultiValueMap<String,String>							ResponseHeaders=new LinkedMultiValueMap<String,String>();
		HttpStatus												ResponseStatus=HttpStatus.OK;
		ResponseEntity<CMyWebServiceFrontendResponse2>			Response=new ResponseEntity<CMyWebServiceFrontendResponse2>(ResponseBody,ResponseHeaders,ResponseStatus);
		
		return(Response);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------