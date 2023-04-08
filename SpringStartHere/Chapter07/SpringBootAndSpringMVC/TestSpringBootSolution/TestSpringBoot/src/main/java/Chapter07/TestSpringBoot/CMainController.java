package Chapter07.TestSpringBoot;
//----------------------------------------------------------------------------------------------------------------------
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.RequestMapping;
//----------------------------------------------------------------------------------------------------------------------
// !!! ANNOTATION [@Controller] oznacuje CLASS za CONTROLLER, a zaroven aj ako BEAN OBJECT.   
@Controller
public class CMainController
{
//----------------------------------------------------------------------------------------------------------------------
	// !!! ANNOTATION [@RequestMapping] definuje URL PATH pre ktory bude spusteny CONTROLLER.  
	@RequestMapping("/Home")
	public String ActionMethodHome()
	{
		// !!! Vracia sa nazov HTML FILE, ktory sa ma vratit v HTTP RESPONSE.
		String													HtmlFileName="Home.html";
		
		return(HtmlFileName);
	}	
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------