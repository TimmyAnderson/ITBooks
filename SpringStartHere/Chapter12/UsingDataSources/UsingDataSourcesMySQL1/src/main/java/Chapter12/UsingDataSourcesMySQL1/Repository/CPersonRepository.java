package Chapter12.UsingDataSourcesMySQL1.Repository;
//----------------------------------------------------------------------------------------------------------------------
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.List;
import org.springframework.jdbc.core.JdbcTemplate;
import org.springframework.jdbc.core.RowMapper;
import org.springframework.stereotype.Repository;
//----------------------------------------------------------------------------------------------------------------------
// !!! CLASS reprezentuje REPOSITORY OBJECT, ktory vykonava pristup do DB.
// !!! REPOSITORY OBJECTS ak su SPRING BEANS OBJECT by mali byt oznacene pomocou ANNOTATION [@Repository].
@Repository
public class CPersonRepository
{
//----------------------------------------------------------------------------------------------------------------------
	// !!!!! SPRING dokaze automaticky namapovat CLASS [JdbcTemplate] na DATABASE, ktorej DRIVER bol vlozeny pomocou DEPENDENCY do PROJECT.
	private final JdbcTemplate									MDatabase;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	public CPersonRepository(JdbcTemplate Database)
	{
		MDatabase=Database;
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	private static CPerson MyObjectMapper(ResultSet Result, int Index) throws SQLException
	{
		// !!! Z CLASS [Result] sa nacitaju jednotlive COLUMNS.
		int														ID=Result.getInt("ID");
		String													FirstName=Result.getString("FirstName");
		String													LastName=Result.getString("LastName");
		int														Age=Result.getInt("Age");
		
		CPerson													Person=new CPerson(ID,FirstName,LastName,Age);

		return(Person);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	public List<CPerson> GetAllPersons()
	{
		 String													SQL="SELECT * FROM Persons";
		 
		 // !!! CLASS [RowMapper<T>] cita data z CLASS [ResultSet] a jednotlive RECORDS konvertuje na instancie TYPE 'T'.
		 // !!! Instanciu CLASS [RowMapper<T>] je mozne nahradit LAMBA EXPRESSION, alebo volanim METHOD.
		 RowMapper<CPerson>										RowMapper=CPersonRepository::MyObjectMapper;
		 
		 // !!! Vykona sa QUERY, ktora vracia instanciu CLASS [List<T>].
		 List<CPerson>											Records=MDatabase.query(SQL,RowMapper);
		 
		 return(Records);
	}
//----------------------------------------------------------------------------------------------------------------------
	public void AddPerson(CPerson Person)
	{
		// !!! SQL COMMAND OBSAHUJE PARAMETERS definovane pomocou CHARACTER [?].
		String													SQL="INSERT INTO Persons (FirstName,LastName,Age) VALUES (?,?,?)";

		// !!! Vykona sa SQL COMMAND nad DATABASE.
		// !!! PARAMETERS SQL COMMAND sa nahradia za VALUES.
		MDatabase.update(SQL,Person.getFirstName(),Person.getLastName(),Person.getAge());
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------