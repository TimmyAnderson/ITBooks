//----------------------------------------------------------------------------------------------------------------------
package PrototypeByStereotype;
//----------------------------------------------------------------------------------------------------------------------
import org.springframework.beans.factory.config.BeanDefinition;
import org.springframework.context.annotation.Scope;
import org.springframework.stereotype.Component;
//----------------------------------------------------------------------------------------------------------------------
@Component
// !!! BEAN je oznaceny ako PROROTYPE SCOPE BEAN.
@Scope(BeanDefinition.SCOPE_PROTOTYPE) 
public class CPrototypeByStereotypeBeanChild
{
//----------------------------------------------------------------------------------------------------------------------
	public CPrototypeByStereotypeBeanChild()
	{
		System.out.format("BEAN [CPrototypeByStereotypeBeanChild] CREATED.\n");
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------