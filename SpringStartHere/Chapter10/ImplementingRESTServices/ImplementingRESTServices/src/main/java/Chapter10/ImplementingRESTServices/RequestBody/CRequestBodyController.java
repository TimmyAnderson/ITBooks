package Chapter10.ImplementingRESTServices.RequestBody;
//----------------------------------------------------------------------------------------------------------------------
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.util.LinkedMultiValueMap;
import org.springframework.util.MultiValueMap;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RestController;
//----------------------------------------------------------------------------------------------------------------------
@RestController
public class CRequestBodyController
{
//----------------------------------------------------------------------------------------------------------------------
	// !!!!! ACTION METHOD cita data z HTTP REQUEST BODY. HTTP REQUEST BODY je mozne ziskat tak, ze sa do ACTION METHOD prida PARAMETER, ktory je oznaceny pomocou ANNOTATION [@RequestBody].
	@GetMapping("/RequestBodyGet")
	public ResponseEntity<CMyResponse> RequestBodyGet(@RequestBody CMyRequest Request)
	{
		CMyResponse												ResponseBody=new CMyResponse(Request.getValue1().toLowerCase(),Request.getValue1().toLowerCase());
		MultiValueMap<String,String>							ResponseHeaders=new LinkedMultiValueMap<String,String>();
		HttpStatus												ResponseStatus=HttpStatus.OK;
		ResponseEntity<CMyResponse>								Response=new ResponseEntity<CMyResponse>(ResponseBody,ResponseHeaders,ResponseStatus);
		
		return(Response);
	}	
//----------------------------------------------------------------------------------------------------------------------
	// !!!!! ACTION METHOD cita data z HTTP REQUEST BODY. HTTP REQUEST BODY je mozne ziskat tak, ze sa do ACTION METHOD prida PARAMETER, ktory je oznaceny pomocou ANNOTATION [@RequestBody].
	@PostMapping("/RequestBodyPost")
	public ResponseEntity<CMyResponse> RequestBodyPost(@RequestBody CMyRequest Request)
	{
		CMyResponse												ResponseBody=new CMyResponse(Request.getValue1().toUpperCase(),Request.getValue1().toUpperCase());
		MultiValueMap<String,String>							ResponseHeaders=new LinkedMultiValueMap<String,String>();
		HttpStatus												ResponseStatus=HttpStatus.OK;
		ResponseEntity<CMyResponse>								Response=new ResponseEntity<CMyResponse>(ResponseBody,ResponseHeaders,ResponseStatus);
		
		return(Response);
	}	
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------