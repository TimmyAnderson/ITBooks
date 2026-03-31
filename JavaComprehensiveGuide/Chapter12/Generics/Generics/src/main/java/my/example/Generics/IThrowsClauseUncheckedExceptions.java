package my.example.Generics;
//----------------------------------------------------------------------------------------------------------------------
// !!! INTERFACE umoznuje ako TYPE PARAMETER iba UNCHECKED EXCEPTIONS.
public interface IThrowsClauseUncheckedExceptions<TException extends RuntimeException>
{
//----------------------------------------------------------------------------------------------------------------------
	// !!! JAVA umoznuje pouzitie TYPE PARAMETER v THROWS CLAUSE. 
	void ThrowException(boolean throwException) throws TException;
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------