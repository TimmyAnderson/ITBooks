//----------------------------------------------------------------------------------------------------------------------
package NoSpring;
//----------------------------------------------------------------------------------------------------------------------
public class CNoSpringPrintB2 implements INoSpringPrintB
{
//----------------------------------------------------------------------------------------------------------------------
	@Override
	public void DoPrint2(CNoSpringMessage Message)
	{
		System.out.format("FROM [CNoSpringPrintB2] - MESSAGE [%s] !\n",Message.getMessage());
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------