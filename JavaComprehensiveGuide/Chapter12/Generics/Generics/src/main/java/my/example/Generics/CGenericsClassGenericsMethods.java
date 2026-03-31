package my.example.Generics;
//----------------------------------------------------------------------------------------------------------------------
public final class CGenericsClassGenericsMethods<TClassType>
{
//----------------------------------------------------------------------------------------------------------------------
	private final TClassType									classValue;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	// !!! NON-GENERICS CONSTRUCTOR.
	public CGenericsClassGenericsMethods(TClassType classValue)
	{
		this.classValue=classValue;
		
		System.out.printf("GENERICS CLASS - NON-GENERICS CONSTRUCTOR - CLASS VALUE [%s].\n",classValue);
	}
//----------------------------------------------------------------------------------------------------------------------
	// !!! GENERICS CONSTRUCTOR.
	public <TConstructorType> CGenericsClassGenericsMethods(TClassType classValue, TConstructorType constructorValue)
	{
		this.classValue=classValue;
		
		System.out.printf("GENERICS CLASS - GENERICS CONSTRUCTOR - CLASS VALUE [%s] CONSTRUCTOR VALUE [%s].\n",classValue,constructorValue);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	// !!! STATIC NON-GENERICS METHOD.
	public static void StaticNonGenericsMethod(String parameter)
	{
		System.out.printf("GENERICS CLASS - STATIC NON-GENERICS METHOD - PARAMETER [%s].\n",parameter);
	}
//----------------------------------------------------------------------------------------------------------------------
	/*
	// !!! STATIC NON-GENERICS METHOD.
	// !!!!! JAVA NEUMOZNUJE v STATIC METHODS pouzit CLASS TYPE ARGUMENTS.
	public static void StaticNonGenericsMethodClassValue(TClassType classValue)
	{
		System.out.printf("GENERICS CLASS - STATIC NON-GENERICS METHOD - CLASS VALUE [%s].\n",classValue);
	}
	*/
//----------------------------------------------------------------------------------------------------------------------
	// !!! STATIC GENERICS METHOD.
	public static <TMethodType> void StaticGenericsMethod(TMethodType methodValue)
	{
		System.out.printf("GENERICS CLASS - STATIC GENERICS METHOD - METHOD VALUE [%s].\n",methodValue);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	// !!! NON-STATIC NON-GENERICS METHOD.
	public TClassType NonStaticNonGenericsMethod()
	{
		return(classValue);
	}
//----------------------------------------------------------------------------------------------------------------------
	// !!! NON-STATIC GENERICS METHOD.
	public <TMethodType> TClassType NonStaticGenericsMethod(TMethodType methodValue)
	{
		System.out.printf("GENERICS CLASS - NON-STATIC GENERICS METHOD - METHOD VALUE [%s].\n",methodValue);
		
		return(classValue);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	public TClassType getClassValue()
	{
		return(classValue);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------