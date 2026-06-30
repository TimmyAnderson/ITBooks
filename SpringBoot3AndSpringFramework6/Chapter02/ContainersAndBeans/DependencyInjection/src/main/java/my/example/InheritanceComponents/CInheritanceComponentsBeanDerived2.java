package my.example.InheritanceComponents;
//----------------------------------------------------------------------------------------------------------------------
// !!!!! ANNOTATION [@Component] NIE je INHERITED. A preto TYPE NIE je COMPONENT.
public class CInheritanceComponentsBeanDerived2 extends CInheritanceComponentsBeanBase2
{
//----------------------------------------------------------------------------------------------------------------------
	@Override
	public String GetText()
	{
		return("From BEAN DERIVED 2.");
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------