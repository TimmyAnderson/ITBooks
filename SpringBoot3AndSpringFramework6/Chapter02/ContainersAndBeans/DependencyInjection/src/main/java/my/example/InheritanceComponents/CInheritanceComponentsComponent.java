package my.example.InheritanceComponents;
import org.springframework.beans.factory.annotation.Autowired;
//----------------------------------------------------------------------------------------------------------------------
import org.springframework.stereotype.Component;
//----------------------------------------------------------------------------------------------------------------------
@Component
public class CInheritanceComponentsComponent
{
//----------------------------------------------------------------------------------------------------------------------
	private final CInheritanceComponentsBean1					bean1;
	private final CInheritanceComponentsBeanBase2				beanBase2;
	private final CInheritanceComponentsBeanDerived2			beanDerived2;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	@Autowired
	public CInheritanceComponentsComponent(CInheritanceComponentsBean1 bean1, CInheritanceComponentsBeanBase2 beanBase2, @Autowired(required=false) CInheritanceComponentsBeanDerived2 beanDerived2)
	{
		this.bean1=bean1;
		this.beanBase2=beanBase2;
		this.beanDerived2=beanDerived2;
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	public void Test()
	{
		String													beanText1=(bean1!=null) ? bean1.GetText() : "";
		String													beanBaseText2=(beanBase2!=null) ? beanBase2.GetText() : "";
		String													beanDerivedText2=(beanDerived2!=null) ? beanDerived2.GetText() : "";
		
		System.out.printf("BEAN 1 - VALUE [%s].\n",beanText1);
		System.out.printf("BEAN BASE 2 - VALUE [%s].\n",beanBaseText2);
		System.out.printf("BEAN DERIVED 2 - VALUE [%s].\n",beanDerivedText2);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------