package my.example.ConditionalBeans;
//----------------------------------------------------------------------------------------------------------------------
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Conditional;
import org.springframework.context.annotation.Configuration;
//----------------------------------------------------------------------------------------------------------------------
@Configuration
public class CConditionalBeansFactory
{
//----------------------------------------------------------------------------------------------------------------------
	@Bean
	// !!! Aplikuje sa CONDITION.
	@Conditional(CConditionalBeansConditionTrue.class)
	public CConditionalBeansBean3 MyBean3()
	{
		CConditionalBeansBean3									bean=new CConditionalBeansBean3();
		
		return(bean);
	}
//----------------------------------------------------------------------------------------------------------------------
	@Bean
	// !!! Aplikuje sa CONDITION.
	@Conditional(CConditionalBeansConditionFalse.class)
	public CConditionalBeansBean4 MyBean4()
	{
		CConditionalBeansBean4									bean=new CConditionalBeansBean4();
		
		return(bean);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------