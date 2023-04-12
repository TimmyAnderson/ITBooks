package Chapter15.Testing.Repository;
//----------------------------------------------------------------------------------------------------------------------
import java.util.List;
import org.springframework.data.jdbc.repository.query.Modifying;
import org.springframework.data.jdbc.repository.query.Query;
import org.springframework.data.repository.CrudRepository;
//----------------------------------------------------------------------------------------------------------------------
public interface IAccountRepository extends CrudRepository<Account,Integer>
{
//----------------------------------------------------------------------------------------------------------------------
	@Query("SELECT * FROM Account")
	List<Account> findAccounts();
//----------------------------------------------------------------------------------------------------------------------
	@Modifying
	@Query("UPDATE Account SET Amount=:Amount WHERE ID=:ID")
	void ChangeAmount(int ID, int Amount);	
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------