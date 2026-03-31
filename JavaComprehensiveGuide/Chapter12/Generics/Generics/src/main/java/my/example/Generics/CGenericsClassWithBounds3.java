package my.example.Generics;
//----------------------------------------------------------------------------------------------------------------------
// !!!!! BOUNDS implementuju RECURSIVE TYPE BOUNDS, ked TYPE PARAMETER je pouzity v CONDITION daneho BOUND.
public final class CGenericsClassWithBounds3<TParameter1 extends CBoundsClassBase2<TParameter1>, TParameter2 extends IBoundsInterface1<TParameter2>, TParameter3 extends IBoundsInterface2<TParameter3>>
{
//----------------------------------------------------------------------------------------------------------------------
	private final TParameter1									value1;
	private final TParameter2									value2;
	private final TParameter3									value3;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	public CGenericsClassWithBounds3(TParameter1 value1, TParameter2 value2, TParameter3 value3)
	{
		this.value1=value1;
		this.value2=value2;
		this.value3=value3;
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	public void Print()
	{
		// !!! Pouzitie BOUND umoznuje pouzitie METHODS BOUND TYPE.
		String													innerValue1=value1.Print(value1);
		
		// !!! Pouzitie BOUND umoznuje pouzitie METHODS BOUND TYPE.
		TParameter2												innerValue2=value2.getValueInterface1();
		
		// !!! Pouzitie BOUND umoznuje pouzitie METHODS BOUND TYPE.
		TParameter3												innerValue3=value3.getValueInterface2();
		
		System.out.printf("BOUNDS - VALUE 1 [%s] VALUE 2 [%s] VALUE 3 [%s].\n",innerValue1,innerValue2,innerValue3);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	public TParameter1 getValue1()
	{
		return(value1);
	}
//----------------------------------------------------------------------------------------------------------------------
	public TParameter2 getValue2()
	{
		return(value2);
	}
//----------------------------------------------------------------------------------------------------------------------
	public TParameter3 getValue3()
	{
		return(value3);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------