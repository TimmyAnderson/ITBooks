//-------------------------------------------------------------------------------------------------------
#include "CErrorThisParentShared.h"
#include "CErrorThisChildShared.h"
//-------------------------------------------------------------------------------------------------------
using namespace std;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
// !!!!! Vo FUNCTION TestErrorThisShared() INICIALIZACIA THIS POINTER sposobi MEMORY ACCESS ERROR. Dovodom je nasledujuci.
// 1. CODE [std::shared_ptr<CErrorThisParentShared>(this)] vytvori instanciu CLASS [shared_ptr<CErrorThisParentShared>], ktorej REFERENCE COUNTER bude nastaveny na 1.
// 2. V CONSTRUCTOR CLASS [CErrorThisChildShared] po priradeni hodnoty 'std::shared_ptr<CErrorThisParentShared>(this)' do FIELD 'MParent' dojde k inkrementacii REFERENCE COUNTER na 2.
// 3. Po skonceni CONSTRUCTOR CLASS [CErrorThisChildShared] sa uvolni hodnota 'std::shared_ptr<CErrorThisParentShared>(this)' a hodnota REFERENCE COUNTER klesne na 1.
// !!! 4. Na konci SCOPE vo FUNCTION TestErrorThisShared() sa zavola DESTRUCTOR CLASS [CErrorThisParentShared] pretoze instancia CLASS [shared_ptr<CErrorThisParentShared>] obsahovala NEZAVISLU hodnotu REFERENCE COUNTER a ten klesol pri opusteni SCOPE na 0.
// 5. DESCTRUCTOR CLASS [CErrorThisParentShared] zavola DESTRUCTOR FIELD 'MChild', ktory znizi hodnotu REFERENCE COUNTER na 0 a tym padom zavola DESTRUCTOR OBJECT [CErrorThisChildShared].
// !!! 6. DESCTRUCTOR CLASS [CErrorThisChildShared] zavola DESTRUCTOR FIELD 'MChild', ktory znizi hodnotu REFERENCE COUNTER na 0 a tym padom zavola DESTRUCTOR OBJECT [CErrorThisChildParent].
// !!!!! 7. Teraz dojde k MEMORY ACCESS EXCEPTION, pretoze pre TEN ISTY OBJECT [CErrorThisChildParent] sa DESTRUCTOR vola 2. KRAT.
CErrorThisParentShared::CErrorThisParentShared(void)
	: MChild(new CErrorThisChildShared(std::shared_ptr<CErrorThisParentShared>(this)))
{
	wcout << L"METHOD CErrorThisParentShared::CErrorThisParentShared() CALLED ! REFERENCE COUNTER [" << MChild.use_count() << L"] !" << endl;
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void CErrorThisParentShared::CallChild(void)
{
	MChild->SomeMethod();
}
//-------------------------------------------------------------------------------------------------------