package my.example.ConditionalOnMissingBeanBeans;
//----------------------------------------------------------------------------------------------------------------------
import org.springframework.boot.autoconfigure.condition.ConditionalOnMissingBean;

import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
//----------------------------------------------------------------------------------------------------------------------
@Configuration
public class CConditionalOnMissingBeanBeansFactory
{
//----------------------------------------------------------------------------------------------------------------------
	@Bean
	// !!! Aplikuje sa CONDITION.
	@ConditionalOnMissingBean(CConditionalOnMissingBeanBeansBean.class)
	public CConditionalOnMissingBeanBeansBean3 MyBean3()
	{
		CConditionalOnMissingBeanBeansBean3						bean=new CConditionalOnMissingBeanBeansBean3();
		
		return(bean);
	}
//----------------------------------------------------------------------------------------------------------------------
	@Bean
	// !!! Aplikuje sa CONDITION.
	@ConditionalOnMissingBean(CConditionalOnMissingBeanBeansNotBean.class)
	public CConditionalOnMissingBeanBeansBean4 MyBean4()
	{
		CConditionalOnMissingBeanBeansBean4						bean=new CConditionalOnMissingBeanBeansBean4();
		
		return(bean);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------