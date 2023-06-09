//----------------------------------------------------------------------------------------------------------------------
package WriteParametersAspect;
//----------------------------------------------------------------------------------------------------------------------
// !!! Toto NIE JE SPRING BEAN OBJECT.
public class CWriteParametersAspectMessage
{
//----------------------------------------------------------------------------------------------------------------------
	private final String										MText1;
	private final String										MText2;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	public CWriteParametersAspectMessage(String Text1, String Text2)
	{
		MText1=Text1;
		MText2=Text2;
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	public String getText1()
	{
		return(MText1);
	}
//----------------------------------------------------------------------------------------------------------------------
	public String getText2()
	{
		return(MText2);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	@Override
	public String toString()
	{
		String													Text=String.format("TYPE [CReadParametersAspectMessage] - TEXT 1 [%s] TEXT 2 [%s].",MText1,MText2);	
	
		return(Text);
	}	
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------