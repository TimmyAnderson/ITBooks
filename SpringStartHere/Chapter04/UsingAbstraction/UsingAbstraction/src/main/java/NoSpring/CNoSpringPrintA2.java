//----------------------------------------------------------------------------------------------------------------------
package NoSpring;
//----------------------------------------------------------------------------------------------------------------------
public class CNoSpringPrintA2 implements INoSpringPrintA
{
//----------------------------------------------------------------------------------------------------------------------
	@Override
	public void DoPrint1(CNoSpringMessage Message)
	{
		System.out.format("FROM [CNoSpringPrintA2] - MESSAGE [%s] !\n",Message.getMessage());
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------