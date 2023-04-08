using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
//-------------------------------------------------------------------------------------------------------
// Tento SC je zadefinovany na klientovi.
//-------------------------------------------------------------------------------------------------------
namespace DCEquivalenceClient
{
//-------------------------------------------------------------------------------------------------------
	[ServiceContract]
	public interface IDCEquivalenceContract
	{
//-------------------------------------------------------------------------------------------------------
		[OperationContract]
		CClientPerson GetPerson();
		[OperationContract]
		// !!!!!!! Mento typu CClientPerson sa nezhoduje s menom na servri CServerPerson, ale TO NEVADI. Operacia sa vykona.
		// !!!!!!! Avsak meno lokalnej premmenej Person musi byt zhodne inak to vrati vynimku.
		void SendPerson(CClientPerson Person);
		// !!!!!!! Cize toto je chyba - lebo meno lokalnej premenej je ClientPerson a to je rozdielne na mene na serveri kde je Person. !!!!!!!
		//void SendPerson(CClientPerson ClientPerson);
//-------------------------------------------------------------------------------------------------------
		[OperationContract]
		CClientErrorPerson GetErrorPerson();
		[OperationContract]
		void SendErrorPerson(CClientErrorPerson Person);
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------