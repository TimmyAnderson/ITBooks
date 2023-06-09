//----------------------------------------------------------------------------------------------------------------------
package NoSpring;
//----------------------------------------------------------------------------------------------------------------------
public class CNoSpringPrinter
{
//----------------------------------------------------------------------------------------------------------------------
	private final INoSpringPrintA								MPrintA;
	private final INoSpringPrintB								MPrintB;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	public CNoSpringPrinter(INoSpringPrintA PrintA, INoSpringPrintB PrintB)
	{
		MPrintA=PrintA;	
		MPrintB=PrintB;	
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	public void PrintMessage(CNoSpringMessage Message)
	{
		MPrintA.DoPrint1(Message);
		MPrintB.DoPrint2(Message);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------