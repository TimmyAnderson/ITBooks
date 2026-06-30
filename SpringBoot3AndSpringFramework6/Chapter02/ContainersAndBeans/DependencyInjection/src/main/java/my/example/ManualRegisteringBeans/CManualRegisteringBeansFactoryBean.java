package my.example.ManualRegisteringBeans;
//----------------------------------------------------------------------------------------------------------------------
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.config.BeanDefinition;
import org.springframework.beans.factory.support.BeanDefinitionBuilder;
import org.springframework.beans.factory.support.DefaultListableBeanFactory;

import org.springframework.stereotype.Component;
//----------------------------------------------------------------------------------------------------------------------
// !!! BEAN je FACTORY BEAN, ktory MANUALNE registruje BEAN [CManualRegisteringBeansBean].
@Component
public class CManualRegisteringBeansFactoryBean
{
//----------------------------------------------------------------------------------------------------------------------
	@Autowired
	public CManualRegisteringBeansFactoryBean(DefaultListableBeanFactory beanFactory)
	{
		BeanDefinitionBuilder									beanDefinitionBuilder=BeanDefinitionBuilder.genericBeanDefinition(CManualRegisteringBeansBean.class);
		
		beanDefinitionBuilder.addPropertyValue("value1","Timmy");
		beanDefinitionBuilder.addPropertyValue("value2",12);
		
		BeanDefinition											beanDefinition=beanDefinitionBuilder.getBeanDefinition();
		
		beanFactory.registerBeanDefinition("myBean",beanDefinition);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------