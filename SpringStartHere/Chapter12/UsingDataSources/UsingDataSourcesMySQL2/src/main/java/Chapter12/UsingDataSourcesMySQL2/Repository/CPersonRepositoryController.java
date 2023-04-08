package Chapter12.UsingDataSourcesMySQL2.Repository;
//----------------------------------------------------------------------------------------------------------------------
import java.util.List;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RestController;
//----------------------------------------------------------------------------------------------------------------------
@RestController
public class CPersonRepositoryController
{
//----------------------------------------------------------------------------------------------------------------------
	private final CPersonRepository								MRepository;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	public CPersonRepositoryController(CPersonRepository Repository)
	{
		MRepository=Repository;
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	// CURL [curl -v -X GET localhost:8080/GetAllPersons].
	@GetMapping("/GetAllPersons")
	public List<CPerson> GetAllPersons()
	{
		List<CPerson>											Persons=MRepository.GetAllPersons();

		return(Persons);
	}		
//----------------------------------------------------------------------------------------------------------------------
	// CURL [curl -v -X POST localhost:8080/AddPerson -H "Content-Type: application/json" -d "{\"firstName\":\"Timmy\",\"lastName\":\"Anderson\",\"age\":12}"].
	// CURL [curl -v -X POST localhost:8080/AddPerson -H "Content-Type: application/json" -d "{\"firstName\":\"Jenny\",\"lastName\":\"Thompson\",\"age\":13}"].
	@PostMapping("/AddPerson")
	public void AddPerson(@RequestBody CPerson Person)
	{
		MRepository.AddPerson(Person);
	}	
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------