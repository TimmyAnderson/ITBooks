package my.example.DependsOnBeans;
//----------------------------------------------------------------------------------------------------------------------
import org.springframework.beans.factory.annotation.Autowired;

import org.springframework.beans.factory.support.DefaultListableBeanFactory;

import org.springframework.context.ConfigurableApplicationContext;

import org.springframework.stereotype.Component;
//----------------------------------------------------------------------------------------------------------------------
@Component
public class CDependsOnBeansBean3
{
//----------------------------------------------------------------------------------------------------------------------
	private boolean												containsDependentBean;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	@Autowired
	public CDependsOnBeansBean3(ConfigurableApplicationContext context)
	{
		DefaultListableBeanFactory								beanFactory=(DefaultListableBeanFactory) context.getAutowireCapableBeanFactory();
		
		// !!!!! Volanie METHOD zisti ci SPRING MANAGE BEAN uz bol vytvoreny, bez toho, aby automaticky vytvoril SPRING MANAGE BEAN, ak tato este nebola vytvorena. 
		containsDependentBean=beanFactory.containsSingleton("MyDependentBean3");
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	public String GetText()
	{
		String													response=String.format("From BEAN 3. DEPENDENT BEAN [%s].",containsDependentBean);
		
		return(response);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------