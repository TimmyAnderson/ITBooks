package my.example.BeanPostProcessors;
//----------------------------------------------------------------------------------------------------------------------
import org.springframework.beans.BeansException;
import org.springframework.beans.factory.config.BeanPostProcessor;
//----------------------------------------------------------------------------------------------------------------------
// !!! CLASS IMPLEMENTUJUCA INTERFACE [BeanPostProcessor] je oznacena ako BEAN pomocou FACTORY METHOD.
public class CBeanPostProcessorsPostProcessor2 implements BeanPostProcessor
{
//----------------------------------------------------------------------------------------------------------------------
	@Override
	public Object postProcessBeforeInitialization(Object bean, String beanName) throws BeansException
	{
		System.out.printf("!!!!! PROCESSOR 2 - BEFORE INITIALIZATION CALLED for BEAN [%s].\n",beanName);
		
		return(bean);
	}
//----------------------------------------------------------------------------------------------------------------------
	@Override
	public Object postProcessAfterInitialization(Object bean, String beanName) throws BeansException
	{
		System.out.printf("!!!!! PROCESSOR 2 - AFTER INITIALIZATION CALLED for BEAN [%s].\n",beanName);
		
		return(bean);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------