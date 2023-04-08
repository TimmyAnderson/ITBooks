package Chapter10.ImplementingRESTServices.ExceptionHandling;
//----------------------------------------------------------------------------------------------------------------------
import org.springframework.stereotype.Service;
//----------------------------------------------------------------------------------------------------------------------
// !!! CLASS emuluje cinnost nejakeho SERVICE, ktory moze hodit EXCEPTION.
@Service
public class CExceptionService
{
//----------------------------------------------------------------------------------------------------------------------
	public void DoSomething(boolean ThrowException)
	{
		if (ThrowException==true)
		{
			throw(new CMyException("Some EXCEPTION !!!"));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------