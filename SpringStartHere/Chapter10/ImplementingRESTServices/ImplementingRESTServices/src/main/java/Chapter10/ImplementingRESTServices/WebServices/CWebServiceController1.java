package Chapter10.ImplementingRESTServices.WebServices;
//----------------------------------------------------------------------------------------------------------------------
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.ResponseBody;
//----------------------------------------------------------------------------------------------------------------------
// !!! CLASS sa oznaci ako CONTROLLER pomocou ANNOTATION [@Controller].
@Controller
public class CWebServiceController1
{
//----------------------------------------------------------------------------------------------------------------------
	// !!! Definuje sa URL na ktorej WEB SERVICE prijima HTTP REQUESTS.
	@GetMapping("/Test1")
	// !!! ACTION METHOD sa pomocou ANNOTATION [@ResponseBody] oznaci za WEB SERVICE, ktory vracia CONTENT a NIE NAZOV VIEW.
	@ResponseBody
	// !!! ACTION METHOD vracia STRING CONTENT, a NIE NAZOV VIEW, ako pri CONTROLLERS, ktore vracaju VIEWS na RENDERING.
	public String TestMethod1()
	{
		return("Hello TEST 1 !");
	}
//----------------------------------------------------------------------------------------------------------------------
	// !!! Definuje sa URL na ktorej WEB SERVICE prijima HTTP REQUESTS.
	@GetMapping("/Test2")
	// !!! ACTION METHOD sa pomocou ANNOTATION [@ResponseBody] oznaci za WEB SERVICE, ktory vracia CONTENT a NIE NAZOV VIEW.
	@ResponseBody
	// !!! ACTION METHOD vracia STRING CONTENT, a NIE NAZOV VIEW, ako pri CONTROLLERS, ktore vracaju VIEWS na RENDERING.
	public String TestMethod2()
	{
		return("Hello TEST 2 !");
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------