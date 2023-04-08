package Chapter09.UsingSpringWebScopes;
//----------------------------------------------------------------------------------------------------------------------
import org.springframework.stereotype.Component;
import org.springframework.web.context.annotation.RequestScope;
import Chapter09.UsingSpringWebScopes.Helpers.CHelpers;
//----------------------------------------------------------------------------------------------------------------------
// !!!!! CLASS je SPRING BEAN.
@Component
// !!!!! SPRING BEAN ma REQUEST SCOPE.
@RequestScope
public class CRequestScopeLoginProcessor
{
//----------------------------------------------------------------------------------------------------------------------
	private final CSessionScopeLoggedUserManagementService		MLoggedUserManagementService;
	private final CApplicationScopeLoginCountService			MLoginCountService;
//----------------------------------------------------------------------------------------------------------------------
	private String												MUsername;
	private String												MPassword;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	public CRequestScopeLoginProcessor(CSessionScopeLoggedUserManagementService LoggedUserManagementService, CApplicationScopeLoginCountService LoginCountService)
	{
		System.out.format("TIME [%s] - CRequestScopeLoginProcessor OBJECT CREATED.\n",CHelpers.GetTime());
		
		MLoggedUserManagementService=LoggedUserManagementService;
		MLoginCountService=LoginCountService;
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	public String getUsername()
	{
		return(MUsername);
	}
//----------------------------------------------------------------------------------------------------------------------
	public void setUsername(String Username)
	{
		MUsername=Username;
	}
//----------------------------------------------------------------------------------------------------------------------
	public String getPassword()
	{
		return(MPassword);
	}
//----------------------------------------------------------------------------------------------------------------------
	public void setPassword(String Password)
	{
		MPassword=Password;
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	public boolean Login()
	{
		if (MUsername.equals("Timmy")==true && MPassword.equals("xxx")==true)
		{
			MLoginCountService.Increment();
		
			// !!!!! Do SERVICE, ktory ma SESSION SERVICE sa ulozi USERNAME.
			MLoggedUserManagementService.setUsername(MUsername);
		
			return(true);
		}
		else
		{
			return(false);
		}
	}	
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------