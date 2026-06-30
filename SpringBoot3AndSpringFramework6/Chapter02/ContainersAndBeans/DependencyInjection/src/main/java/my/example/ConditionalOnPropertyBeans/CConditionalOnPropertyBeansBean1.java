package my.example.ConditionalOnPropertyBeans;
//----------------------------------------------------------------------------------------------------------------------
import org.springframework.boot.autoconfigure.condition.ConditionalOnProperty;

import org.springframework.stereotype.Component;
//----------------------------------------------------------------------------------------------------------------------
@Component
// !!! Aplikuje sa CONDITION.
@ConditionalOnProperty(name="MyProperty",havingValue="AAA")
public class CConditionalOnPropertyBeansBean1
{
//----------------------------------------------------------------------------------------------------------------------
	public String GetText()
	{
		return("From BEAN 1.");
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------