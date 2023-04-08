package Chapter09.UsingSpringWebScopes;
//----------------------------------------------------------------------------------------------------------------------
import org.springframework.stereotype.Service;
import org.springframework.web.context.annotation.SessionScope;
import Chapter09.UsingSpringWebScopes.Helpers.CHelpers;
import jakarta.annotation.PostConstruct;
import jakarta.annotation.PreDestroy;
//----------------------------------------------------------------------------------------------------------------------
// !!!!! CLASS je SPRING BEAN.
@Service
// !!!!! SPRING BEAN ma SESSION SCOPE.
@SessionScope
public class CSessionScopeLoggedUserManagementService
{
//----------------------------------------------------------------------------------------------------------------------
	// !!!!! SPRING BEAN OBJECT, ktory ma SESSION SCOPE NIE je TRHEAD SAFE.
	private Object												MLock=new Object();
	private String												MUsername;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	public CSessionScopeLoggedUserManagementService()
	{
		System.out.format("TIME [%s] - CSessionScopeLoggedUserManagementService OBJECT CREATED.\n",CHelpers.GetTime());
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	@PostConstruct
	public void InitializeBean()
	{
		System.out.format("TIME [%s] - METHOD CSessionScopeLoggedUserManagementService.InitializeBean() CALLED !\n",CHelpers.GetTime());
	}
//----------------------------------------------------------------------------------------------------------------------
	@PreDestroy
	public void DestroyBean()
	{ 	
		System.out.format("TIME [%s] - METHOD CSessionScopeLoggedUserManagementService.DestroyBean() CALLED !\n",CHelpers.GetTime());
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	public String getUsername()
	{
		synchronized(MLock)
		{
			return(MUsername);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	public void setUsername(String Username)
	{
		synchronized(MLock)
		{
			MUsername=Username;
		}
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------