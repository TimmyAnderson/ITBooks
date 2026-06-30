package my.example.ConditionalOnMissingBeanBeans;
//----------------------------------------------------------------------------------------------------------------------
import org.springframework.boot.autoconfigure.condition.ConditionalOnMissingBean;

import org.springframework.stereotype.Component;
//----------------------------------------------------------------------------------------------------------------------
@Component
// !!! Aplikuje sa CONDITION.
@ConditionalOnMissingBean(CConditionalOnMissingBeanBeansNotBean.class)
public class CConditionalOnMissingBeanBeansBean2
{
//----------------------------------------------------------------------------------------------------------------------
	public String GetText()
	{
		return("From BEAN 2.");
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------