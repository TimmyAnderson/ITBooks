package Chapter08.SpringBootAndSpringMVC;
//----------------------------------------------------------------------------------------------------------------------
import java.util.List;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.RequestParam;
//----------------------------------------------------------------------------------------------------------------------
@Controller
public class CUsingHttpVerbsController
{
//----------------------------------------------------------------------------------------------------------------------
	private final CPersonsService									MNamesService;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	// !!! PARAMETERS sa naplnia pomocou DEPENDENCY INJECTION.
	public CUsingHttpVerbsController(CPersonsService NamesService)
	{
		MNamesService=NamesService; 	
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	// !!! ACTION METHOD sa vola pre METHOD GET.
	//@RequestMapping(path={"/UsingHttpVerbs"},method={RequestMethod.GET})
	// !!! Alternativne sa moze pouzit aj ANNOTATION [@PostMapping]
	@GetMapping(path={"/UsingHttpVerbs"})
	public String ActionMethodUsingHttpVerbsGet(Model Page)
	{
		List<CPerson>											Persons=MNamesService.GetPersons();	

		Page.addAttribute("Persons",Persons);
	
		String													HtmlFileName="UsingHttpVerbs.html";
		
		return(HtmlFileName);
	}	
//----------------------------------------------------------------------------------------------------------------------
	// !!! ACTION METHOD sa vola pre METHOD POST.
	//@RequestMapping(path={"/UsingHttpVerbs1"},method={RequestMethod.POST})
	// !!! Alternativne sa moze pouzit aj ANNOTATION [@PostMapping]
	@PostMapping(path={"/UsingHttpVerbs1"})
	// !!!!! SPRING dokaze konvertovat PARAMETERS z HTTP REQUEST na spravny JAVA TYPE.
	public String ActionMethodUsingHttpVerbsPost1(@RequestParam String FirstName, @RequestParam String LastName, @RequestParam int Age, Model Page)
	{
		MNamesService.AddName(new CPerson(FirstName,LastName,Age));
	
		List<CPerson>											Persons=MNamesService.GetPersons();	

		Page.addAttribute("Persons",Persons);
	
		String													HtmlFileName="UsingHttpVerbs.html";
		
		return(HtmlFileName);
	}	
//----------------------------------------------------------------------------------------------------------------------
	// !!! ACTION METHOD sa vola pre METHOD POST.
	@RequestMapping(path={"/UsingHttpVerbs2"},method={RequestMethod.POST})
	// !!!!! SPRING dokaze konvertovat PARAMETERS z HTTP REQUEST na spravny JAVA TYPE.
	// !!!!! Ak je PARAMETER TYPE CUSTOM TYPE, tak sa NESMIE pouzit ANNOTATION [@RequestParam].
	public String ActionMethodUsingHttpVerbsPost2(CPerson Person, Model Page)
	{
		MNamesService.AddName(Person);
	
		List<CPerson>											Persons=MNamesService.GetPersons();	

		Page.addAttribute("Persons",Persons);
	
		String													HtmlFileName="UsingHttpVerbs.html";
		
		return(HtmlFileName);
	}	
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------