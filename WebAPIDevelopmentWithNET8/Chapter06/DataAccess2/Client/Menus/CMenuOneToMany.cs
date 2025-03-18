﻿using System;
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
	public sealed class CMenuOneToMany : CMenu
	{
//--------------------------------------------------------------------------------------------------------------------------------
		private const string									BASE_ADDRESS="https://localhost:7000/";
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		public CMenuOneToMany()
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
			string												URL=$"{BASE_ADDRESS}OneToMany/GetEntities";
			CMyHttpClientHeaders								Headers=null;
			CMyHttpClientContent								Content=null;
			TimeSpan											Timeout=TimeSpan.FromHours(1);
			CMyHttpClientOperationRequest						Request=new CMyHttpClientOperationRequest(MessageID,Method,URL,Headers,Content,Timeout);

			CMyHttpClient.ExecuteMessage(Request);
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandGetEntity(string CommandID, object[] Parameters)
		{
			int													ID=((int) Parameters[0]);

			string												MessageID=CommandID;
			EMyHttpClientHttpMethod								Method=EMyHttpClientHttpMethod.E_GET;
			string												URL=$"{BASE_ADDRESS}OneToMany/GetEntity?ID={ID}";
			CMyHttpClientHeaders								Headers=null;
			CMyHttpClientContent								Content=null;
			TimeSpan											Timeout=TimeSpan.FromHours(1);
			CMyHttpClientOperationRequest						Request=new CMyHttpClientOperationRequest(MessageID,Method,URL,Headers,Content,Timeout);

			CMyHttpClient.ExecuteMessage(Request);
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandInsertEntity(string CommandID, object[] Parameters)
		{
			string												EntityPrincipalValue=((string) Parameters[0]);
			string												EntityDependentValue1=((string) Parameters[1]);
			string												EntityDependentValue2=((string) Parameters[2]);

			CEntityOneToManyDependent							DependentEntity1=new CEntityOneToManyDependent(EntityDependentValue1);
			CEntityOneToManyDependent							DependentEntity2=new CEntityOneToManyDependent(EntityDependentValue2);

			CEntityOneToManyPrincipal							PrincipalEntity=new CEntityOneToManyPrincipal(EntityPrincipalValue,new CEntityOneToManyDependent[]{DependentEntity1,DependentEntity2});

			string												MessageID=CommandID;
			EMyHttpClientHttpMethod								Method=EMyHttpClientHttpMethod.E_POST;
			string												URL=$"{BASE_ADDRESS}OneToMany/InsertEntity";
			CMyHttpClientHeaders								Headers=null;
			CMyHttpClientContent								Content=CMyHttpClientContent.CreateContentJsonObject(PrincipalEntity);
			TimeSpan											Timeout=TimeSpan.FromHours(1);
			CMyHttpClientOperationRequest						Request=new CMyHttpClientOperationRequest(MessageID,Method,URL,Headers,Content,Timeout);

			CMyHttpClient.ExecuteMessage(Request);
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandUpdateEntity(string CommandID, object[] Parameters)
		{
			int													PrincipalID=((int) Parameters[0]);
			string												EntityPrincipalValue=((string) Parameters[1]);
			string												EntityDependentValue1=((string) Parameters[2]);
			string												EntityDependentValue2=((string) Parameters[3]);

			CEntityOneToManyPrincipal							EntityPrincipal;

			{
				string											MessageID=CommandID;
				EMyHttpClientHttpMethod							Method=EMyHttpClientHttpMethod.E_GET;
				string											URL=$"{BASE_ADDRESS}OneToMany/GetEntity?ID={PrincipalID}";
				CMyHttpClientHeaders							Headers=null;
				CMyHttpClientContent							Content=null;
				TimeSpan										Timeout=TimeSpan.FromHours(1);
				CMyHttpClientOperationRequest					Request=new CMyHttpClientOperationRequest(MessageID,Method,URL,Headers,Content,Timeout);
				CMyHttpClientOperationResponse					Response=CMyHttpClient.ExecuteMessage(Request);

				if (Response.StatusCode==HttpStatusCode.OK)
				{
					EntityPrincipal=Response.Content.ConvertToObject<CEntityOneToManyPrincipal>();
				}
				else
				{
					Console.WriteLine($"ENTITY NOT FOUND for ID [{PrincipalID}].");
					return;
				}
			}

			CEntityOneToManyDependent							EntityDependent1=EntityPrincipal.EntitiesDependent.OrderBy(P => P.EntityDependentID).FirstOrDefault();
			CEntityOneToManyDependent							EntityDependent2=EntityPrincipal.EntitiesDependent.OrderBy(P => P.EntityDependentID).Skip(1).FirstOrDefault();

			EntityPrincipal.EntityPrincipalValue=EntityPrincipalValue;

			if (EntityDependent1!=null)
			{
				EntityDependent1.EntityDependentValue=EntityDependentValue1;
			}

			if (EntityDependent2!=null)
			{
				EntityDependent2.EntityDependentValue=EntityDependentValue2;
			}

			{
				string											MessageID=CommandID;
				EMyHttpClientHttpMethod							Method=EMyHttpClientHttpMethod.E_PUT;
				string											URL=$"{BASE_ADDRESS}OneToMany/UpdateEntity";
				CMyHttpClientHeaders							Headers=null;
				CMyHttpClientContent							Content=CMyHttpClientContent.CreateContentJsonObject(EntityPrincipal);
				TimeSpan										Timeout=TimeSpan.FromHours(1);
				CMyHttpClientOperationRequest					Request=new CMyHttpClientOperationRequest(MessageID,Method,URL,Headers,Content,Timeout);

				CMyHttpClient.ExecuteMessage(Request);
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandDeleteEntity(string CommandID, object[] Parameters)
		{
			int													ID=((int) Parameters[0]);

			string												MessageID=CommandID;
			EMyHttpClientHttpMethod								Method=EMyHttpClientHttpMethod.E_DELETE;
			string												URL=$"{BASE_ADDRESS}OneToMany/DeleteEntity?ID={ID}";
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
			CommandsCollection.Add(new CMenuCommand("2","GET ENTITY",new EMenuCommandParameterType[]{EMenuCommandParameterType.E_INT},ExecuteCommandGetEntity));
			CommandsCollection.Add(new CMenuCommand("3","INSERT ENTITY",new EMenuCommandParameterType[]{EMenuCommandParameterType.E_STRING,EMenuCommandParameterType.E_STRING,EMenuCommandParameterType.E_STRING},ExecuteCommandInsertEntity));
			CommandsCollection.Add(new CMenuCommand("4","UPDATE ENTITY",new EMenuCommandParameterType[]{EMenuCommandParameterType.E_INT,EMenuCommandParameterType.E_STRING,EMenuCommandParameterType.E_STRING,EMenuCommandParameterType.E_STRING},ExecuteCommandUpdateEntity));
			CommandsCollection.Add(new CMenuCommand("5","DELETE ENTITY",new EMenuCommandParameterType[]{EMenuCommandParameterType.E_INT},ExecuteCommandDeleteEntity));

			CMenuCommand[]										Commands=CommandsCollection.ToArray();

			return(Commands);
		}
//--------------------------------------------------------------------------------------------------------------------------------
	}
//--------------------------------------------------------------------------------------------------------------------------------
}
//--------------------------------------------------------------------------------------------------------------------------------