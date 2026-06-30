package my.example.BeanPostProcessors;
//----------------------------------------------------------------------------------------------------------------------
import org.springframework.beans.BeansException;
import org.springframework.beans.factory.config.BeanPostProcessor;
//----------------------------------------------------------------------------------------------------------------------
// !!! CLASS IMPLEMENTUJUCA INTERFACE [BeanPostProcessor] je registrovana MANUALNE.
public class CBeanPostProcessorsPostProcessor4 implements BeanPostProcessor
{
//----------------------------------------------------------------------------------------------------------------------
	@Override
	public Object postProcessBeforeInitialization(Object bean, String beanName) throws BeansException
	{
		System.out.printf("!!!!! PROCESSOR 4 - BEFORE INITIALIZATION CALLED for BEAN [%s].\n",beanName);
		
		return(bean);
	}
//----------------------------------------------------------------------------------------------------------------------
	@Override
	public Object postProcessAfterInitialization(Object bean, String beanName) throws BeansException
	{
		System.out.printf("!!!!! PROCESSOR 4 - AFTER INITIALIZATION CALLED for BEAN [%s].\n",beanName);
		
		return(bean);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------