//----------------------------------------------------------------------------------------------------------------------
package NoSpring;
//----------------------------------------------------------------------------------------------------------------------
public class CNoSpringPrintA1 implements INoSpringPrintA
{
//----------------------------------------------------------------------------------------------------------------------
	@Override
	public void DoPrint1(CNoSpringMessage Message)
	{
		System.out.format("FROM [CNoSpringPrintA1] - MESSAGE [%s] !\n",Message.getMessage());
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------