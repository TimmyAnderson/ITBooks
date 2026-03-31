package my.example.Generics;
//----------------------------------------------------------------------------------------------------------------------
// !!! INTERFACE umoznuje ako TYPE PARAMETER CHECKED aj UNCHECKED EXCEPTIONS.
public interface IThrowsClauseAllExceptions<TException extends Throwable>
{
//----------------------------------------------------------------------------------------------------------------------
	// !!! JAVA umoznuje pouzitie TYPE PARAMETER v THROWS CLAUSE. 
	void ThrowException(boolean throwException) throws TException;
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------