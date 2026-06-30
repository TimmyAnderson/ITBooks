package my.example.DependsOnBeans;
//----------------------------------------------------------------------------------------------------------------------
import org.springframework.beans.factory.annotation.Autowired;

import org.springframework.beans.factory.support.DefaultListableBeanFactory;

import org.springframework.context.ConfigurableApplicationContext;
//----------------------------------------------------------------------------------------------------------------------
public class CDependsOnBeansBean4
{
//----------------------------------------------------------------------------------------------------------------------
	private boolean												containsDependentBean;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	@Autowired
	public CDependsOnBeansBean4(ConfigurableApplicationContext context)
	{
		DefaultListableBeanFactory								beanFactory=(DefaultListableBeanFactory) context.getAutowireCapableBeanFactory();
		
		// !!!!! Volanie METHOD zisti ci SPRING MANAGE BEAN uz bol vytvoreny, bez toho, aby automaticky vytvoril SPRING MANAGE BEAN, ak tato este nebola vytvorena. 
		containsDependentBean=beanFactory.containsSingleton("MyDependentBean4");
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	public String GetText()
	{
		String													response=String.format("From BEAN 4. DEPENDENT BEAN [%s].",containsDependentBean);
		
		return(response);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------