package Chapter09.UsingSpringWebScopes.Scopes;
//----------------------------------------------------------------------------------------------------------------------
import org.springframework.stereotype.Component;
import org.springframework.web.context.annotation.SessionScope;
import Chapter09.UsingSpringWebScopes.Helpers.CHelpers;
import jakarta.annotation.PostConstruct;
import jakarta.annotation.PreDestroy;
//----------------------------------------------------------------------------------------------------------------------
// !!! CLASS sa oznaci ako SPRING BEAN OBJECT.
@Component
// !!! SPRING BEAN OBJECT ma nastaveny SESSION SCOPE.
@SessionScope
public class CScopeSessionBean
{
//----------------------------------------------------------------------------------------------------------------------
	public CScopeSessionBean()
	{
		System.out.format("TIME [%s] - CONSTRUCTOR CScopeSessionBean() CALLED !\n",CHelpers.GetTime());
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	@PostConstruct
	public void InitializeBean()
	{
		System.out.format("TIME [%s] - METHOD CScopeSessionBean.InitializeBean() CALLED !\n",CHelpers.GetTime());
	}
//----------------------------------------------------------------------------------------------------------------------
	@PreDestroy
	public void DestroyBean()
	{ 	
		System.out.format("TIME [%s] - METHOD CScopeSessionBean.DestroyBean() CALLED !\n",CHelpers.GetTime());
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	public void DoSomething1()
	{
		System.out.format("TIME [%s] - METHOD CScopeSessionBean.DoSomething1() CALLED !\n",CHelpers.GetTime());
	}
//----------------------------------------------------------------------------------------------------------------------
	public void DoSomething2()
	{
		System.out.format("TIME [%s] - METHOD CScopeSessionBean.DoSomething2() CALLED !\n",CHelpers.GetTime());
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------