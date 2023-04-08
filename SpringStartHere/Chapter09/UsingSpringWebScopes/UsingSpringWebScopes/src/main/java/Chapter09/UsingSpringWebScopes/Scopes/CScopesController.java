package Chapter09.UsingSpringWebScopes.Scopes;
//----------------------------------------------------------------------------------------------------------------------
import Chapter09.UsingSpringWebScopes.Helpers.CHelpers;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpSession;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PostMapping;
//----------------------------------------------------------------------------------------------------------------------
@Controller
// !!!!! CONTROLLER je BEAN OBJECT, ktory ma SINGLETON SCOPE, pretoze SINGLETON SCOPE je DEFAULT SCOPE.
public class CScopesController
{
//----------------------------------------------------------------------------------------------------------------------
	// !!!!! FIELD obsahuje REFERENCE na PROXY OBJECT ktory je WRAPPED okolo SPRING BEAN OBJECT.
	// !!!!! Kedze SPRING BEAN OBJECT na REQUEST SCOPE, tak SPRING BEAN OBJECT, ktory zapuzdruje je vytvarany az po prichode HTTP REQUEST. Pred prichodom HTTP REQUEST PROXY OBJECT NEOBSAHUJE SPRING BEAN OBJECT.
	// !!!!! Samotny PROXY OBJECT je SINGLETON, pretoze je vytvoreny v CONSTRUCTOR CONTROLLER OBJECT, ktory ma SINGLETON SCOPE.
	// !!!!! Kedze samotny PROXY OBJECT je SINGLETON, moze mat MODIFIER 'final'.
	private final CScopeRequestBean								MBeanScopeRequest;
	// !!!!! FIELD obsahuje REFERENCE na PROXY OBJECT ktory je WRAPPED okolo SPRING BEAN OBJECT.
	// !!!!! Kedze SPRING BEAN OBJECT na SESSION SCOPE, tak SPRING BEAN OBJECT, ktory zapuzdruje je vytvarany az po vytvoreni HTTP SESSION. Pred vytvorenim HTTP SESSION PROXY OBJECT NEOBSAHUJE SPRING BEAN OBJECT.
	// !!!!! Samotny PROXY OBJECT je SINGLETON, pretoze je vytvoreny v CONSTRUCTOR CONTROLLER OBJECT, ktory ma SINGLETON SCOPE.
	// !!!!! Kedze samotny PROXY OBJECT je SINGLETON, moze mat MODIFIER 'final'.
	private final CScopeSessionBean								MBeanScopeSession;
	private final CScopeApplicationBean							MBeanScopeApplication;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	// !!!!! Pre TYPE 'CScopeRequestBean' SPRING vytvori SINGLETON instanciu PROXY OBJECT, ktory je WRAPPED okolo SPRING BEAN OBJECT.
	// !!!!! Pre TYPE 'CScopeRequestBean', kedze CONSTRCUTOR CONTROLLER NIE je volany v HTTP REQUEST, kedze je to SINGLETON OBJECT, tak interne PROXY OBJECT v tejto chvili este NEVYTVORI internu instanciu SPRING BEAN OBJECT.
	// !!!!! Pre TYPE 'CScopeSessionBean' SPRING vytvori SINGLETON instanciu PROXY OBJECT, ktory je WRAPPED okolo SPRING BEAN OBJECT.
	// !!!!! Pre TYPE 'CScopeSessionBean', kedze CONSTRCUTOR CONTROLLER NIE je volany v HTTP SESSION, kedze je to SINGLETON OBJECT, tak interne PROXY OBJECT v tejto chvili este NEVYTVORI internu instanciu SPRING BEAN OBJECT.
	public CScopesController(CScopeRequestBean BeanScopeRequest, CScopeSessionBean BeanScopeSession, CScopeApplicationBean BeanScopeApplication)
	{
		System.out.format("TIME [%s] - CONSTRUCTOR CScopesController() CALLED !\n",CHelpers.GetTime());
	
		MBeanScopeRequest=BeanScopeRequest;
		MBeanScopeSession=BeanScopeSession;
		MBeanScopeApplication=BeanScopeApplication;
		
		// !!!!! PROXY OBJECT robi INJECTION vsetky METHODS SPRING BEAN OBJECT, pricom pred volanim kazdej skontroluje ci pre dany HTTP REQUEST asociovany s CURRENT THREAD existuje interna instancia SPRING BEAN OBJECT. Ak nie, tak ju vytvori.
		// !!!!! Kedze volanie CONTROLLER CONSTRUCTOR bezi v THREADE, ktory NEMA asociovany HTTP REQUEST, tak hodi EXCEPTION, pretoze neexistuje HTTP REQUEST pre ktory by bolo mozne asociovat s internou instanciou SPRING BEAN OBJECT.
		//MBeanScopeRequest.DoSomething1();
		
		// !!!!! PROXY OBJECT robi INJECTION vsetky METHODS SPRING BEAN OBJECT, pricom pred volanim kazdej skontroluje ci pre danu HTTP SESSION asociovanu s CURRENT THREAD existuje interna instancia SPRING BEAN OBJECT. Ak nie, tak ju vytvori.
		// !!!!! Kedze volanie CONTROLLER CONSTRUCTOR bezi v THREADE, ktory NEMA asociovanu HTTP SESSION, tak hodi EXCEPTION, pretoze neexistuje HTTP SESSION pre ktoru by bolo mozne asociovat s internou instanciou SPRING BEAN OBJECT.
		//MBeanScopeSession.DoSomething1();
		
		// !!! Kedze SPRING BEAN OBJECT ma APPLICATION CONTEXT, tak je mozne volat METHODS tohto SPRING BEAN OBJECT v LUBOVOLNOM THREAD.
		//MBeanScopeApplication.DoSomething1();
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	private void AddResults(Model Page)
	{
		CHelpers.PrintLineSeparator();
		
		String													NewString=CHelpers.GetTime();
		
		Page.addAttribute("Date",String.format("TIME [%s] !",NewString));
		
		System.out.format("TIME [%s] - BEFORE CALLING CScopeRequestBean.DoSomething1() !\n",CHelpers.GetTime());

		// !!!!! PROXY OBJECT robi INJECTION vsetkych METHODS SPRING BEAN OBJECT, pricom pred volanim kazdej skontroluje ci pre dany HTTP REQUEST asociovany s CURRENT THREAD existuje interna instancia SPRING BEAN OBJECT. Ak nie, tak ju vytvori.
		MBeanScopeRequest.DoSomething1();
		
		System.out.format("TIME [%s] - AFTER CALLING CScopeRequestBean.DoSomething1() !\n",CHelpers.GetTime());
		
		// !!!!! Pri volani METHOD [void MBeanScopeRequest.DoSomething2()] uz PROXY OBJECT NEVYTVORI novu instanciu SPRING BEAN OBJECT, kedze pre HTTP REQUEST asociovany s CURRENT THREAD uz instancia SPRING BEAN OBJECT bola vytvorena.
		MBeanScopeRequest.DoSomething2();
		
		System.out.format("TIME [%s] - AFTER CALLING CScopeRequestBean.DoSomething2() !\n",CHelpers.GetTime());
		
		// !!!!! Pri volani METHOD [String MBeanScopeRequest.toString()] uz PROXY OBJECT NEVYTVORI novu instanciu SPRING BEAN OBJECT, kedze pre HTTP REQUEST asociovany s CURRENT THREAD uz instancia SPRING BEAN OBJECT bola vytvorena.
		String													BeanScopeRequestName=MBeanScopeRequest.toString();

		Page.addAttribute("RequestScope",String.format("REQUEST SCOPE BEAN [%s] !",BeanScopeRequestName));

		CHelpers.PrintLineSeparator();

		System.out.format("TIME [%s] - BEFORE CALLING CScopeSessionBean.DoSomething1() !\n",CHelpers.GetTime());

		// !!!!! PROXY OBJECT robi INJECTION vsetkych METHODS SPRING BEAN OBJECT, pricom pred volanim kazdej skontroluje ci pre danu HTTP SESSION asociovanu s CURRENT THREAD existuje interna instancia SPRING BEAN OBJECT. Ak nie, tak ju vytvori.
		MBeanScopeSession.DoSomething1();
		
		System.out.format("TIME [%s] - AFTER CALLING CScopeSessionBean.DoSomething1() !\n",CHelpers.GetTime());
		
		// !!!!! Pri volani METHOD [void MBeanScopeSession.DoSomething2()] uz PROXY OBJECT NEVYTVORI novu instanciu SPRING BEAN OBJECT, kedze pre HTTP SESSION asociovanu s CURRENT THREAD uz instancia SPRING BEAN OBJECT bola vytvorena.
		MBeanScopeSession.DoSomething2();
		
		System.out.format("TIME [%s] - AFTER CALLING CScopeSessionBean.DoSomething2() !\n",CHelpers.GetTime());

		// !!!!! Pri volani METHOD [String MBeanScopeSession.toString()] uz PROXY OBJECT NEVYTVORI novu instanciu SPRING BEAN OBJECT, kedze pre HTTP SESSION asociovanu s CURRENT THREAD uz instancia SPRING BEAN OBJECT bola vytvorena.
		String													BeanScopeSessionName=MBeanScopeSession.toString();

		Page.addAttribute("SessionScope",String.format("SESSION SCOPE BEAN [%s] !",BeanScopeSessionName));

		CHelpers.PrintLineSeparator();

		System.out.format("TIME [%s] - BEFORE CALLING CScopeApplicationBean.DoSomething1() !\n",CHelpers.GetTime());

		// !!! Kedze SPRING BEAN OBJECT ma APPLICATION CONTEXT, tak je mozne volat METHODS tohto SPRING BEAN OBJECT v LUBOVOLNOM THREAD.
		MBeanScopeApplication.DoSomething1();
		
		System.out.format("TIME [%s] - AFTER CALLING CScopeApplicationBean.DoSomething1() !\n",CHelpers.GetTime());
		
		// !!! Kedze SPRING BEAN OBJECT ma APPLICATION CONTEXT, tak je mozne volat METHODS tohto SPRING BEAN OBJECT v LUBOVOLNOM THREAD.
		MBeanScopeApplication.DoSomething2();
		
		System.out.format("TIME [%s] - AFTER CALLING CScopeApplicationBean.DoSomething2() !\n",CHelpers.GetTime());

		// !!! Kedze SPRING BEAN OBJECT ma APPLICATION CONTEXT, tak je mozne volat METHODS tohto SPRING BEAN OBJECT v LUBOVOLNOM THREAD.
		String													BeanScopeApplicationName=MBeanScopeApplication.toString();

		Page.addAttribute("ApplicationScope",String.format("APPLICATION SCOPE BEAN [%s] !",BeanScopeApplicationName));
		
		CHelpers.PrintLineSeparator();
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	@GetMapping("/Scopes")
	public String ScopesGet(Model Page)
	{
		AddResults(Page);
	
		String													HtmlFileName="Scopes.html";
		
		return(HtmlFileName);
	}
//----------------------------------------------------------------------------------------------------------------------
	@PostMapping("/Refresh")
	public String ScopesRefreshPost(Model Page)
	{
		AddResults(Page);
	
		String													HtmlFileName="Scopes.html";
		
		return(HtmlFileName);
	}
//----------------------------------------------------------------------------------------------------------------------
	@PostMapping("/TerminateSession")
	public String ScopesTerminateSessionPost(Model Page, HttpServletRequest Request)
	{
		// !!!!! Ak EXISTUJE, METHOD vrati HTTP SESSION. Inak vrati NULL.
		HttpSession												CurrentSession=Request.getSession(false);

		if (CurrentSession!=null)
		{
			System.out.format("TIME [%s] - BEFORE SESSION is TERMINATED !\n",CHelpers.GetTime());
		
			// !!!!! Uzatvori sa CURRENT HTTP SESSION. Zaroven sa odstrania aj vsetky SPRING BEAN OBJECTS so SESSION SCOPE.
			CurrentSession.invalidate();
			
			System.out.format("TIME [%s] - AFTER SESSION is TERMINATED !\n",CHelpers.GetTime());
		}
	
		AddResults(Page);
	
		String													HtmlFileName="Scopes.html";
		
		return(HtmlFileName);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------