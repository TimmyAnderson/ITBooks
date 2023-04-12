package Chapter15.MyTests;
//----------------------------------------------------------------------------------------------------------------------
import static org.mockito.BDDMockito.given;
import static org.mockito.Mockito.mock;
import static org.mockito.Mockito.verify;
//----------------------------------------------------------------------------------------------------------------------
import java.util.Optional;
import org.junit.jupiter.api.DisplayName;
import org.junit.jupiter.api.Test;
import Chapter15.Testing.Repository.Account;
import Chapter15.Testing.Repository.CAccountService;
import Chapter15.Testing.Repository.IAccountRepository;
//----------------------------------------------------------------------------------------------------------------------
public class CMyTests1
{
//----------------------------------------------------------------------------------------------------------------------
	@Test
	@DisplayName("This is MY TEST OK 1.")
	public void MyTestOK1()
	{
		// !!!!! Pomocou MOCK FRAMEWORK sa vytvori MOCK OBJECT.
		// !!!!! METHOD [<T> T Mockito.mock(Class<T> ClassToMock)] je sucastou MOCKITO MOCK FRAMEWORK a umoznuje vytvarat EMPTY MOCK OBJECTS.
		IAccountRepository										AccountRepository=mock(IAccountRepository.class);

		// !!! Vytvori sa SERVICE OBJECT s pouzitim MOCK OBJECT.
		CAccountService											AccountService=new CAccountService(AccountRepository);

		// !!!!! Pripravia sa DATA pre MOCK OBJECT.
		Account													Sender=new Account();
		
		Sender.setId(1);
		Sender.setAmount(1000);
		
		Account													Destination=new Account();
		
		Destination.setId(2);
		Destination.setAmount(1000);

		// !!!!! Pomocou METHOD [<T> BDDMockito.BDDMyOngoingStubbing<T> given(T MethodCall)] a METHOD [BDDMyOngoingStubbing<T> BDDMockito.willReturn(T Value)] sa da nastavit aka VALUE sa ma vratit, ak sa zavola dana METHOD MOCK OBJECT s danymi PARAMETERS.
		given(AccountRepository.findById(Sender.getId())).willReturn(Optional.of(Sender));

		// !!!!! Pomocou METHOD [<T> BDDMockito.BDDMyOngoingStubbing<T> given(T MethodCall)] a METHOD [BDDMyOngoingStubbing<T> BDDMockito.willReturn(T Value)] sa da nastavit aka VALUE sa ma vratit, ak sa zavola dana METHOD MOCK OBJECT s danymi PARAMETERS.
		given(AccountRepository.findById(Destination.getId())).willReturn(Optional.of(Destination));

		// !!!!! Spusti sa testovana METHOD.
		AccountService.TransferAmount(1,2,200,false);

		// !!!!! Pomocou METHOD [<T> T Mockito.verify(T Mock)] sa vykona kontrola bola zavolana METHOD MOCK OBJECT so spravnymi PARAMETERS.
		verify(AccountRepository).ChangeAmount(1,800);
		
		// !!!!! Pomocou METHOD [<T> T Mockito.verify(T Mock)] sa vykona kontrola bola zavolana METHOD MOCK OBJECT so spravnymi PARAMETERS.
		verify(AccountRepository).ChangeAmount(2,1200);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------