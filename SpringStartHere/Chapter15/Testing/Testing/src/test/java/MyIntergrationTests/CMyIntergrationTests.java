package MyIntergrationTests;
//----------------------------------------------------------------------------------------------------------------------
import static org.mockito.Mockito.verify;
import static org.mockito.Mockito.when;
//----------------------------------------------------------------------------------------------------------------------
import java.util.Optional;
import org.junit.jupiter.api.DisplayName;
import org.junit.jupiter.api.Test;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.boot.test.mock.mockito.MockBean;
import Chapter15.Testing.TestingApplication;
import Chapter15.Testing.Repository.Account;
import Chapter15.Testing.Repository.CAccountService;
import Chapter15.Testing.Repository.IAccountRepository;
//----------------------------------------------------------------------------------------------------------------------
// !!!!! Na CLASS so SPRING INTEGRATION TESTS MUSI byt aplikovana ANNOTATION [@SpringBootTest], aby SPRING BOOT vedel, ze CLASS obsahuje SPRING INTEGRATION TESTS.
// !!!!! Na to, aby sa TESTS spustili, je NUTNE nastavit PROPERTY [classes] na APPLICATION CLASS. APPLICATION CLASS je CLASS, kde sa nachadza JAVA MAIN METHOD.
@SpringBootTest(classes={TestingApplication.class})
public class CMyIntergrationTests
{
//----------------------------------------------------------------------------------------------------------------------
	// !!!!! Na FIELDS, ktore obsahuju SPRING BOOT OBJECTS, ktore maju byt vytvorene ako MOCK OBJECTS je treba aplikovat ANNOTATION [@MockBean]. Tieto SPRING BEAN OBJECTS su vytvorene zo SPRING APPLICATION CONTEXT.
	@MockBean
	private IAccountRepository									MAccountRepository;
//----------------------------------------------------------------------------------------------------------------------
	// !!!!! Na FIELDS, ktore obsahuju SPRING BOOT OBJECTS a su DEPENDENT na inych SPRING BOOT OBJECTS je treba aplikovat ANNOTATION [@Autowired].
	@Autowired
	private CAccountService										MAccountService;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	@Test
	@DisplayName("This is MY INTEGRATION TEST.")
	public void MyIntegrationTest()
	{
		// !!!!! Pripravia sa DATA pre MOCK OBJECT.
		Account													Sender=new Account();
		
		Sender.setId(1);
		Sender.setAmount(1000);
		
		Account													Destination=new Account();
		
		Destination.setId(2);
		Destination.setAmount(1000);
	
		// !!!!! Pomocou METHOD [<T> OngoingStubbing<T> Mockito.when(T MethodCall)] a METHOD [OngoingStubbing<T> OngoingStubbing<T>.thenReturn(T Value)] sa da nastavit aka VALUE sa ma vratit, ak sa zavola dana METHOD MOCK OBJECT s danymi PARAMETERS.
		when(MAccountRepository.findById(Sender.getId())).thenReturn(Optional.of(Sender));

		// !!!!! Pomocou METHOD [<T> OngoingStubbing<T> Mockito.when(T MethodCall)] a METHOD [OngoingStubbing<T> OngoingStubbing<T>.thenReturn(T Value)] sa da nastavit aka VALUE sa ma vratit, ak sa zavola dana METHOD MOCK OBJECT s danymi PARAMETERS.
		when(MAccountRepository.findById(Destination.getId())).thenReturn(Optional.of(Destination));
	
		// !!!!! Spusti sa testovana METHOD.
		MAccountService.TransferAmount(1,2,200,false);

		// !!!!! Pomocou METHOD [<T> T Mockito.verify(T Mock)] sa vykona kontrola bola zavolana METHOD MOCK OBJECT so spravnymi PARAMETERS.
		verify(MAccountRepository).ChangeAmount(1,800);
		
		// !!!!! Pomocou METHOD [<T> T Mockito.verify(T Mock)] sa vykona kontrola bola zavolana METHOD MOCK OBJECT so spravnymi PARAMETERS.
		verify(MAccountRepository).ChangeAmount(2,1200);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------