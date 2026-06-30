package my.example.LifecycleEventsInterfaces;
import org.springframework.beans.BeansException;
//----------------------------------------------------------------------------------------------------------------------
import org.springframework.beans.factory.BeanClassLoaderAware;
import org.springframework.beans.factory.BeanFactory;
import org.springframework.beans.factory.BeanFactoryAware;
import org.springframework.beans.factory.BeanNameAware;

import org.springframework.context.ApplicationContext;
import org.springframework.context.ApplicationContextAware;
import org.springframework.context.EnvironmentAware;

import org.springframework.core.env.Environment;

import org.springframework.stereotype.Component;
//----------------------------------------------------------------------------------------------------------------------
@Component
public class CLifecycleEventsInterfacesAwareBean implements ApplicationContextAware, BeanNameAware, EnvironmentAware, BeanClassLoaderAware, BeanFactoryAware
{
//----------------------------------------------------------------------------------------------------------------------
	@Override
	public void setBeanFactory(BeanFactory beanFactory) throws BeansException
	{
		System.out.printf("!!!!! BEAN AWARE - SET BEAN FACTORY CALLED.\n");
	}
//----------------------------------------------------------------------------------------------------------------------
	@Override
	public void setBeanClassLoader(ClassLoader classLoader)
	{
		System.out.printf("!!!!! BEAN AWARE - SET BEAN CLASS LOADER CALLED.\n");
	}
//----------------------------------------------------------------------------------------------------------------------
	@Override
	public void setEnvironment(Environment environment)
	{
		System.out.printf("!!!!! BEAN AWARE - SET ENVIRONMENT CALLED.\n");
	}
//----------------------------------------------------------------------------------------------------------------------
	@Override
	public void setBeanName(String name)
	{
		System.out.printf("!!!!! BEAN AWARE - SET BEAN NAME CALLED. BEAN NAME [%s]\n",name);
	}
//----------------------------------------------------------------------------------------------------------------------
	@Override
	public void setApplicationContext(ApplicationContext applicationContext) throws BeansException
	{
		System.out.printf("!!!!! BEAN AWARE - SET APPLICATION CALLED.\n");
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	public String GetText()
	{
		return("From BEAN AWARE.");
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------