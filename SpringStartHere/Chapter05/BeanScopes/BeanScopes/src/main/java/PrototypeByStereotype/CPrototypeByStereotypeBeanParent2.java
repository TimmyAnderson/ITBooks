//----------------------------------------------------------------------------------------------------------------------
package PrototypeByStereotype;
//----------------------------------------------------------------------------------------------------------------------
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.config.BeanDefinition;
import org.springframework.context.annotation.Scope;
import org.springframework.stereotype.Component;
//----------------------------------------------------------------------------------------------------------------------
@Component
// !!! BEAN je oznaceny ako PROROTYPE SCOPE BEAN.
@Scope(BeanDefinition.SCOPE_PROTOTYPE) 
public class CPrototypeByStereotypeBeanParent2
{
//----------------------------------------------------------------------------------------------------------------------
	@Autowired
	private CPrototypeByStereotypeBeanChild						MChild;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	public CPrototypeByStereotypeBeanParent2()
	{
		System.out.format("BEAN [CPrototypeByStereotypeBeanParent2] CREATED.\n");
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	public CPrototypeByStereotypeBeanChild getChild()
	{
		return(MChild);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------