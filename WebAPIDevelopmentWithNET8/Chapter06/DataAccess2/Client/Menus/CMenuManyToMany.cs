using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Text;
using System.Threading.Tasks;
using DataAccess2Web;
using MySharedLibrary;
//--------------------------------------------------------------------------------------------------------------------------------
namespace Client
{
//--------------------------------------------------------------------------------------------------------------------------------
	public sealed class CMenuManyToMany : CMenu
	{
//--------------------------------------------------------------------------------------------------------------------------------
		private const string									BASE_ADDRESS="https://localhost:7000/";
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		public CMenuManyToMany()
			: base(new CMenuCommand("q","QUIT",new EMenuCommandParameterType[0],null))
		{
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandGetEntities(string CommandID, object[] Parameters)
		{
			string												MessageID=CommandID;
			EMyHttpClientHttpMethod								Method=EMyHttpClientHttpMethod.E_GET;
			string												URL=$"{BASE_ADDRESS}ManyToMany/GetEntities";
			CMyHttpClientHeaders								Headers=null;
			CMyHttpClientContent								Content=null;
			TimeSpan											Timeout=TimeSpan.FromHours(1);
			CMyHttpClientOperationRequest						Request=new CMyHttpClientOperationRequest(MessageID,Method,URL,Headers,Content,Timeout);

			CMyHttpClient.ExecuteMessage(Request);
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandGetEntityM(string CommandID, object[] Parameters)
		{
			int													ID=((int) Parameters[0]);

			string												MessageID=CommandID;
			EMyHttpClientHttpMethod								Method=EMyHttpClientHttpMethod.E_GET;
			string												URL=$"{BASE_ADDRESS}ManyToMany/GetEntityM?ID={ID}";
			CMyHttpClientHeaders								Headers=null;
			CMyHttpClientContent								Content=null;
			TimeSpan											Timeout=TimeSpan.FromHours(1);
			CMyHttpClientOperationRequest						Request=new CMyHttpClientOperationRequest(MessageID,Method,URL,Headers,Content,Timeout);

			CMyHttpClient.ExecuteMessage(Request);
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandGetEntityN(string CommandID, object[] Parameters)
		{
			int													ID=((int) Parameters[0]);

			string												MessageID=CommandID;
			EMyHttpClientHttpMethod								Method=EMyHttpClientHttpMethod.E_GET;
			string												URL=$"{BASE_ADDRESS}ManyToMany/GetEntityN?ID={ID}";
			CMyHttpClientHeaders								Headers=null;
			CMyHttpClientContent								Content=null;
			TimeSpan											Timeout=TimeSpan.FromHours(1);
			CMyHttpClientOperationRequest						Request=new CMyHttpClientOperationRequest(MessageID,Method,URL,Headers,Content,Timeout);

			CMyHttpClient.ExecuteMessage(Request);
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandGetEntityMN(string CommandID, object[] Parameters)
		{
			int													ID=((int) Parameters[0]);

			string												MessageID=CommandID;
			EMyHttpClientHttpMethod								Method=EMyHttpClientHttpMethod.E_GET;
			string												URL=$"{BASE_ADDRESS}ManyToMany/GetEntityMN?ID={ID}";
			CMyHttpClientHeaders								Headers=null;
			CMyHttpClientContent								Content=null;
			TimeSpan											Timeout=TimeSpan.FromHours(1);
			CMyHttpClientOperationRequest						Request=new CMyHttpClientOperationRequest(MessageID,Method,URL,Headers,Content,Timeout);

			CMyHttpClient.ExecuteMessage(Request);
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandInsertEntity(string CommandID, object[] Parameters)
		{
			string												EntityMValue=((string) Parameters[0]);
			string												EntityNValue=((string) Parameters[1]);
			string												EntityMNValue=((string) Parameters[2]);

			CEntityManyToManyM									EntityM=new CEntityManyToManyM(EntityMValue);
			CEntityManyToManyN									EntityN=new CEntityManyToManyN(EntityNValue);

			CEntityManyToManyMN									PrincipalMN=new CEntityManyToManyMN(EntityMNValue,EntityM,EntityN);

			string												MessageID=CommandID;
			EMyHttpClientHttpMethod								Method=EMyHttpClientHttpMethod.E_POST;
			string												URL=$"{BASE_ADDRESS}ManyToMany/InsertEntity";
			CMyHttpClientHeaders								Headers=null;
			CMyHttpClientContent								Content=CMyHttpClientContent.CreateContentJsonObject(PrincipalMN);
			TimeSpan											Timeout=TimeSpan.FromHours(1);
			CMyHttpClientOperationRequest						Request=new CMyHttpClientOperationRequest(MessageID,Method,URL,Headers,Content,Timeout);

			CMyHttpClient.ExecuteMessage(Request);
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandUpdateEntity(string CommandID, object[] Parameters)
		{
			int													EntityMNID=((int) Parameters[0]);
			string												EntityMValue=((string) Parameters[1]);
			string												EntityNValue=((string) Parameters[2]);
			string												EntityMNValue=((string) Parameters[3]);

			CEntityManyToManyMN									EntityMN;

			{
				string											MessageID=CommandID;
				EMyHttpClientHttpMethod							Method=EMyHttpClientHttpMethod.E_GET;
				string											URL=$"{BASE_ADDRESS}ManyToMany/GetEntityMN?ID={EntityMNID}";
				CMyHttpClientHeaders							Headers=null;
				CMyHttpClientContent							Content=null;
				TimeSpan										Timeout=TimeSpan.FromHours(1);
				CMyHttpClientOperationRequest					Request=new CMyHttpClientOperationRequest(MessageID,Method,URL,Headers,Content,Timeout);
				CMyHttpClientOperationResponse					Response=CMyHttpClient.ExecuteMessage(Request);

				if (Response.StatusCode==HttpStatusCode.OK)
				{
					EntityMN=Response.Content.ConvertToObject<CEntityManyToManyMN>();
				}
				else
				{
					Console.WriteLine($"ENTITY NOT FOUND for ID [{EntityMNID}].");
					return;
				}
			}

			CEntityManyToManyM									EntityM=EntityMN.EntityM;
			CEntityManyToManyN									EntityN=EntityMN.EntityN;

			EntityMN.EntityMNValue=EntityMNValue;

			if (EntityM!=null)
			{
				EntityM.EntityMValue=EntityMValue;
			}

			if (EntityN!=null)
			{
				EntityN.EntityNValue=EntityNValue;
			}

			{
				string											MessageID=CommandID;
				EMyHttpClientHttpMethod							Method=EMyHttpClientHttpMethod.E_PUT;
				string											URL=$"{BASE_ADDRESS}ManyToMany/UpdateEntity";
				CMyHttpClientHeaders							Headers=null;
				CMyHttpClientContent							Content=CMyHttpClientContent.CreateContentJsonObject(EntityMN);
				TimeSpan										Timeout=TimeSpan.FromHours(1);
				CMyHttpClientOperationRequest					Request=new CMyHttpClientOperationRequest(MessageID,Method,URL,Headers,Content,Timeout);

				CMyHttpClient.ExecuteMessage(Request);
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandDeleteEntityM(string CommandID, object[] Parameters)
		{
			int													ID=((int) Parameters[0]);

			string												MessageID=CommandID;
			EMyHttpClientHttpMethod								Method=EMyHttpClientHttpMethod.E_DELETE;
			string												URL=$"{BASE_ADDRESS}ManyToMany/DeleteEntityM?ID={ID}";
			CMyHttpClientHeaders								Headers=null;
			CMyHttpClientContent								Content=null;
			TimeSpan											Timeout=TimeSpan.FromHours(1);
			CMyHttpClientOperationRequest						Request=new CMyHttpClientOperationRequest(MessageID,Method,URL,Headers,Content,Timeout);

			CMyHttpClient.ExecuteMessage(Request);
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandDeleteEntityN(string CommandID, object[] Parameters)
		{
			int													ID=((int) Parameters[0]);

			string												MessageID=CommandID;
			EMyHttpClientHttpMethod								Method=EMyHttpClientHttpMethod.E_DELETE;
			string												URL=$"{BASE_ADDRESS}ManyToMany/DeleteEntityN?ID={ID}";
			CMyHttpClientHeaders								Headers=null;
			CMyHttpClientContent								Content=null;
			TimeSpan											Timeout=TimeSpan.FromHours(1);
			CMyHttpClientOperationRequest						Request=new CMyHttpClientOperationRequest(MessageID,Method,URL,Headers,Content,Timeout);

			CMyHttpClient.ExecuteMessage(Request);
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandDeleteEntityMN(string CommandID, object[] Parameters)
		{
			int													ID=((int) Parameters[0]);

			string												MessageID=CommandID;
			EMyHttpClientHttpMethod								Method=EMyHttpClientHttpMethod.E_DELETE;
			string												URL=$"{BASE_ADDRESS}ManyToMany/DeleteEntityMN?ID={ID}";
			CMyHttpClientHeaders								Headers=null;
			CMyHttpClientContent								Content=null;
			TimeSpan											Timeout=TimeSpan.FromHours(1);
			CMyHttpClientOperationRequest						Request=new CMyHttpClientOperationRequest(MessageID,Method,URL,Headers,Content,Timeout);

			CMyHttpClient.ExecuteMessage(Request);
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		protected override CMenuCommand[] GetCommands()
		{
			List<CMenuCommand>									CommandsCollection=new List<CMenuCommand>();

			CommandsCollection.Add(new CMenuCommand("1","GET ENTITIES",new EMenuCommandParameterType[0],ExecuteCommandGetEntities));
			CommandsCollection.Add(new CMenuCommand("2","GET ENTITY M",new EMenuCommandParameterType[]{EMenuCommandParameterType.E_INT},ExecuteCommandGetEntityM));
			CommandsCollection.Add(new CMenuCommand("3","GET ENTITY N",new EMenuCommandParameterType[]{EMenuCommandParameterType.E_INT},ExecuteCommandGetEntityN));
			CommandsCollection.Add(new CMenuCommand("4","GET ENTITY MN",new EMenuCommandParameterType[]{EMenuCommandParameterType.E_INT},ExecuteCommandGetEntityMN));
			CommandsCollection.Add(new CMenuCommand("5","INSERT ENTITY",new EMenuCommandParameterType[]{EMenuCommandParameterType.E_STRING,EMenuCommandParameterType.E_STRING,EMenuCommandParameterType.E_STRING},ExecuteCommandInsertEntity));
			CommandsCollection.Add(new CMenuCommand("6","UPDATE ENTITY",new EMenuCommandParameterType[]{EMenuCommandParameterType.E_INT,EMenuCommandParameterType.E_STRING,EMenuCommandParameterType.E_STRING,EMenuCommandParameterType.E_STRING},ExecuteCommandUpdateEntity));
			CommandsCollection.Add(new CMenuCommand("7","DELETE ENTITY M",new EMenuCommandParameterType[]{EMenuCommandParameterType.E_INT},ExecuteCommandDeleteEntityM));
			CommandsCollection.Add(new CMenuCommand("8","DELETE ENTITY N",new EMenuCommandParameterType[]{EMenuCommandParameterType.E_INT},ExecuteCommandDeleteEntityN));
			CommandsCollection.Add(new CMenuCommand("9","DELETE ENTITY MN",new EMenuCommandParameterType[]{EMenuCommandParameterType.E_INT},ExecuteCommandDeleteEntityMN));

			CMenuCommand[]										Commands=CommandsCollection.ToArray();

			return(Commands);
		}
//--------------------------------------------------------------------------------------------------------------------------------
	}
//--------------------------------------------------------------------------------------------------------------------------------
}
//--------------------------------------------------------------------------------------------------------------------------------