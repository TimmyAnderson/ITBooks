package Chapter12.UsingDataSourcesMultiDB;
//----------------------------------------------------------------------------------------------------------------------
import javax.sql.DataSource;
import org.springframework.beans.factory.annotation.Qualifier;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
import org.springframework.context.annotation.Primary;
import org.springframework.jdbc.core.JdbcTemplate;
import com.zaxxer.hikari.HikariDataSource;
//----------------------------------------------------------------------------------------------------------------------
// !!!!!! PROJECT vyzaduje, aby bola vytvorena DATABASE [chapter12multidatasource1] a v nej TABLE [Persons].
// !!!!!! PROJECT vyzaduje, aby bola vytvorena DATABASE [chapter12multidatasource2] a v nej TABLE [Persons].
@Configuration
public class CConfiguration
{
//----------------------------------------------------------------------------------------------------------------------
	// !!! ANNOTATION [@Value] umoznuje nastavit FIELD na lubovolnu VALUE.
	// !!!!! SYNTAX [${PROPERTY_NAME}] cita PROPERTY z FILE [application.properties].
	@Value("${My.Datasource1.Url}")
	private String												MDatabase1URL;
	@Value("${My.Datasource1.UserName}")
	private String												MDatabase1UserName;
	@Value("${My.Datasource1.Password}")
	private String												MDatabase1Password;
//----------------------------------------------------------------------------------------------------------------------
	@Value("${My.Datasource2.Url}")
	private String												MDatabase2URL;
	@Value("${My.Datasource2.UserName}")
	private String												MDatabase2UserName;
	@Value("${My.Datasource2.Password}")
	private String												MDatabase2Password;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	// !!!!! Pomocou ANNOTATION [@Qualifier] sa priradi danemu SPRING BEAN NAME.
	@Bean
	@Qualifier("DataSource1")
	public DataSource CreateCustomDataSource1()
	{
		// !!! Vytvori sa CUSTOM DATA SOURCE.
		HikariDataSource										Source=new HikariDataSource();

		// !!! CUSTOM DATA SOURCE sa nakonfiguruje.
		Source.setJdbcUrl(MDatabase1URL);
		Source.setUsername(MDatabase1UserName);
		Source.setPassword(MDatabase1Password);
		
		return(Source);
	}
//----------------------------------------------------------------------------------------------------------------------
	// !!!!! Pomocou ANNOTATION [@Qualifier] sa priradi danemu SPRING BEAN NAME.
	@Bean
	@Qualifier("DataSource2")
	public DataSource CreateCustomDataSource2()
	{
		// !!! Vytvori sa CUSTOM DATA SOURCE.
		HikariDataSource										Source=new HikariDataSource();

		// !!! CUSTOM DATA SOURCE sa nakonfiguruje.
		Source.setJdbcUrl(MDatabase2URL);
		Source.setUsername(MDatabase2UserName);
		Source.setPassword(MDatabase2Password);
		
		return(Source);
	}
//----------------------------------------------------------------------------------------------------------------------
	// !!!!! Pomocou ANNOTATION [@Qualifier] sa priradi danemu SPRING BEAN NAME.
	// !!!!! Kvoli spustenie UNIT TESTS MUSI byt jeden SPRING BEAN TYPE [JdbcTemplate] nastaveny ako PRIMARY pomocou ANNOTATION [@Primary].
	@Bean
	@Primary
	@Qualifier("JdbcTemplate1")
	// !!!!! Pomocou ANNOTATION [@Qualifier] sa definuje, ktory SPRING BEAN TYPE [JdbcTemplate] sa ma pouzit.
	public JdbcTemplate CreateCustomJdbcTemplate1(@Qualifier("DataSource1") DataSource Source)
	{
		// !!! Vytvori sa CUSTOM JDBC TEMPLATE s nastavenou instanciou TYPE [DataSource].
		JdbcTemplate											Template=new JdbcTemplate(Source);
	
		return(Template);
	}
//----------------------------------------------------------------------------------------------------------------------
	// !!!!! Pomocou ANNOTATION [@Qualifier] sa priradi danemu SPRING BEAN NAME.
	@Bean
	@Qualifier("JdbcTemplate2")
	// !!!!! Pomocou ANNOTATION [@Qualifier] sa definuje, ktory SPRING BEAN TYPE [JdbcTemplate] sa ma pouzit.
	public JdbcTemplate CreateCustomJdbcTemplate2(@Qualifier("DataSource2") DataSource Source)
	{
		// !!! Vytvori sa CUSTOM JDBC TEMPLATE s nastavenou instanciou TYPE [DataSource].
		JdbcTemplate											Template=new JdbcTemplate(Source);
	
		return(Template);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------