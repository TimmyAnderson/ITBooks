package Chapter14.UsingSpringData.Repository;
//----------------------------------------------------------------------------------------------------------------------
import java.util.List;
import org.springframework.data.jdbc.repository.query.Modifying;
import org.springframework.data.jdbc.repository.query.Query;
import org.springframework.data.repository.CrudRepository;
//----------------------------------------------------------------------------------------------------------------------
// !!!!! V SPRING DATA sa na pristup k DATABASE pouzivaju INTERFACES z ktorych SPRING DATA automaticky generuje CLASSES, ktore tieto INTERFACES implementuju. CLASSES su registrovane ako SPRING BEAN OBJECTS.
// !!!!! CUSTOM REPOSITORY INTERFACE implementuje STANDARD SPRING DATA INTERFACE [CrudRepository<T,ID>], ktory definuje CRUD OPERATIONS pre dany ENTITY TYPE 'T'.
// !!!!! TYPE PARAMETER 'ID' MUSI byt OBJECT ako napriklad TYPE [Integer], a NIE PRIMITIVE TYPE ako TYPE [int].
public interface IAccountRepository extends CrudRepository<Account,Integer>
{
//----------------------------------------------------------------------------------------------------------------------
	// !!!!! METHOD ma explicitne definovanu QUERY.
	@Query("SELECT * FROM Account")
	List<Account> findAccounts();
//----------------------------------------------------------------------------------------------------------------------
	// !!!!! Pre tuto METHOD je AUTOMATICKY generovany SQL COMMAND na zaklade jej NAME a PROTOTYPE.
	List<Account> findAccountsByName(String name);
//----------------------------------------------------------------------------------------------------------------------
	// !!!!! Ak SQL COMMAND vykonava INSERT, UPDATE, alebo DELETE, MUSI sa applikovat ANNOTATION [@Modifying].
	// !!!!! Ak SQL COMMAND ma PARAMETERS, tak ich NAMES MUSIA byt IDENTICKE ako NAMES METHOD PARAMETERS.
	@Modifying
	@Query("UPDATE Account SET Amount=:Amount WHERE ID=:ID")
	void ChangeAmount(long ID, int Amount);	
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------