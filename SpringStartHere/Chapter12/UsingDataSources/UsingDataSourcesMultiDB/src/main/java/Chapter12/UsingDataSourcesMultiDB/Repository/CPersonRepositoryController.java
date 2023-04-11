package Chapter12.UsingDataSourcesMultiDB.Repository;
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
	private final CPersonRepository1								MRepository1;
	private final CPersonRepository2								MRepository2;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	public CPersonRepositoryController(CPersonRepository1 Repository1, CPersonRepository2 Repository2)
	{
		MRepository1=Repository1;
		MRepository2=Repository2;
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	// CURL [curl -v -X GET localhost:8080/GetAllPersons1].
	@GetMapping("/GetAllPersons1")
	public List<CPerson> GetAllPersons1()
	{
		List<CPerson>											Persons=MRepository1.GetAllPersons();

		return(Persons);
	}		
//----------------------------------------------------------------------------------------------------------------------
	// CURL [curl -v -X GET localhost:8080/GetAllPersons2].
	@GetMapping("/GetAllPersons2")
	public List<CPerson> GetAllPersons2()
	{
		List<CPerson>											Persons=MRepository2.GetAllPersons();

		return(Persons);
	}		
//----------------------------------------------------------------------------------------------------------------------
	// CURL [curl -v -X POST localhost:8080/AddPerson1 -H "Content-Type: application/json" -d "{\"firstName\":\"Timmy\",\"lastName\":\"Anderson\",\"age\":12}"].
	// CURL [curl -v -X POST localhost:8080/AddPerson1 -H "Content-Type: application/json" -d "{\"firstName\":\"Jenny\",\"lastName\":\"Thompson\",\"age\":13}"].
	@PostMapping("/AddPerson1")
	public void AddPerson1(@RequestBody CPerson Person)
	{
		MRepository1.AddPerson(Person);
	}	
//----------------------------------------------------------------------------------------------------------------------
	// CURL [curl -v -X POST localhost:8080/AddPerson2 -H "Content-Type: application/json" -d "{\"firstName\":\"Timmy\",\"lastName\":\"Anderson\",\"age\":12}"].
	// CURL [curl -v -X POST localhost:8080/AddPerson2 -H "Content-Type: application/json" -d "{\"firstName\":\"Jenny\",\"lastName\":\"Thompson\",\"age\":13}"].
	@PostMapping("/AddPerson2")
	public void AddPerson2(@RequestBody CPerson Person)
	{
		MRepository2.AddPerson(Person);
	}	
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------