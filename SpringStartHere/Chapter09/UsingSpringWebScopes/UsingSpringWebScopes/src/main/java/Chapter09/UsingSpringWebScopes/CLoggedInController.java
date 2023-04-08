package Chapter09.UsingSpringWebScopes;
//----------------------------------------------------------------------------------------------------------------------
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpSession;
//----------------------------------------------------------------------------------------------------------------------
@Controller
public class CLoggedInController
{
//----------------------------------------------------------------------------------------------------------------------
	// !!!!! PROXY OBJECT je vytvoreny ako SINGLETON, no instancia SPRING BEAN OBJECT ma SESSION SCOPE.
	// !!!!! Kedze PROXY OBJECT si interne spravuje vytvaranie instancie SPRING BEAN OBJECT, tak samotny PROXY OBJECT moze byt SINGLETON a tym padom mat MODIFIER 'final' a byt inicializovany v CONSTRUCTOR CONTROLLER, ktory ma tiez SINGLETON SCOPE.
	private final CSessionScopeLoggedUserManagementService		MLoggedUserManagementService;
	private final CApplicationScopeLoginCountService			MLoginCountService;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	public CLoggedInController(CSessionScopeLoggedUserManagementService LoggedUserManagementService, CApplicationScopeLoginCountService LoginCountService)
	{
		System.out.format("CLoggedInController OBJECT CREATED.\n");
		
		MLoggedUserManagementService=LoggedUserManagementService;
		MLoginCountService=LoginCountService;
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	@GetMapping("/LoggedIn")
	public String ActionMethodGet(@RequestParam(required=false) String DoLogout, Model Page, HttpServletRequest Request)
	{
		if (DoLogout!=null)
		{
			// !!!!! LOG OUT sa robi nastavenim USER NAME v SERVICE, ktory ma SESSION SCOPE na NULL.
			// !!!!! Samotna HTTP SESSION vsak NIE JE uzatvorena.
			MLoggedUserManagementService.setUsername(null);
		}
	
		// !!!!! Zo SERVICE, ktory ma SESSION SCOPE sa nacita nazov CURRENT USER.
		String													Username=MLoggedUserManagementService.getUsername();

		if (Username!=null)
		{
			String												TextLoggedUserManagementService=MLoggedUserManagementService.toString();
			int													Counter=MLoginCountService.getCounter();
			
			Page.addAttribute("Username",Username);
			Page.addAttribute("LoginCount",Counter);
			Page.addAttribute("Object",String.format("SESSION SCOPE OBJECT [%s].",TextLoggedUserManagementService));
		
			// !!! Ak USER je LOGGED IN, tak sa zobrazi WEB PAGE.
			String												HtmlFileName="LoggedIn.html";
		
			return(HtmlFileName);
		}
		else
		{
			HttpSession											Session=Request.getSession(false);
			
			if (Session!=null)
			{
				// !!! Uzatvori sa HTTP SESSION.
				Session.invalidate();
			}
		
			// !!! Ak USER NIE je LOGGED IN, tak sa spravi REDIRECT na LOGIN PAGE.
			String												HtmlFileName="redirect:Index";
		
			return(HtmlFileName);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	
	
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------