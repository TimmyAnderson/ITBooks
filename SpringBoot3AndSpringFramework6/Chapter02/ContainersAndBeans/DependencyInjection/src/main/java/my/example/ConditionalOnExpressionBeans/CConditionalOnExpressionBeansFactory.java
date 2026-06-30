package my.example.ConditionalOnExpressionBeans;
//----------------------------------------------------------------------------------------------------------------------
import org.springframework.boot.autoconfigure.condition.ConditionalOnExpression;

import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
//----------------------------------------------------------------------------------------------------------------------
@Configuration
public class CConditionalOnExpressionBeansFactory
{
//----------------------------------------------------------------------------------------------------------------------
	@Bean
	// !!! Aplikuje sa CONDITION.
	@ConditionalOnExpression("1==1")
	public CConditionalOnExpressionBeansBean3 MyBean3()
	{
		CConditionalOnExpressionBeansBean3						bean=new CConditionalOnExpressionBeansBean3();
		
		return(bean);
	}
//----------------------------------------------------------------------------------------------------------------------
	@Bean
	// !!! Aplikuje sa CONDITION.
	@ConditionalOnExpression("1==2")
	public CConditionalOnExpressionBeansBean4 MyBean4()
	{
		CConditionalOnExpressionBeansBean4						bean=new CConditionalOnExpressionBeansBean4();
		
		return(bean);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------