package Chapter14.UsingSpringData.Repository;
//----------------------------------------------------------------------------------------------------------------------
import java.util.List;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;
//----------------------------------------------------------------------------------------------------------------------
@RestController
public class CAccountController
{
//----------------------------------------------------------------------------------------------------------------------
	private final CAccountService								MAccountService;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	public CAccountController(CAccountService AccountService)
	{
		MAccountService=AccountService;
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	// CURL [curl -v -X GET localhost:8080/GetAllAccounts].
	@GetMapping("/GetAllAccounts")
	public List<Account> GetAllAccounts()
	{
		List<Account>											AllAccounts=MAccountService.GetAllAccounts();
	
		return(AllAccounts);
	}
//----------------------------------------------------------------------------------------------------------------------
	// CURL [curl -v -X GET localhost:8080/GetAccountsByName?Name=Timmy].
	// CURL [curl -v -X GET localhost:8080/GetAccountsByName?Name=Jenny].
	@GetMapping("/GetAccountsByName")
	public List<Account> GetAccountsByName(@RequestParam String Name)
	{
		List<Account>											AllAccounts=MAccountService.GetAccountsByName(Name);
	
		return(AllAccounts);
	}
//----------------------------------------------------------------------------------------------------------------------
	// CURL [curl -v -X POST localhost:8080/TransferAmountCommit -H "Content-Type: application/json" -d "{\"senderID\":1,\"receiverID\":2,\"amount\":200}"].
	@PostMapping("/TransferAmountCommit")
	public void TransferAmountCommit(@RequestBody CTransferRequest TransferRequest)
	{
		int														SenderID=TransferRequest.getSenderID();
		int														ReceiverID=TransferRequest.getReceiverID();
		int														Amount=TransferRequest.getAmount();
		boolean													ThrowException=false;

		MAccountService.TransferAmount(SenderID,ReceiverID,Amount,ThrowException);
	}
//----------------------------------------------------------------------------------------------------------------------
	// CURL [curl -v -X POST localhost:8080/TransferAmountRollback -H "Content-Type: application/json" -d "{\"senderID\":1,\"receiverID\":2,\"amount\":200}"].
	@PostMapping("/TransferAmountRollback")
	public void TransferAmountRollback(@RequestBody CTransferRequest TransferRequest)
	{
		int														SenderID=TransferRequest.getSenderID();
		int														ReceiverID=TransferRequest.getReceiverID();
		int														Amount=TransferRequest.getAmount();
		boolean													ThrowException=true;

		MAccountService.TransferAmount(SenderID,ReceiverID,Amount,ThrowException);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------