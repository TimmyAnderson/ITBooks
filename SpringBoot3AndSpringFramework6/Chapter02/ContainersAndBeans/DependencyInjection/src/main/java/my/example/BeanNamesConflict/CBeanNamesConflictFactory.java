package my.example.BeanNamesConflict;
//----------------------------------------------------------------------------------------------------------------------
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
//----------------------------------------------------------------------------------------------------------------------
// !!! BEAN ma NAME [CBeanNamesConflictFactory].
@Configuration
public class CBeanNamesConflictFactory
{
//----------------------------------------------------------------------------------------------------------------------
	// !!! BEAN ma NAME [CBeanNamesConflictFactory].
	// !!!!! Dojde ku KONFLIKTU BEAN NAMES, takze PROGRAM sa NESPUSTI.
	@Bean
	public CBeanNamesConflictBean CBeanNamesConflictFactory()
	{
		CBeanNamesConflictBean									bean=new CBeanNamesConflictBean("111");
		
		return(bean);
	}
//----------------------------------------------------------------------------------------------------------------------
	// !!! BEAN ma NAME [MyBean].
	@Bean
	public CBeanNamesConflictBean MyBean()
	{
		CBeanNamesConflictBean									bean=new CBeanNamesConflictBean("222");
		
		return(bean);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------