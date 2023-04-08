// dllmain.h : Declaration of module class.

class CMyCOMModule : public ATL::CAtlDllModuleT< CMyCOMModule >
{
public :
	DECLARE_LIBID(LIBID_MyCOMLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_MYCOM, "{1BD1B3D2-897B-4154-AF99-718D7FA0ED9C}")
};

extern class CMyCOMModule _AtlModule;
