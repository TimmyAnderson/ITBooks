package Chapter15.MyTests;
//----------------------------------------------------------------------------------------------------------------------
import static org.junit.jupiter.api.Assertions.assertThrows;
import static org.mockito.ArgumentMatchers.anyInt;
import static org.mockito.BDDMockito.given;
import static org.mockito.Mockito.never;
import static org.mockito.Mockito.verify;
//----------------------------------------------------------------------------------------------------------------------
import java.util.Optional;
import org.junit.jupiter.api.DisplayName;
import org.junit.jupiter.api.extension.ExtendWith;
import org.junit.jupiter.api.Test;
import org.mockito.InjectMocks;
import org.mockito.Mock;
import org.mockito.junit.jupiter.MockitoExtension;
import Chapter15.Testing.Repository.Account;
import Chapter15.Testing.Repository.CAccountService;
import Chapter15.Testing.Repository.CMyException;
import Chapter15.Testing.Repository.IAccountRepository;
//----------------------------------------------------------------------------------------------------------------------
// !!!!! ANNOTATION [@ExtendWith(MockitoExtension.class)] umozni MOCK LIBRARY [Mockito] aby vedela, ze musi vytvorit MOCK OBJECTS.
@ExtendWith(MockitoExtension.class)
public class CMyTests2
{
//----------------------------------------------------------------------------------------------------------------------
	// !!!!! Na FIELDS do ktorych maju byt ulozene MOCK OBJECTS aplikuje ANNOTATION [@Mock], aby MOCK LIBRARY [Mockito] tieto FIELDS naplnil instanciami MOCK OBJECTS.
	@Mock
	private IAccountRepository									MAccountRepository;
//----------------------------------------------------------------------------------------------------------------------
	// !!!!! Na FIELDS do ktorych maju byt ulozene OBJECTS, v ktorych sa pouzivaju MOCK OBJECTS je potrebne aplikovat ANNOTATION [@InjectMocks], aby MOCK LIBRARY [Mockito] vytvoril aj s nastavenymi MOCK OBJECTS.
	@InjectMocks
	private CAccountService										MAccountService;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	@Test
	@DisplayName("This is MY TEST OK 2.")
	public void MyTestOK2()
	{
		// !!!!! Pripravia sa DATA pre MOCK OBJECT.
		Account													Sender=new Account();
		
		Sender.setId(1);
		Sender.setAmount(1000);
		
		Account													Destination=new Account();
		
		Destination.setId(2);
		Destination.setAmount(1000);

		// !!!!! Pomocou METHOD [<T> BDDMockito.BDDMyOngoingStubbing<T> given(T MethodCall)] a METHOD [BDDMyOngoingStubbing<T> BDDMockito.willReturn(T Value)] sa da nastavit aka VALUE sa ma vratit, ak sa zavola dana METHOD MOCK OBJECT s danymi PARAMETERS.
		given(MAccountRepository.findById(Sender.getId())).willReturn(Optional.of(Sender));

		// !!!!! Pomocou METHOD [<T> BDDMockito.BDDMyOngoingStubbing<T> given(T MethodCall)] a METHOD [BDDMyOngoingStubbing<T> BDDMockito.willReturn(T Value)] sa da nastavit aka VALUE sa ma vratit, ak sa zavola dana METHOD MOCK OBJECT s danymi PARAMETERS.
		given(MAccountRepository.findById(Destination.getId())).willReturn(Optional.of(Destination));

		// !!!!! Spusti sa testovana METHOD.
		MAccountService.TransferAmount(1,2,200,false);

		// !!!!! Pomocou METHOD [<T> T Mockito.verify(T Mock)] sa vykona kontrola bola zavolana METHOD MOCK OBJECT so spravnymi PARAMETERS.
		verify(MAccountRepository).ChangeAmount(1,800);
		
		// !!!!! Pomocou METHOD [<T> T Mockito.verify(T Mock)] sa vykona kontrola bola zavolana METHOD MOCK OBJECT so spravnymi PARAMETERS.
		verify(MAccountRepository).ChangeAmount(2,1200);
	}
//----------------------------------------------------------------------------------------------------------------------
	@Test
	@DisplayName("This is MY TEST ERROR.")
	public void MyTestERROR()
	{
		// !!!!! Pripravia sa DATA pre MOCK OBJECT.
		Account													Sender=new Account();
		
		Sender.setId(1);
		Sender.setAmount(1000);
	
		// !!!!! Pomocou METHOD [<T> BDDMockito.BDDMyOngoingStubbing<T> given(T MethodCall)] a METHOD [BDDMyOngoingStubbing<T> BDDMockito.willReturn(T Value)] sa da nastavit aka VALUE sa ma vratit, ak sa zavola dana METHOD MOCK OBJECT s danymi PARAMETERS.
		given(MAccountRepository.findById(Sender.getId())).willReturn(Optional.of(Sender));
	
		// !!!!! Pomocou METHOD [<T> BDDMockito.BDDMyOngoingStubbing<T> given(T MethodCall)] a METHOD [BDDMyOngoingStubbing<T> BDDMockito.willReturn(T Value)] sa da nastavit aka VALUE sa ma vratit, ak sa zavola dana METHOD MOCK OBJECT s danymi PARAMETERS.
		// !!!!! UMYSELNE sa nastavi, aby pre volanie [MAccountRepository.findById(2)] vracal MOCK OBJECT NULL.
		given(MAccountRepository.findById(2)).willReturn(Optional.empty());

		// !!!!! Pomocou METHOD [<T extends Throwable> T Assertions.assertThrows(Class<T> ExpectedType, Executable Executable)] sa zavola testovana METHOD 'Executable', pricom sa ocakava, ze METHOD hodi EXCEPTION TYPE 'ExpectedType'.
		assertThrows(CMyException.class,() -> MAccountService.TransferAmount(1,2,200,false));

		// !!!!! Vykona sa kontrola, ze sa dana METHOD VOBEC NEZAVOLALA, pretoze jej CODE je az za vznikom EXCEPTION.
    	verify(MAccountRepository,never()).ChangeAmount(anyInt(),anyInt());
	}	
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------