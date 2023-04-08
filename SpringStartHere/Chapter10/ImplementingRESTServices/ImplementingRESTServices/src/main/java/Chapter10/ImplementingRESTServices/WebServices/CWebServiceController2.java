package Chapter10.ImplementingRESTServices.WebServices;
//----------------------------------------------------------------------------------------------------------------------
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RestController;
//----------------------------------------------------------------------------------------------------------------------
// !!! CLASS sa oznaci ako REST CONTROLLER pomocou ANNOTATION [@RestController].
@RestController
public class CWebServiceController2
{
//----------------------------------------------------------------------------------------------------------------------
	// !!! Definuje sa URL na ktorej WEB SERVICE prijima HTTP REQUESTS.
	@GetMapping("/Test3")
	// !!! ACTION METHOD NIE JE potrebne oznacovat pomocou ANNOTATION [@ResponseBody], pretoze aplikovanim ANNOTATION [@RestController] na CLASS su vsetky ACTION METHODS povazovane za WEB SERVICES.
	// !!! ACTION METHOD vracia STRING CONTENT, a NIE NAZOV VIEW, ako pri CONTROLLERS, ktore vracaju VIEWS na RENDERING.
	public String TestMethod()
	{
		return("Hello TEST 3 !");
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------