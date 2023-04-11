package Chapter13.UsingTransactions.Transactions;
//----------------------------------------------------------------------------------------------------------------------
import java.util.List;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;
//----------------------------------------------------------------------------------------------------------------------
@Service
public class CAccountService
{
//----------------------------------------------------------------------------------------------------------------------
	private final CAccountRepository							MAccountRepository;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	public CAccountService(CAccountRepository AccountRepository)
	{
		MAccountRepository=AccountRepository;
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	// !!!!! METHOD NEVYKONAVA MUTABLE OPERATIONS a tym padom NEMUSI bezat v TRANSACTION.
	public List<CAccount> GetAllAccounts()
	{
		List<CAccount>											AllAccounts=MAccountRepository.GetAllAccounts();
	
		return(AllAccounts);
	}
//----------------------------------------------------------------------------------------------------------------------
	// !!!!! METHOD VYKONAVA MUTABLE OPERATIONS, a preto MUSI bezat v TRANSACTION.
	@Transactional
	public void TransferAmount(int SenderID, int ReceiverID, int Amount, boolean ThrowException)
	{
		CAccount												Sender=MAccountRepository.GetAccount(SenderID);
		CAccount												Receiver=MAccountRepository.GetAccount(ReceiverID);
	
		int														SenderNewAmount=(Sender.getAmount()-Amount);
		int														ReceiverNewAmount=(Receiver.getAmount()+Amount);
	
		MAccountRepository.ChangeAmount(SenderID,SenderNewAmount);
	
		MAccountRepository.ChangeAmount(ReceiverID,ReceiverNewAmount);

		if (ThrowException==true)
		{
			throw(new RuntimeException("My EXCEPTION !!!"));
		}
	}	
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------