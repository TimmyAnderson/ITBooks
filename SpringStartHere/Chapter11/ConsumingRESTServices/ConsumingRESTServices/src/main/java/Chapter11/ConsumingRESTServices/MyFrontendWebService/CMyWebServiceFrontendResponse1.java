package Chapter11.ConsumingRESTServices.MyFrontendWebService;
//----------------------------------------------------------------------------------------------------------------------
public class CMyWebServiceFrontendResponse1
{
//----------------------------------------------------------------------------------------------------------------------
	private String												MFrontendID;
	private String												MBackendID;
	private String												MValue1;
	private String												MValue2;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	public CMyWebServiceFrontendResponse1()
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	public CMyWebServiceFrontendResponse1(String FrontendID, String BackendID, String Value1, String Value2)
	{
		MFrontendID=FrontendID;
		MBackendID=BackendID;
		MValue1=Value1;
		MValue2=Value2;
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	public String getFrontendID()
	{
		return(MFrontendID);
	}
//----------------------------------------------------------------------------------------------------------------------
	public void setFrontendID(String FrontendID)
	{
		MFrontendID=FrontendID;
	}
//----------------------------------------------------------------------------------------------------------------------
	public String getBackendID()
	{
		return(MBackendID);
	}
//----------------------------------------------------------------------------------------------------------------------
	public void setBackendID(String BackendID)
	{
		MBackendID=BackendID;
	}
//----------------------------------------------------------------------------------------------------------------------
	public String getValue1()
	{
		return(MValue1);
	}
//----------------------------------------------------------------------------------------------------------------------
	public void setValue1(String Value1)
	{
		MValue1=Value1;
	}
//----------------------------------------------------------------------------------------------------------------------
	public String getValue2()
	{
		return(MValue2);
	}
//----------------------------------------------------------------------------------------------------------------------
	public void setValue2(String Value2)
	{
		MValue2=Value2;
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------