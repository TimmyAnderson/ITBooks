package my.example.HierarchicalContexts.Parent;
//----------------------------------------------------------------------------------------------------------------------
import org.springframework.beans.factory.annotation.Autowired;

import org.springframework.stereotype.Component;

import my.example.HierarchicalContexts.Child1.CHierarchicalContextsChild1Bean1;
import my.example.HierarchicalContexts.Child1.CHierarchicalContextsChild1Bean2;
import my.example.HierarchicalContexts.Child2.CHierarchicalContextsChild2Bean1;
import my.example.HierarchicalContexts.Child2.CHierarchicalContextsChild2Bean2;
//----------------------------------------------------------------------------------------------------------------------
@Component
public class CHierarchicalContextsParentComponent
{
//----------------------------------------------------------------------------------------------------------------------
	private final CHierarchicalContextsParentBean1				localBean1;
	private final CHierarchicalContextsParentBean2				localBean2;
	// !!!!! V PARENT CONTEXT NIE su pristupne BEANS z CHILD CONTEXT.
	private final CHierarchicalContextsChild1Bean1				child1Bean1;
	private final CHierarchicalContextsChild1Bean2				child1Bean2;
	private final CHierarchicalContextsChild2Bean1				child2Bean1;
	private final CHierarchicalContextsChild2Bean2				child2Bean2;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	@Autowired
	public CHierarchicalContextsParentComponent(CHierarchicalContextsParentBean1 localBean1, CHierarchicalContextsParentBean2 localBean2, @Autowired(required=false) CHierarchicalContextsChild1Bean1 child1Bean1, @Autowired(required=false) CHierarchicalContextsChild1Bean2 child1Bean2, @Autowired(required=false) CHierarchicalContextsChild2Bean1 child2Bean1, @Autowired(required=false) CHierarchicalContextsChild2Bean2 child2Bean2)
	{
		this.localBean1=localBean1;
		this.localBean2=localBean2;
		this.child1Bean1=child1Bean1;
		this.child1Bean2=child1Bean2;
		this.child2Bean1=child2Bean1;
		this.child2Bean2=child2Bean2;
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	public void Test()
	{
		String													localBeanText1=localBean1.GetText();
		String													localBeanText2=localBean2.GetText();
		String													child1BeanText1=(child1Bean1!=null) ? child1Bean1.GetText() : "";
		String													child1BeanText2=(child1Bean2!=null) ? child1Bean2.GetText() : "";
		String													child2BeanText1=(child2Bean1!=null) ? child2Bean1.GetText() : "";
		String													child2BeanText2=(child2Bean2!=null) ? child2Bean2.GetText() : "";
		
		System.out.printf("PARENT - LOCAL BEAN 1 - VALUE [%s].\n",localBeanText1);
		System.out.printf("PARENT - LOCAL BEAN 2 - VALUE [%s].\n",localBeanText2);
		System.out.printf("PARENT - CHILD 1 BEAN 1 - VALUE [%s].\n",child1BeanText1);
		System.out.printf("PARENT - CHILD 1 BEAN 2 - VALUE [%s].\n",child1BeanText2);
		System.out.printf("PARENT - CHILD 2 BEAN 1 - VALUE [%s].\n",child2BeanText1);
		System.out.printf("PARENT - CHILD 2 BEAN 2 - VALUE [%s].\n",child2BeanText2);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------