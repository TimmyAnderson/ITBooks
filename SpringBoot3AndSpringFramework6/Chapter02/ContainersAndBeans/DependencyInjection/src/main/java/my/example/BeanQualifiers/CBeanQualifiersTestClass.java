package my.example.BeanQualifiers;
//----------------------------------------------------------------------------------------------------------------------
import org.springframework.beans.factory.annotation.Qualifier;

import org.springframework.stereotype.Component;
//----------------------------------------------------------------------------------------------------------------------
@Component
public class CBeanQualifiersTestClass
{
//----------------------------------------------------------------------------------------------------------------------
	private final CBeanQualifiersClassQualifier1				beanQualifier1;
	private final CBeanQualifiersClassQualifier2				beanQualifier2;
	private final CBeanQualifiersClassMultiQualifier1			beanMultiQualifier1;
	private final CBeanQualifiersClassMultiQualifier2			beanMultiQualifier2;
	private final CBeanQualifiersClassSingleQualifier1			beanSingleQualifier1;
	private final CBeanQualifiersClassSingleQualifier2			beanSingleQualifier2;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	// !!!!! ANNOTATION [@IBeanQualifiersMultiAnnotation1] oznacuje, ktory BEAN sa ma pouzit.
	// !!!!! ANNOTATION [@IBeanQualifiersMultiAnnotation2] oznacuje, ktory BEAN sa ma pouzit.
	// !!!!! ANNOTATION [@IBeanQualifiersSingleAnnotation1] oznacuje, ktory BEAN sa ma pouzit na zaklade ENUM VALUE.
	public CBeanQualifiersTestClass(@Qualifier("ClassQualifier1") CBeanQualifiersClassQualifier1 beanQualifier1, @Qualifier("ClassQualifier2") CBeanQualifiersClassQualifier2 beanQualifier2, @IBeanQualifiersMultiAnnotation1 CBeanQualifiersClassMultiQualifier1 beanMultiQualifier1, @IBeanQualifiersMultiAnnotation2 CBeanQualifiersClassMultiQualifier2 beanMultiQualifier2, @IBeanQualifiersSingleAnnotation(IBeanQualifiersSingleAnnotation.EValue.VALUE_1) CBeanQualifiersClassSingleQualifier1 beanSingleQualifier1, @IBeanQualifiersSingleAnnotation(IBeanQualifiersSingleAnnotation.EValue.VALUE_2) CBeanQualifiersClassSingleQualifier2 beanSingleQualifier2)
	{
		this.beanQualifier1=beanQualifier1;
		this.beanQualifier2=beanQualifier2;
		this.beanMultiQualifier1=beanMultiQualifier1;
		this.beanMultiQualifier2=beanMultiQualifier2;
		this.beanSingleQualifier1=beanSingleQualifier1;
		this.beanSingleQualifier2=beanSingleQualifier2;
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	public void Test()
	{
		String													beanQualifierText1=beanQualifier1.GetStringValue();
		String													beanQualifierText2=beanQualifier2.GetStringValue();
		String													beanMultiQualifierText1=beanMultiQualifier1.GetStringValue();
		String													beanMultiQualifierText2=beanMultiQualifier2.GetStringValue();
		String													beanSingleQualifierText1=beanSingleQualifier1.GetStringValue();
		String													beanSingleQualifierText2=beanSingleQualifier2.GetStringValue();
		
		System.out.printf("BEAN QUALIFIER 1 - VALUE [%s].\n",beanQualifierText1);
		System.out.printf("BEAN QUALIFIER 2 - VALUE [%s].\n",beanQualifierText2);
		System.out.printf("BEAN MULTI QUALIFIER 1 - VALUE [%s].\n",beanMultiQualifierText1);
		System.out.printf("BEAN MULTI QUALIFIER 2 - VALUE [%s].\n",beanMultiQualifierText2);
		System.out.printf("BEAN SINGLE QUALIFIER 1 - VALUE [%s].\n",beanSingleQualifierText1);
		System.out.printf("BEAN SINGLE QUALIFIER 2 - VALUE [%s].\n",beanSingleQualifierText2);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------