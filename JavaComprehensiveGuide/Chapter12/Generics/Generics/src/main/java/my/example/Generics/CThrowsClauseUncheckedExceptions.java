package my.example.Generics;
//----------------------------------------------------------------------------------------------------------------------
public final class CThrowsClauseUncheckedExceptions implements IThrowsClauseUncheckedExceptions<ArithmeticException>
{
//----------------------------------------------------------------------------------------------------------------------
	public void ThrowException(boolean throwException) throws ArithmeticException
	{
		if (throwException==true)
		{
			System.out.println("EXCEPTION will be THROWN.");
			
			throw(new ArithmeticException("Some ERROR."));
		}
		else
		{
			System.out.println("EXCEPTION will not be THROWN.");
		}
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------