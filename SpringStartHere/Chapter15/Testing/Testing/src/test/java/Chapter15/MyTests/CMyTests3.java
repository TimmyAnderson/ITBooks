package Chapter15.MyTests;
//----------------------------------------------------------------------------------------------------------------------
import static org.junit.jupiter.api.Assertions.assertEquals;
//----------------------------------------------------------------------------------------------------------------------
import org.junit.jupiter.api.DisplayName;
import org.junit.jupiter.api.Test;
import Chapter15.Testing.Repository.CAccountController;
//----------------------------------------------------------------------------------------------------------------------
public class CMyTests3
{
//----------------------------------------------------------------------------------------------------------------------
	@Test
	@DisplayName("This is MY TEST RETURN.")
	public void MyTestReturn()
	{
		CAccountController										Controller=new CAccountController(null);
		String													Result=Controller.ToUpper("Timmy Anderson");
		
		// !!!!! METHOD [void Assertions.assertEquals(Object Expected, Object Actual)] vykonava test ci su VALUES rovnake.
		assertEquals("TIMMY ANDERSON",Result);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------