package my.example.Generics;
//----------------------------------------------------------------------------------------------------------------------
public final class CTypeErasureMethodOverloadingInGenericClass<TType>
{
//----------------------------------------------------------------------------------------------------------------------
	public void OverloadedMethod(TType value)
	{
		System.out.printf("GENERIC METHOD - VALUE [%s].\n",value);
	}
//----------------------------------------------------------------------------------------------------------------------
	public void OverloadedMethod(Long value)
	{
		System.out.printf("NON-GENERIC METHOD - LONG - VALUE [%s].\n",value);
	}
//----------------------------------------------------------------------------------------------------------------------
	public void OverloadedMethod(Integer value)
	{
		System.out.printf("NON-GENERIC METHOD - INTEGER - VALUE [%s].\n",value);
	}
//----------------------------------------------------------------------------------------------------------------------
	// !!! JAVA NEUMOZNUE vykonat METHOD OVERLOADING pre REPLACEMENT TYPES.
	/*
	public void OverloadedMethod(Object value)
	{
		System.out.printf("NON-GENERIC METHOD - OBJECT - VALUE [%s].\n",value);
	}
	*/
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------