package my.example.Generics;
//----------------------------------------------------------------------------------------------------------------------
public final class CNonGenericsClassGenericsMethods
{
//----------------------------------------------------------------------------------------------------------------------
	private final String										classValue;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	// !!! NON-GENERICS CONSTRUCTOR.
	public CNonGenericsClassGenericsMethods(String classValue)
	{
		this.classValue=classValue;
		
		System.out.printf("NON-GENERICS CLASS - NON-GENERICS CONSTRUCTOR - CLASS VALUE [%s].\n",classValue);
	}
//----------------------------------------------------------------------------------------------------------------------
	// !!! GENERICS CONSTRUCTOR.
	public <TConstructorType> CNonGenericsClassGenericsMethods(String classValue, TConstructorType constructorValue)
	{
		this.classValue=classValue;
		
		System.out.printf("NON-GENERICS CLASS - GENERICS CONSTRUCTOR - CLASS VALUE [%s] CONSTRUCTOR VALUE [%s].\n",classValue,constructorValue);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	// !!! STATIC NON-GENERICS METHOD.
	public static void StaticNonGenericsMethod(String parameter)
	{
		System.out.printf("NON-GENERICS CLASS - STATIC NON-GENERICS METHOD - PARAMETER [%s].\n",parameter);
	}
//----------------------------------------------------------------------------------------------------------------------
	// !!! STATIC GENERICS METHOD.
	public static <TMethodType> void StaticGenericsMethod(TMethodType methodValue)
	{
		System.out.printf("NON-GENERICS CLASS - STATIC GENERICS METHOD - METHOD VALUE [%s].\n",methodValue);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	// !!! NON-STATIC NON-GENERICS METHOD.
	public String NonStaticNonGenericsMethod()
	{
		return(classValue);
	}
//----------------------------------------------------------------------------------------------------------------------
	// !!! NON-STATIC GENERICS METHOD.
	public <TMethodType> String NonStaticGenericsMethod(TMethodType methodValue)
	{
		System.out.printf("NON-GENERICS CLASS - NON-STATIC GENERICS METHOD - METHOD VALUE [%s].\n",methodValue);
		
		return(classValue);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	public String getClassValue()
	{
		return(classValue);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------