package Chapter12.UsingDataSourcesMySQL2;
//----------------------------------------------------------------------------------------------------------------------
import javax.sql.DataSource;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
import com.zaxxer.hikari.HikariDataSource;
//----------------------------------------------------------------------------------------------------------------------
@Configuration
public class CConfiguration
{
//----------------------------------------------------------------------------------------------------------------------
	// !!! ANNOTATION [@Value] umoznuje nastavit FIELD na lubovolnu VALUE.
	// !!!!! SYNTAX [${PROPERTY_NAME}] cita PROPERTY z FILE [application.properties].
	@Value("${My.Datasource.Url}")
	private String												MDatabaseURL;
	@Value("${My.Datasource.UserName}")
	private String												MDatabaseUserName;
	@Value("${My.Datasource.Password}")
	private String												MDatabasePassword;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	@Bean
	public DataSource CreateCustomDataSource()
	{
		// !!! Vytvori sa CUSTOM DATA SOURCE.
		HikariDataSource										Source=new HikariDataSource();

		// !!! CUSTOM DATA SOURCE sa nakonfiguruje.
		Source.setJdbcUrl(MDatabaseURL);
		Source.setUsername(MDatabaseUserName);
		Source.setPassword(MDatabasePassword);
		
		return(Source);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------