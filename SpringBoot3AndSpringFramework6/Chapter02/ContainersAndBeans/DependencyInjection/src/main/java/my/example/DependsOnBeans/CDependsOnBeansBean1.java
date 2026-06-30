package my.example.DependsOnBeans;
//----------------------------------------------------------------------------------------------------------------------
import org.springframework.beans.factory.annotation.Autowired;

import org.springframework.beans.factory.support.DefaultListableBeanFactory;

import org.springframework.context.ConfigurableApplicationContext;

import org.springframework.context.annotation.DependsOn;

import org.springframework.stereotype.Component;
//----------------------------------------------------------------------------------------------------------------------
@Component
// !!!!! EXPLICITNE sa vytvori DEPENDENCY na inom BEAN.
@DependsOn("MyDependentBean1")
public class CDependsOnBeansBean1
{
//----------------------------------------------------------------------------------------------------------------------
	private boolean												containsDependentBean;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	@Autowired
	public CDependsOnBeansBean1(ConfigurableApplicationContext context)
	{
		DefaultListableBeanFactory								beanFactory=(DefaultListableBeanFactory) context.getAutowireCapableBeanFactory();

		// !!!!! Volanie METHOD zisti ci SPRING MANAGE BEAN uz bol vytvoreny, bez toho, aby automaticky vytvoril SPRING MANAGE BEAN, ak tato este nebola vytvorena. 
		containsDependentBean=beanFactory.containsSingleton("MyDependentBean1");
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	public String GetText()
	{
		String													response=String.format("From BEAN 1. DEPENDENT BEAN [%s].",containsDependentBean);
		
		return(response);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------