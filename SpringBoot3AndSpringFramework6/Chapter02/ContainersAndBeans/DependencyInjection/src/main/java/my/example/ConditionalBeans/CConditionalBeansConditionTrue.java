package my.example.ConditionalBeans;
//----------------------------------------------------------------------------------------------------------------------
import org.springframework.context.annotation.Condition;
import org.springframework.context.annotation.ConditionContext;
import org.springframework.core.type.AnnotatedTypeMetadata;
//----------------------------------------------------------------------------------------------------------------------
// !!! CLASS implementuje CONDITION, ktora je stale TRUE.
public class CConditionalBeansConditionTrue implements Condition
{
//----------------------------------------------------------------------------------------------------------------------
	@Override
	public boolean matches(ConditionContext context, AnnotatedTypeMetadata metadata)
	{
		return(true);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------