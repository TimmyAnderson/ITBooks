package my.example.ConditionalOnExpressionBeans;
//----------------------------------------------------------------------------------------------------------------------
import org.springframework.boot.autoconfigure.condition.ConditionalOnExpression;

import org.springframework.stereotype.Component;
//----------------------------------------------------------------------------------------------------------------------
@Component
// !!! Aplikuje sa CONDITION.
@ConditionalOnExpression("1==2")
public class CConditionalOnExpressionBeansBean2
{
//----------------------------------------------------------------------------------------------------------------------
	public String GetText()
	{
		return("From BEAN 2.");
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------