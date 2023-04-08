package Chapter11.ConsumingRESTServices.MyFrontendWebService;
//----------------------------------------------------------------------------------------------------------------------
import feign.Response;
import java.io.IOException;
import java.nio.charset.Charset;
import java.util.Collection;
import java.util.Optional;
import java.util.UUID;
import org.apache.commons.io.IOUtils;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.util.LinkedMultiValueMap;
import org.springframework.util.MultiValueMap;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RestController;
import com.fasterxml.jackson.core.exc.StreamReadException;
import com.fasterxml.jackson.databind.DatabindException;
import com.fasterxml.jackson.databind.ObjectMapper;
import Chapter11.ConsumingRESTServices.MyBackendWebService.CMyWebServiceBackendRequest;
import Chapter11.ConsumingRESTServices.MyBackendWebService.CMyWebServiceBackendResponse;
//----------------------------------------------------------------------------------------------------------------------
// !!!!! CONTROLLER implementuje FRONTEND SERVICE, ktory vola BACHEND SERVICE pomocou JAVA WEB CLIENT OPEN FEIND.
@RestController
public class CMyWebServiceFrontendOpenFeindController
{
//----------------------------------------------------------------------------------------------------------------------
	// !!! SPRING vrati cez DEPENDENCY INJECTION INTERNU implementaciu INTERFACE, ktoru pre INTERFACE vygeneroval.
	private final IWebClientOpenFeignInterface					MWebClientOpenFeignInterface;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	@Autowired
	public CMyWebServiceFrontendOpenFeindController(IWebClientOpenFeignInterface WebClientOpenFeignInterface)
	{
		MWebClientOpenFeignInterface=WebClientOpenFeignInterface;
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	private static String GetHeader(String HeaderName, Response BackendResponse)
	{
		Collection<String>										Values=BackendResponse.headers().get(HeaderName);

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
	// CURL [curl -v -X POST localhost:8080/MyWebServiceFrontendOpenFeignPost1 -H "Content-Type: application/json" -d "{\"value1\":\"Jenny\",\"value2\":\"Thompson\"}"].
	@PostMapping("/MyWebServiceFrontendOpenFeignPost1")
	public ResponseEntity<CMyWebServiceFrontendResponse1> MyWebServiceFrontendOpenFeignPost1(@RequestBody CMyWebServiceFrontendRequest Request)
	{
		String													MyHeader1=UUID.randomUUID().toString();
		String													MyHeader2=UUID.randomUUID().toString();
		CMyWebServiceBackendRequest								BackendRequest=new CMyWebServiceBackendRequest(Request.getValue1(),Request.getValue2());
		CMyWebServiceBackendResponse							BackendResponse=MWebClientOpenFeignInterface.MyWebServiceBackendPost1(MyHeader1,MyHeader2,BackendRequest);

		String													FrontendID=UUID.randomUUID().toString();
		String													BackendID=BackendResponse.getBackendID();
		String													Value1=BackendResponse.getValue1();
		String													Value2=BackendResponse.getValue2();
		CMyWebServiceFrontendResponse1							ResponseBody=new CMyWebServiceFrontendResponse1(FrontendID,BackendID,Value1,Value2);
		MultiValueMap<String,String>							ResponseHeaders=new LinkedMultiValueMap<String,String>();
		HttpStatus												ResponseStatus=HttpStatus.OK;
		ResponseEntity<CMyWebServiceFrontendResponse1>			Response=new ResponseEntity<CMyWebServiceFrontendResponse1>(ResponseBody,ResponseHeaders,ResponseStatus);
		
		return(Response);
	}
//----------------------------------------------------------------------------------------------------------------------
	// CURL [curl -v -X POST localhost:8080/MyWebServiceFrontendOpenFeignPost2 -H "Content-Type: application/json" -d "{\"value1\":\"Jenny\",\"value2\":\"Thompson\"}"].
	@PostMapping("/MyWebServiceFrontendOpenFeignPost2")
	public ResponseEntity<CMyWebServiceFrontendResponse2> MyWebServiceFrontendOpenFeignPost2(@RequestBody CMyWebServiceFrontendRequest Request) throws StreamReadException, DatabindException, IOException
	{
		String													MyHeader1="AAA " + UUID.randomUUID().toString();
		String													MyHeader2="BBB " + UUID.randomUUID().toString();
		CMyWebServiceBackendRequest								BackendRequest=new CMyWebServiceBackendRequest(Request.getValue1(),Request.getValue2());
		
		Response												BackendResponse=MWebClientOpenFeignInterface.MyWebServiceBackendPost2(MyHeader1,MyHeader2,BackendRequest);
		Charset													BackendResponseCharset=BackendResponse.charset();
		String													BackendResponseBodyContent=IOUtils.toString(BackendResponse.body().asInputStream(),BackendResponseCharset);
		ObjectMapper											Deserializer=new ObjectMapper();
		CMyWebServiceBackendResponse							BackendResponseBody=Deserializer.readValue(BackendResponseBodyContent,CMyWebServiceBackendResponse.class);
		String													FrontendID=UUID.randomUUID().toString();
		String													BackendResponseMyHeader1=GetHeader("MyHeader1",BackendResponse);
		String													BackendResponseMyHeader2=GetHeader("MyHeader2",BackendResponse);
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