//----------------------------------------------------------------------------------------------------------------------
package SpringMultiImplementationQualifier;
//----------------------------------------------------------------------------------------------------------------------
// !!! CLASS NIE JE pridavana do SPRING CONTEXT, kedze nevyuziva ziadnu funkcionalitu SPRING FRAMEWORK.
public class CSpringMultiImplementationQualifierMessage
{
//----------------------------------------------------------------------------------------------------------------------
	private final String										MMessage;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	public CSpringMultiImplementationQualifierMessage(String Message)
	{
		MMessage=Message;	
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	public String getMessage()
	{
		return(MMessage);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------