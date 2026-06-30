package my.example.CyclicDependencies;
//----------------------------------------------------------------------------------------------------------------------
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.context.annotation.Lazy;
import org.springframework.stereotype.Component;
//----------------------------------------------------------------------------------------------------------------------
// !!!!! ANNOTATION [@Lazy] riesi CYCLIC DEPENDENCY.
@Lazy
@Component
public class CCyclicDependenciesLazyComponent
{
//----------------------------------------------------------------------------------------------------------------------
	private final CCyclicDependenciesLazyBean1					bean1;
	private final CCyclicDependenciesLazyBean2					bean2;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	@Autowired
	public CCyclicDependenciesLazyComponent(CCyclicDependenciesLazyBean1 bean1, CCyclicDependenciesLazyBean2 bean2)
	{
		this.bean1=bean1;
		this.bean2=bean2;
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	public void Test()
	{
		String													TextBean1=bean1.Print();
		String													TextBean2=bean2.Print();
		
		System.out.printf("MISSING BEANS - BEAN 1 [%s].\n",TextBean1);
		System.out.printf("MISSING BEANS - BEAN 2 [%s].\n",TextBean2);
	}	
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------