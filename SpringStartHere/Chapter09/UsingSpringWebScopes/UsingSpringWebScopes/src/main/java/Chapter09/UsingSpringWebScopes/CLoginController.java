package Chapter09.UsingSpringWebScopes;
//----------------------------------------------------------------------------------------------------------------------
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestParam;
//----------------------------------------------------------------------------------------------------------------------
@Controller
public class CLoginController
{
//----------------------------------------------------------------------------------------------------------------------
	private final CRequestScopeLoginProcessor					MLoginProcessor;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	// !!! PARAMETER sa naplni pomocou DEPENDENCY INJECTION.
	public CLoginController(CRequestScopeLoginProcessor LoginProcessor)
	{
		System.out.format("CLoginController OBJECT CREATED.\n");
		
		MLoginProcessor=LoginProcessor;
		
		// !!!!! Hodi EXCEPTION, pretoze CLASS 'CLoginProcessor' ma REQUEST SCOPE ale s CURRENT THREAD nie je asociovany ziaden HTTP REQUEST.
		//System.out.format("CLoginController initialized with OBJECT [%s].\n",MLoginProcessor.toString());
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	@GetMapping("/Login")
	public String ActionMethodLoginGet()
	{
		String													HtmlFileName="Login.html";
		
		return(HtmlFileName);
	}
//----------------------------------------------------------------------------------------------------------------------
	@PostMapping("/Login")
	public String ActionMethodLoginPost(@RequestParam String Username, @RequestParam String Password, Model Page)
	{
		System.out.format("ActionMethodLoginPost() - BEFORE SETTERS CALLED.\n");

		// !!!!! SPRING BEAN az pri volani PRVEJ METHOD PROXY OBJECT SPRING BEAN zisti, ze CLASS 'CLoginProcessor' ma REQUEST SCOPE a kedze je v NOVOM HTTP REQUEST, tak vytvori NOVU INSTANCIU CLASS 'CLoginProcessor' volanim jej CONSTRUCTOR.
		//MLoginProcessor.toString();
	
		// !!! Nastavia sa PROPERTIES na SPRING BEAN OBJECT s REQUEST SCOPE.
		
		// !!!!! SPRING BEAN az pri volani PRVEJ METHOD PROXY OBJECT SPRING BEAN zisti, ze CLASS 'CLoginProcessor' ma REQUEST SCOPE a kedze je v NOVOM HTTP REQUEST, tak vytvori NOVU INSTANCIU CLASS 'CLoginProcessor' volanim jej CONSTRUCTOR.
		MLoginProcessor.setUsername(Username);
		
		System.out.format("ActionMethodLoginPost() - AFTER 1. SETTER CALLED.\n");
		
		MLoginProcessor.setPassword(Password);

		System.out.format("ActionMethodLoginPost() - AFTER 2. SETTER CALLED.\n");
	
		boolean													IsLogged=MLoginProcessor.Login();

		String													ProcessorName=MLoginProcessor.toString();

		if (IsLogged==true)
		{
			Page.addAttribute("Result",String.format("PROCESSOR [%s] - User is LOGGED IN !",ProcessorName));
			
			String												HtmlFileName="redirect:LoggedIn";
			
			return(HtmlFileName);
		}
		else
		{
			Page.addAttribute("Result",String.format("PROCESSOR [%s] - LOGIN FAILED !",ProcessorName));
			
			String												HtmlFileName="Login.html";
			
			return(HtmlFileName);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------