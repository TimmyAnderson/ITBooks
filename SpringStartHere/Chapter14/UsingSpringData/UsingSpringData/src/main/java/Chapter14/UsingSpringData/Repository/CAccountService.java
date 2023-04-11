package Chapter14.UsingSpringData.Repository;
//----------------------------------------------------------------------------------------------------------------------
import java.util.List;
import java.util.Optional;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;
//----------------------------------------------------------------------------------------------------------------------
@Service
public class CAccountService
{
//----------------------------------------------------------------------------------------------------------------------
	private final IAccountRepository							MAccountRepository;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	public CAccountService(IAccountRepository AccountRepository)
	{
		MAccountRepository=AccountRepository;
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	public List<Account> GetAllAccounts()
	{
		List<Account>											Accounts=MAccountRepository.findAccounts();
	
		return(Accounts);
	}
//----------------------------------------------------------------------------------------------------------------------
	public List<Account> GetAccountsByName(String Name)
	{
		List<Account>											Accounts=MAccountRepository.findAccountsByName(Name);
	
		return(Accounts);
	}
//----------------------------------------------------------------------------------------------------------------------
	// !!!!! METHOD VYKONAVA MUTABLE OPERATIONS, a preto MUSI bezat v TRANSACTION.
	@Transactional
	public void TransferAmount(int SenderID, int ReceiverID, int Amount, boolean ThrowException)
	{
		// !!!!! METHOD [Optional<T> CrudRepository<T,ID>.findById(ID Id)] je definovana v INTERFACE [CrudRepository<T,ID>].
		Optional<Account>										Sender=MAccountRepository.findById(SenderID);
		Optional<Account>										Receiver=MAccountRepository.findById(ReceiverID);

		if (Sender.isPresent()==false)
		{
			throw(new CMyException("SENDER NOT FOUND !!!"));
		}

		if (Receiver.isPresent()==false)
		{
			throw(new CMyException("RECEIVER NOT FOUND !!!"));
		}
	
		int														SenderNewAmount=(Sender.get().getAmount()-Amount);
		int														ReceiverNewAmount=(Receiver.get().getAmount()+Amount);
	
		MAccountRepository.ChangeAmount(SenderID,SenderNewAmount);
	
		MAccountRepository.ChangeAmount(ReceiverID,ReceiverNewAmount);

		if (ThrowException==true)
		{
			throw(new CMyException("My EXCEPTION !!!"));
		}
	}	
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------