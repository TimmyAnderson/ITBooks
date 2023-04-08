package Chapter10.ImplementingRESTServices.ExceptionHandling;
//----------------------------------------------------------------------------------------------------------------------
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.util.LinkedMultiValueMap;
import org.springframework.util.MultiValueMap;
import org.springframework.web.bind.annotation.ExceptionHandler;
import org.springframework.web.bind.annotation.RestControllerAdvice;
//----------------------------------------------------------------------------------------------------------------------
// !!!!! CLASS obsahuje REST CONTROLLER ADVICES a preto MUSI byt oznacena pomocou ANNOTATION [@RestControllerAdvice].
@RestControllerAdvice
public class CExceptionAdvices
{
//----------------------------------------------------------------------------------------------------------------------
	// !!!!! EXCEPTION ADVICE MUSI byt oznacena pomocou ANNOTATION [@ExceptionHandler], ktora definuje EXCEPTION TYPE na ktory ma dany EXCEPTION ADVICE reagovat.
	@ExceptionHandler(CMyException.class)
	public ResponseEntity<CResponseError> ExceptionTest1(CMyException E)
	{
		// !!! Vrati sa ERROR HTTP RESPONSE TYPE [ResponseEntity<CResponseError>].
		CResponseError											ResponseBody=new CResponseError(String.format("There is some ERROR with MESSAGE [%s] ! PROCESSED by EXCEPTION ADVICE.",E.getMessage()));
		MultiValueMap<String,String>							ResponseHeaders=new LinkedMultiValueMap<String,String>();
		HttpStatus												ResponseStatus=HttpStatus.BAD_REQUEST;
		ResponseEntity<CResponseError>							Response=new ResponseEntity<CResponseError>(ResponseBody,ResponseHeaders,ResponseStatus);
			
		return(Response);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------