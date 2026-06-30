package my.example.BeanInitializationProblem;
//----------------------------------------------------------------------------------------------------------------------
import org.springframework.beans.factory.annotation.Autowired;

import org.springframework.stereotype.Component;
//----------------------------------------------------------------------------------------------------------------------
@Component
public class CBeanInitializationProblemComponent
{
//----------------------------------------------------------------------------------------------------------------------
	private final CBeanInitializationProblemBean1				bean1;
//----------------------------------------------------------------------------------------------------------------------
	@Autowired
	private CBeanInitializationProblemBean2						bean2;
	private CBeanInitializationProblemBean3						bean3;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	@Autowired
	public CBeanInitializationProblemComponent(CBeanInitializationProblemBean1 bean1)
	{
		this.bean1=bean1;
		
		System.out.printf("!!! COMPONENT CONSTRUCTOR is CALLED.\n");
		
		// !!!!! CONSTRUCTOR sa vola SKOR ako sa vykona FIELDS AUTOWIRING a SETTERS AUTOWIRING a preto FIELD BEAN a SETTER BEAN su v CONSTRCTOR nastavene na VALUE [null].
		System.out.printf("!!! COMPONENT CONSTRUCTOR BEAN 1 EXISTS [%s].\n",bean1!=null);
		System.out.printf("!!! COMPONENT CONSTRUCTOR BEAN 2 EXISTS [%s].\n",bean2!=null);
		System.out.printf("!!! COMPONENT CONSTRUCTOR BEAN 3 EXISTS [%s].\n",bean3!=null);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	@Autowired
	public void MySetter(CBeanInitializationProblemBean3 bean3)
	{
		this.bean3=bean3;
		
		System.out.printf("!!! COMPONENT SETTER is CALLED.\n");
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	public void Test()
	{
		String													beanText1=bean1.GetText();
		String													beanText2=bean2.GetText();
		String													beanText3=bean3.GetText();
		
		System.out.printf("BEAN 1 - VALUE [%s].\n",beanText1);
		System.out.printf("BEAN 2 - VALUE [%s].\n",beanText2);
		System.out.printf("BEAN 3 - VALUE [%s].\n",beanText3);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------