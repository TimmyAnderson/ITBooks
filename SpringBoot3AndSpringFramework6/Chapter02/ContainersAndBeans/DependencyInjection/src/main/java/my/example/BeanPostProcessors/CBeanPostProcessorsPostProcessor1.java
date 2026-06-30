package my.example.BeanPostProcessors;
//----------------------------------------------------------------------------------------------------------------------
import org.springframework.beans.BeansException;
import org.springframework.beans.factory.config.BeanPostProcessor;

import org.springframework.stereotype.Component;
//----------------------------------------------------------------------------------------------------------------------
// !!! CLASS IMPLEMENTUJUCA INTERFACE [BeanPostProcessor] je oznacena ako BEAN pomocou ANNOTATION.
@Component
public class CBeanPostProcessorsPostProcessor1 implements BeanPostProcessor
{
//----------------------------------------------------------------------------------------------------------------------
	@Override
	public Object postProcessBeforeInitialization(Object bean, String beanName) throws BeansException
	{
		System.out.printf("!!!!! PROCESSOR 1 - BEFORE INITIALIZATION CALLED for BEAN [%s].\n",beanName);
		
		return(bean);
	}
//----------------------------------------------------------------------------------------------------------------------
	@Override
	public Object postProcessAfterInitialization(Object bean, String beanName) throws BeansException
	{
		System.out.printf("!!!!! PROCESSOR 1 - AFTER INITIALIZATION CALLED for BEAN [%s].\n",beanName);
		
		return(bean);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------