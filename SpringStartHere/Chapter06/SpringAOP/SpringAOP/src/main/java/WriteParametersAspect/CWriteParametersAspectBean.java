//----------------------------------------------------------------------------------------------------------------------
package WriteParametersAspect;
//----------------------------------------------------------------------------------------------------------------------
import org.springframework.stereotype.Component;
//----------------------------------------------------------------------------------------------------------------------
// !!! CLASS reprezentuje SPRING BEAN na ktory su aplikovane ASPECTS.
@Component
public class CWriteParametersAspectBean
{
//----------------------------------------------------------------------------------------------------------------------
	public String PrintMessage(CWriteParametersAspectMessage Message)
	{
		System.out.format("MESSAGE - TEXT 1 [%s] TEXT 2 [%s].\n",Message.getText1(),Message.getText2());
		
		return("My RETURN VALUE.");	
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------