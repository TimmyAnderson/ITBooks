package Chapter08.SpringBootAndSpringMVC;
//----------------------------------------------------------------------------------------------------------------------
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestParam;
//----------------------------------------------------------------------------------------------------------------------
// !!! ANNOTATION [@Controller] oznacuje CLASS za CONTROLLER, a zaroven aj ako BEAN OBJECT.   
@Controller
public class CHomeController
{
//----------------------------------------------------------------------------------------------------------------------
	// !!! ANNOTATION [@RequestMapping] definuje URL PATH pre ktory bude spusteny CONTROLLER.  
	@RequestMapping("/Home")
	// !!! Ako PARAMETER sa MUSI pouzit CLASS [Model].
	public String ActionMethodHome(Model Page)
	{
		// !!! Pomocou METHOD [Model Model.addAttribute(String AttributeName, @Nullable Object AttributeValue)] sa pridavaju DYNAMIC DATA, ktore maju byt vlozene do HTML PAGE.
		Page.addAttribute("Color","green");
		Page.addAttribute("UserName","Timmy Anderson");
	
		// !!! Vracia sa nazov HTML FILE, ktory sa ma vratit v HTTP RESPONSE.
		String													HtmlFileName="Home.html";
		
		return(HtmlFileName);
	}	
//----------------------------------------------------------------------------------------------------------------------
	@RequestMapping("/QueryStringParameters")
	// !!!!! Ak sa PARAMETERS maju byt MAPPED na QUERY STRING, tak je treba na nich aplikovat ANNOTATION [@RequestParam].
	// !!!!! BY-DEFAULT su PARAMETERS MANDATORY a ak nie su zadane, HTTP SERVER vrati HTTP STATUS CODE 400.
	// !!!!! Ak PARAMETERS maju byt OPTIONAL, je nutne nastavit v ANNOTATION [@RequestParam] PROPERTY 'required' na VALUE 'false'. 
	public String ActionMethodQueryStringParameters(@RequestParam String Name, @RequestParam(required=false) String Color, Model Page)
	{
		String													RealColor=(Color!=null) ? Color.toLowerCase() : "";	
	
		if (RealColor.equals("red")==false && RealColor.equals("green")==false && RealColor.equals("blue")==false)
		{
			RealColor="black";
		}

		Page.addAttribute("Color",RealColor);
		Page.addAttribute("UserName",Name);

		String													HtmlFileName="Home.html";
	
		return(HtmlFileName);
	}
//----------------------------------------------------------------------------------------------------------------------
	// !!!!!! PATH VARIABLES musia byt definovane v PATH pomocou SYNTAX [PATH/{PATH_VARIABLE_1}/{PATH_VARIABLE_2}/.../{PATH_VARIABLE_N}].
	@RequestMapping("/PathVariables1/{Name}/{Color}")
	// !!!!! Ak sa PARAMETERS maju byt MAPPED na PATH VARIABLES, tak je treba na nich aplikovat ANNOTATION [@PathVariable].
	// !!!!! Nazvy ACTION METHOD PARAMETERS sa MUSI zhodovat s nazvami PATH VARIABLES. 
	public String ActionMethodPathVariables1(@PathVariable String Name, @PathVariable String Color, Model Page)
	{
		String													RealColor=(Color!=null) ? Color.toLowerCase() : "";	
	
		if (RealColor.equals("red")==false && RealColor.equals("green")==false && RealColor.equals("blue")==false)
		{
			RealColor="black";
		}

		Page.addAttribute("Color",RealColor);
		Page.addAttribute("UserName",Name);

		String													HtmlFileName="Home.html";
	
		return(HtmlFileName);
	}
//----------------------------------------------------------------------------------------------------------------------
	// !!!!!! PATH VARIABLES musia byt definovane v PATH pomocou SYNTAX [PATH/{PATH_VARIABLE_1}/{PATH_VARIABLE_2}/.../{PATH_VARIABLE_N}].
	// !!!!!! Ak maju byt PATH VARIABLES OPTIONAL, je nutne nastavit PROPERTY 'value' ANNOTATION [@RequestMapping] na vsetky mozne kombinacie PATHS.
	@RequestMapping(value={"/PathVariables2/{Name}","/PathVariables2/{Name}/{Color}"})
	// !!!!! Ak sa PARAMETERS maju byt MAPPED na PATH VARIABLES, tak je treba na nich aplikovat ANNOTATION [@PathVariable].
	// !!!!! Nazvy ACTION METHOD PARAMETERS sa MUSI zhodovat s nazvami PATH VARIABLES. 
	// !!!!! BY-DEFAULT su PATH VARIABLES MANDATORY a ak nie su zadane, HTTP SERVER vrati HTTP STATUS CODE 404.
	// !!!!! Ak PATH VARIABLES maju byt OPTIONAL, je nutne nastavit v ANNOTATION [@PathVariable] PROPERTY 'required' na VALUE 'false'. 
	public String ActionMethodPathVariables2(@PathVariable String Name, @PathVariable(required=false) String Color, Model Page)
	{
		String													RealColor=(Color!=null) ? Color.toLowerCase() : "";	
	
		if (RealColor.equals("red")==false && RealColor.equals("green")==false && RealColor.equals("blue")==false)
		{
			RealColor="black";
		}

		Page.addAttribute("Color",RealColor);
		Page.addAttribute("UserName",Name);

		String													HtmlFileName="Home.html";
	
		return(HtmlFileName);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------