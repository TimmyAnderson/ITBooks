package my.example.ConditionalBeans;
//----------------------------------------------------------------------------------------------------------------------
import org.springframework.context.annotation.Condition;
import org.springframework.context.annotation.ConditionContext;
import org.springframework.core.type.AnnotatedTypeMetadata;
//----------------------------------------------------------------------------------------------------------------------
// !!! CLASS implementuje CONDITION, ktora je stale FALSE.
public class CConditionalBeansConditionFalse implements Condition
{
//----------------------------------------------------------------------------------------------------------------------
	@Override
	public boolean matches(ConditionContext context, AnnotatedTypeMetadata metadata)
	{
		return(false);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------