//----------------------------------------------------------------------------------------------------------------------
package Spring1;
//----------------------------------------------------------------------------------------------------------------------
// !!!!! Tato CLASS UMYSELNE NIE JE oznacena ANNOTATION [@Component], pretoze SPRING FRAMEWORK by NEVEDEL rozlisit, ktoru implementaciu INTERFACE [ISpring1PrintB] ma pouzit. 
public class CSpring1PrintB2 implements ISpring1PrintB
{
//----------------------------------------------------------------------------------------------------------------------
	@Override
	public void DoPrint2(CSpring1Message Message)
	{
		System.out.format("FROM [CSpring1PrintB2] - MESSAGE [%s] !\n",Message.getMessage());
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------