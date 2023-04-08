package Chapter10.ImplementingRESTServices.ExceptionHandling;
//----------------------------------------------------------------------------------------------------------------------
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.util.LinkedMultiValueMap;
import org.springframework.util.MultiValueMap;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;
//----------------------------------------------------------------------------------------------------------------------
@RestController
public class CExceptionHandlingController
{
//----------------------------------------------------------------------------------------------------------------------
	private final CExceptionService								MExceptionService;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	@Autowired
	public CExceptionHandlingController(CExceptionService ExceptionService)
	{
		MExceptionService=ExceptionService;
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	@GetMapping("/ExceptionTest1")
	// !!!!! ACTION METHOD vracia CLASS [ResponseEntity<?>] BEZ SPECIFIKACIE konkretneho TYPE, pretoze ak OPERATION zbehne uspesne vracia CLASS [ResponseEntity<CResponseOK>] a ak OPERATION hodi EXCEPTION, vracia CLASS [ResponseEntity<CResponseError>].
	public ResponseEntity<?> ExceptionTest1(@RequestParam boolean ThrowException)
	{
		try
		{
			// !!! METHOD moze hodit EXCEPTION.
			MExceptionService.DoSomething(ThrowException);
			
			// !!! Vrati sa OK HTTP RESPONSE TYPE [ResponseEntity<CResponseOK>].
			CResponseOK											ResponseBody=new CResponseOK("Timmy","Anderson");
			MultiValueMap<String,String>						ResponseHeaders=new LinkedMultiValueMap<String,String>();
			HttpStatus											ResponseStatus=HttpStatus.ACCEPTED;
			ResponseEntity<CResponseOK>							Response=new ResponseEntity<CResponseOK>(ResponseBody,ResponseHeaders,ResponseStatus);
			
			return(Response);
		}
		catch(CMyException E)
		{
			// !!! Vrati sa ERROR HTTP RESPONSE TYPE [ResponseEntity<CResponseError>].
			CResponseError										ResponseBody=new CResponseError(String.format("There is some ERROR with MESSAGE [%s] !",E.getMessage()));
			MultiValueMap<String,String>						ResponseHeaders=new LinkedMultiValueMap<String,String>();
			HttpStatus											ResponseStatus=HttpStatus.BAD_REQUEST;
			ResponseEntity<CResponseError>						Response=new ResponseEntity<CResponseError>(ResponseBody,ResponseHeaders,ResponseStatus);
			
			return(Response);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	@GetMapping("/ExceptionTest2")
	// !!!!! ACTION METHOD NEZACHYTAVA EXCEPTIONS, pretoze tie su zachytene a spracovane v EXCEPTION ADVICE.
	// !!!!! ACTION METHOD VZDY vracia TYPE [ResponseEntity<CResponseOK>]. Ak dojde k EXCEPTION, tak EXCEPTION ADVICE vracia TYPE [ResponseEntity<CResponseError>].
	public ResponseEntity<CResponseOK> ExceptionTest2(@RequestParam boolean ThrowException)
	{
		// !!! METHOD moze hodit EXCEPTION.
		MExceptionService.DoSomething(ThrowException);
		
		// !!! Vrati sa OK HTTP RESPONSE TYPE [ResponseEntity<CResponseOK>].
		CResponseOK												ResponseBody=new CResponseOK("Jenny","Thompson");
		MultiValueMap<String,String>							ResponseHeaders=new LinkedMultiValueMap<String,String>();
		HttpStatus												ResponseStatus=HttpStatus.ACCEPTED;
		ResponseEntity<CResponseOK>								Response=new ResponseEntity<CResponseOK>(ResponseBody,ResponseHeaders,ResponseStatus);
		
		return(Response);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------