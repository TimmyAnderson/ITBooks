package my.example.Generics;
//----------------------------------------------------------------------------------------------------------------------
public final class CThrowsClauseAllExceptionsChecked implements IThrowsClauseAllExceptions<Exception>
{
//----------------------------------------------------------------------------------------------------------------------
	public void ThrowException(boolean throwException) throws Exception
	{
		if (throwException==true)
		{
			System.out.println("EXCEPTION will be THROWN.");
			
			throw(new Exception("Some ERROR."));
		}
		else
		{
			System.out.println("EXCEPTION will not be THROWN.");
		}
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------