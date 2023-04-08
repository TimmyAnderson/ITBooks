//----------------------------------------------------------------------------------------------------------------------
package MyLogAspect;
//----------------------------------------------------------------------------------------------------------------------
import org.springframework.stereotype.Component;
//----------------------------------------------------------------------------------------------------------------------
// !!! CLASS reprezentuje SPRING BEAN na ktory su aplikovane ASPECTS.
@Component
public class CMyLogAspectBean
{
//----------------------------------------------------------------------------------------------------------------------
	public void PrintMessage(CMyLogAspectMessage Message)
	{
		System.out.format("MESSAGE - TEXT 1 [%s] TEXT 2 [%s].\n",Message.getText1(),Message.getText2());	
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------