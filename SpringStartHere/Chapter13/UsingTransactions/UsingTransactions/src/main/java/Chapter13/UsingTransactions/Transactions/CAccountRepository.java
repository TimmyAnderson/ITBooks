package Chapter13.UsingTransactions.Transactions;
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
public class CAccountRepository
{
//----------------------------------------------------------------------------------------------------------------------
	// !!!!! SPRING dokaze automaticky namapovat CLASS [JdbcTemplate] na DATABASE, ktorej DRIVER bol vlozeny pomocou DEPENDENCY do PROJECT.
	private final JdbcTemplate									MDatabase;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	public CAccountRepository(JdbcTemplate Database)
	{
		MDatabase=Database;
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	private static CAccount MyObjectMapper(ResultSet Result, int Index) throws SQLException
	{
		// !!! Z CLASS [Result] sa nacitaju jednotlive COLUMNS.
		int														ID=Result.getInt("ID");
		String													Name=Result.getString("Name");
		int														Amount=Result.getInt("Amount");
		
		CAccount												Account=new CAccount(ID,Name,Amount);

		return(Account);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	public List<CAccount> GetAllAccounts()
	{
		 String													SQL="SELECT * FROM Accounts";
		 
		 RowMapper<CAccount>									RowMapper=CAccountRepository::MyObjectMapper;
		 
		 // !!! Vykona sa QUERY, ktora vracia instanciu CLASS [List<T>].
		 List<CAccount>											Records=MDatabase.query(SQL,RowMapper);
		 
		 return(Records);
	}
//----------------------------------------------------------------------------------------------------------------------
	public CAccount GetAccount(int ID)
	{
		 String													SQL="SELECT * FROM Accounts WHERE ID=?";
		 
		 RowMapper<CAccount>									RowMapper=CAccountRepository::MyObjectMapper;
		 
		 // !!! Vykona sa QUERY, ktora vracia instanciu CLASS [T].
		 CAccount												Record=MDatabase.queryForObject(SQL,RowMapper,ID);
		 
		 return(Record);
	}
//----------------------------------------------------------------------------------------------------------------------
	public void ChangeAmount(int ID, int Amount)
	{
		String													SQL="UPDATE Accounts SET Amount=? WHERE ID=?";
	
    	MDatabase.update(SQL,Amount,ID);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------