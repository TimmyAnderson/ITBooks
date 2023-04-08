//----------------------------------------------------------------------------------------------------------------------
package PrototypeBeanInSingletonBean;
//----------------------------------------------------------------------------------------------------------------------
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.context.ApplicationContext;
import org.springframework.stereotype.Component;
//----------------------------------------------------------------------------------------------------------------------
@Component
public class CPrototypeBeanInSingletonBeanSingleton
{
//----------------------------------------------------------------------------------------------------------------------
	// !!!!! Vlozi sa SPRING BEAN TYPE [ApplicationContext], aby z neho mohli byt vytvarane instancie SPRIN BEANS [CPrototypeBeanInSingletonBeanPrototype].
	@Autowired
	private ApplicationContext									MContext;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	public CPrototypeBeanInSingletonBeanSingleton()
	{
		System.out.println("BEAN [CPrototypeBeanInSingletonBeanSingleton] CREATED.");
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	public void Execute()
	{
		System.out.println("BEANS [CPrototypeBeanInSingletonBeanPrototype] CREATING.");
	
		// !!! Ziskaju sa instancie na SPRING BEANS [CPrototypeBeanInSingletonBeanPrototype], ktore su v PROTOTYPE SCOPE.
		// !!!!! Kedze 	SPRING BEANS [CPrototypeBeanInSingletonBeanPrototype] su v PROTOTYPE SCOPE, tak sa pre kazde volanie SPRING CONTEXT vytvori NOVA instancia SPRING BEAN [CPrototypeBeanInSingletonBeanPrototype].
		CPrototypeBeanInSingletonBeanPrototype					Bean1=MContext.getBean(CPrototypeBeanInSingletonBeanPrototype.class);
		CPrototypeBeanInSingletonBeanPrototype					Bean2=MContext.getBean(CPrototypeBeanInSingletonBeanPrototype.class);

		System.out.println("BEANS [CPrototypeBeanInSingletonBeanPrototype] CREATED.");

		Bean1.setValue("BEAN 1");
		Bean2.setValue("BEAN 2");
	
		Bean1.Print();
		Bean2.Print();
		
		// Vrati FALSE.
		if (Bean1==Bean2)
		{
			System.out.format("BEAN [Bean1] and BEAN [Bean2] point to the SAME OBJECT !\n");
		}
		else
		{
			System.out.format("BEAN [Bean1] and BEAN [Bean2] point to DIFFERENT OBJECTS !\n");
		}
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------