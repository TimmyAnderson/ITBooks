package my.example.ConditionalOnExpressionBeans;
//----------------------------------------------------------------------------------------------------------------------
//import org.springframework.boot.autoconfigure.condition.ConditionalOnExpression;

//import org.springframework.stereotype.Component;
//----------------------------------------------------------------------------------------------------------------------
//@Component
// !!! Aplikuje sa CONDITION.
// !!! Testuje sa EXISTENCIA BEAN.
// !!!!! Nefunguje to, lebo SPRING EXPRESSION LANGUAGE EXPRESSION je EVAULATED SKOR ako su vytvorene instancie BEANS.
// !!!!! Podla AI tento CODE ani NEMOZE fungovat a jeho pouzitie je ANTIPATTERN, ktory fungovat NEBUDE.
//@ConditionalOnExpression("@CConditionalOnExpressionBeansNotBean!=null")
public class CConditionalOnExpressionBeansBean6
{
//----------------------------------------------------------------------------------------------------------------------
	public String GetText()
	{
		return("From BEAN 6.");
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------