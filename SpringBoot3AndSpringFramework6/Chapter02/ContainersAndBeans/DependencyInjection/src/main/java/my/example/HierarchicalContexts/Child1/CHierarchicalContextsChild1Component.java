package my.example.HierarchicalContexts.Child1;
//----------------------------------------------------------------------------------------------------------------------
import org.springframework.beans.factory.annotation.Autowired;

import org.springframework.stereotype.Component;

import my.example.HierarchicalContexts.Child2.CHierarchicalContextsChild2Bean1;
import my.example.HierarchicalContexts.Child2.CHierarchicalContextsChild2Bean2;
import my.example.HierarchicalContexts.Parent.CHierarchicalContextsParentBean1;
import my.example.HierarchicalContexts.Parent.CHierarchicalContextsParentBean2;
//----------------------------------------------------------------------------------------------------------------------
@Component
public class CHierarchicalContextsChild1Component
{
//----------------------------------------------------------------------------------------------------------------------
	private final CHierarchicalContextsChild1Bean1				localBean1;
	private final CHierarchicalContextsChild1Bean2				localBean2;
	// !!!!! V CHILD CONTEXT su pristupne BEANS z PARENT CONTEXT.
	private final CHierarchicalContextsParentBean1				parentBean1;
	private final CHierarchicalContextsParentBean2				parentBean2;
	// !!!!! V CHILD CONTEXT NIE su pristupne BEANS zo SIBLING CONTEXT.
	private final CHierarchicalContextsChild2Bean1				child2Bean1;
	private final CHierarchicalContextsChild2Bean2				child2Bean2;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	@Autowired
	public CHierarchicalContextsChild1Component(CHierarchicalContextsChild1Bean1 localBean1, CHierarchicalContextsChild1Bean2 localBean2, CHierarchicalContextsParentBean1 parentBean1, CHierarchicalContextsParentBean2 parentBean2, @Autowired(required=false) CHierarchicalContextsChild2Bean1 child2Bean1, @Autowired(required=false) CHierarchicalContextsChild2Bean2 child2Bean2)
	{
		this.localBean1=localBean1;
		this.localBean2=localBean2;
		this.parentBean1=parentBean1;
		this.parentBean2=parentBean2;
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
		String													parentBeanText1=parentBean1.GetText();
		String													parentBeanText2=parentBean2.GetText();
		String													child2BeanText1=(child2Bean1!=null) ? child2Bean1.GetText() : "";
		String													child2BeanText2=(child2Bean2!=null) ? child2Bean2.GetText() : "";
		
		System.out.printf("CHILD 1 - LOCAL BEAN 1 - VALUE [%s].\n",localBeanText1);
		System.out.printf("CHILD 1 - LOCAL BEAN 2 - VALUE [%s].\n",localBeanText2);
		System.out.printf("CHILD 1 - PARENT BEAN 1 - VALUE [%s].\n",parentBeanText1);
		System.out.printf("CHILD 1 - PARENT BEAN 2 - VALUE [%s].\n",parentBeanText2);
		System.out.printf("CHILD 1 - CHILD 2 BEAN 1 - VALUE [%s].\n",child2BeanText1);
		System.out.printf("CHILD 1 - CHILD 2 BEAN 2 - VALUE [%s].\n",child2BeanText2);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------