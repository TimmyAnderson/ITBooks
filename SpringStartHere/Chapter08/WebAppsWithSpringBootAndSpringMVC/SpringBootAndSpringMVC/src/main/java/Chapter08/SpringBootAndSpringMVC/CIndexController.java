package Chapter08.SpringBootAndSpringMVC;
//----------------------------------------------------------------------------------------------------------------------
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.RequestMapping;
//----------------------------------------------------------------------------------------------------------------------
// !!! ANNOTATION [@Controller] oznacuje CLASS za CONTROLLER, a zaroven aj ako BEAN OBJECT.   
@Controller
public class CIndexController
{
//----------------------------------------------------------------------------------------------------------------------
	// !!! ANNOTATION [@RequestMapping] definuje URL PATH pre ktory bude spusteny CONTROLLER.  
	@RequestMapping("/Index")
	// !!! Ako PARAMETER sa MUSI pouzit CLASS [Model].
	public String ActionMethodIndex(Model Page)
	{
		// !!! Vracia sa nazov HTML FILE, ktory sa ma vratit v HTTP RESPONSE.
		String													HtmlFileName="Index.html";
		
		return(HtmlFileName);
	}	
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------