package Chapter13.UsingTransactions.Transactions;
//----------------------------------------------------------------------------------------------------------------------
public class CTransferRequest
{
//----------------------------------------------------------------------------------------------------------------------
	private int													MSenderID;
	private int													MReceiverID;
	private int													MAmount;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	public CTransferRequest()
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	public int getSenderID()
	{
		return(MSenderID);
	}
//----------------------------------------------------------------------------------------------------------------------
	public void setSenderID(int SenderID)
	{
		MSenderID=SenderID;
	}
//----------------------------------------------------------------------------------------------------------------------
	public int getReceiverID()
	{
		return(MReceiverID);
	}
//----------------------------------------------------------------------------------------------------------------------
	public void setReceiverID(int ReceiverID)
	{
		MReceiverID=ReceiverID;
	}
//----------------------------------------------------------------------------------------------------------------------
	public int getAmount()
	{
		return(MAmount);
	}
//----------------------------------------------------------------------------------------------------------------------
	public void setAmount(int Amount)
	{
		MAmount=Amount;
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------