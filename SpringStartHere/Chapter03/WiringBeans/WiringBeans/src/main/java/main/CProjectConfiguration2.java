//----------------------------------------------------------------------------------------------------------------------
package main;
//----------------------------------------------------------------------------------------------------------------------
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
//----------------------------------------------------------------------------------------------------------------------
@Configuration
public class CProjectConfiguration2
{
//----------------------------------------------------------------------------------------------------------------------
	@Bean
	public CWiredBeanParent CreateWiredBeanParent()	
	{
		System.out.println("CreateWiredBeanParent() CALLED !");
		
		CWiredBeanParent										Bean=new CWiredBeanParent();
		
		Bean.setValue("Hello WIRED PARENT !!!");

		// !!!!! Ziska sa instancie BEAN 'CWiredBeanChild'.
		// !!!!! Ak BEAN 'CWiredBeanChild', tak sa METHOD [CWiredBeanChild CreateWiredBeanChild()] VOBEC NEVOLA a SPRING FRAMEWORK vrati existujuci BEAN.
		CWiredBeanChild											BeanChild=CreateWiredBeanChild();

		// !!! Vykona sa WIRING PARENT a CHILD BEAN.
		Bean.setChild(BeanChild);
		
		return(Bean);
	}
//----------------------------------------------------------------------------------------------------------------------
	@Bean
	public CWiredBeanChild CreateWiredBeanChild()
	{
		System.out.println("CreateWiredBeanChild() CALLED !");
	
		CWiredBeanChild											Bean=new CWiredBeanChild();
		
		Bean.setValue("Hello WIRED CHILD !!!");
		
		return(Bean);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------