//----------------------------------------------------------------------------------------------------------------------
package Spring1;
//----------------------------------------------------------------------------------------------------------------------
// !!!!! Tato CLASS UMYSELNE NIE JE oznacena ANNOTATION [@Component], pretoze SPRING FRAMEWORK by NEVEDEL rozlisit, ktoru implementaciu INTERFACE [ISpring1PrintA] ma pouzit. 
public class CSpring1PrintA2 implements ISpring1PrintA
{
//----------------------------------------------------------------------------------------------------------------------
	@Override
	public void DoPrint1(CSpring1Message Message)
	{
		System.out.format("FROM [CSpring1PrintA2] - MESSAGE [%s] !\n",Message.getMessage());
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------