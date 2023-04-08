package Chapter10.ImplementingRESTServices.WebServices;
//----------------------------------------------------------------------------------------------------------------------
import java.util.ArrayList;
import java.util.List;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.util.LinkedMultiValueMap;
import org.springframework.util.MultiValueMap;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RestController;
//----------------------------------------------------------------------------------------------------------------------
@RestController
public class CWebServiceCustomHTTPResponseController 
{
//----------------------------------------------------------------------------------------------------------------------
	// !!! ACTION METHOD vracia CLASS [ResponseEntity<T>], ktora umoznuje nastavit HTTP RESPONSE STATUS, HTTP RESPONSE HEADERS aj HTTP RESPONSE BODY.
	@GetMapping("/CustomResponse")
	public ResponseEntity<List<CPerson>> CustomResponse()
	{
		List<CPerson>											ResponseBody=new ArrayList<CPerson>();
		
		ResponseBody.add(new CPerson("Timmy","Anderson",12));
		ResponseBody.add(new CPerson("Jenny","Thompson",13));

		MultiValueMap<String,String>							ResponseHeaders=new LinkedMultiValueMap<String,String>();

		ResponseHeaders.add("MY HEADER 1","MY VALUE 1");
		ResponseHeaders.add("MY HEADER 2","MY VALUE 2");
		ResponseHeaders.add("MY HEADER 3","MY VALUE 3");

		HttpStatus												ResponseStatus=HttpStatus.ACCEPTED;

		ResponseEntity<List<CPerson>>							Response=new ResponseEntity<List<CPerson>>(ResponseBody,ResponseHeaders,ResponseStatus);
		
		return(Response);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------