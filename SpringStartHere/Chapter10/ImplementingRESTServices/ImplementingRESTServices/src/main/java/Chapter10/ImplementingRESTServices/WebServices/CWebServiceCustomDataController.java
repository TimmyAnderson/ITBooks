package Chapter10.ImplementingRESTServices.WebServices;
//----------------------------------------------------------------------------------------------------------------------
import java.util.ArrayList;
import java.util.List;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RestController;
//----------------------------------------------------------------------------------------------------------------------
@RestController
public class CWebServiceCustomDataController
{
//----------------------------------------------------------------------------------------------------------------------
	// !!! ACTION METHOD vracia CUSTOM OBJECT, ktory je BY-DEFAULT FORMATTED ako JSON.
	@GetMapping("/GetPerson")
	public CPerson GetPerson()
	{
		CPerson													Person=new CPerson("Timmy","Anderson",12);

		return(Person);
	}
//----------------------------------------------------------------------------------------------------------------------
	// !!! ACTION METHOD vracia CUSTOM OBJECT COLLECTION, ktora je BY-DEFAULT FORMATTED ako JSON.
	@GetMapping("/GetPersons")
	public List<CPerson> GetPersons()
	{
		List<CPerson>											Persons=new ArrayList<CPerson>();
		
		Persons.add(new CPerson("Timmy","Anderson",12));
		Persons.add(new CPerson("Jenny","Thompson",13));
		
		return(Persons);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------