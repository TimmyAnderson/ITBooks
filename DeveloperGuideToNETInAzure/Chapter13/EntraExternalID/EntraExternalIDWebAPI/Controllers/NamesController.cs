using System;
using System.Collections.Generic;
using System.Linq;
using System.Security.Claims;
using System.Text;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore.ChangeTracking;
using Microsoft.Extensions.Logging;
using Microsoft.Identity.Web;
using Microsoft.Identity.Web.Resource;
//----------------------------------------------------------------------------------------------------------------------
namespace EntraExternalIDWebAPI
{
//----------------------------------------------------------------------------------------------------------------------
	// !!! Kazdy API CALL MUSI byt AUTHORIZED.
	[Authorize]
	[ApiController]
	[Route("[controller]")]
	public class NamesController : ControllerBase
	{
//----------------------------------------------------------------------------------------------------------------------
		private readonly ILogger<NamesController>				MLogger;
		private readonly IDBOperationsService					MDBOperationsService;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public NamesController(ILogger<NamesController> Logger, IDBOperationsService DBOperationsService)
		{
			MLogger=Logger;
			MDBOperationsService=DBOperationsService;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private bool IsProgramMakingRequest()
		{
			const string										CLAIM_TYPE_ID_TYPE="idtyp";
			const string										CLAIM_TYPE_ROLES="roles";
			const string										CLAIM_TYPE_SCP="scp";
			const string										CLAIM_VALUE_APP="app";

			Claim[]												Claims=HttpContext.User.Claims.ToArray();

			// !!! Ak CLAIM [idtyp] obsahuje VALUE [app], tak ACCESS TOKEN bol generovany pre PROGRAM, a nie USER.
			// !!! CLAIM [idtyp] je OPTIONAL a nemusi byt sucastou HTTP REQUEST.
			foreach(Claim Claim in Claims)
			{
				string											ClaimType=Claim.Type;

				if (ClaimType==CLAIM_TYPE_ID_TYPE)
				{
					string										ClaimValue=Claim.Value;

					if (ClaimValue==CLAIM_VALUE_APP)
					{
						return(true);
					}
					else
					{
						return(false);
					}
				}
			}

			// !!! Ak v REQUEST je CLAIM [scp], tak ACCESS TOKEN bol generovany pre USER.
			foreach(Claim Claim in Claims)
			{
				string											ClaimType=Claim.Type;

				if (ClaimType==CLAIM_TYPE_SCP)
				{
					return(false);
				}
			}

			// !!! Ak v REQUEST je CLAIM [roles], tak ACCESS TOKEN bol generovany pre PROGRAM.
			foreach(Claim Claim in Claims)
			{
				string											ClaimType=Claim.Type;

				if (ClaimType==CLAIM_TYPE_ROLES)
				{
					return(true);
				}
			}

			return(false);
		}
//----------------------------------------------------------------------------------------------------------------------
		private Guid? GetUserID()
		{
			string												ObjectID=HttpContext.User.GetObjectId();
			Guid												UserID;
	
			if (Guid.TryParse(ObjectID,out UserID)==true)
			{
				return(UserID);
			}
			else
			{
				return(null);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		private string[] GetRoles()
		{
			List<string>										RolesList=new List<string>();

			Claim[]												Claims=HttpContext.User.Claims.ToArray();
			
			foreach(Claim Claim in Claims)
			{
				string											ClaimType=Claim.Type;

				if (ClaimType==ClaimTypes.Role)
				{
					string										RoleValue=Claim.Value;

					RolesList.Add(RoleValue);
				}
			}

			string[]											Roles=RolesList.ToArray();

			return(Roles);
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private void LogOperation(string OperationName, bool ProgramMakingRequest, Guid? UserID, string[] Roles)
		{
			StringBuilder										RolesText=new StringBuilder();

			for(int Index=0;Index<Roles.Length;Index++)
			{
				if (Index>0)
				{
					RolesText.Append(", ");
				}

				string											Role=Roles[Index];

				RolesText.Append(Role);
			}

			MLogger.LogInformation($"OPERATION [{OperationName}] - PROGRAM REQUEST [{ProgramMakingRequest}] USER ID [{UserID}] ROLES [{RolesText.ToString()}].");
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		[HttpGet("GetNames")]
		// !!! PERMISSIONS, ktore musi CLIENT splnat.
		[RequiredScopeOrAppPermission(new string[]{Program.SCOPE_READ,Program.SCOPE_READ_WRITE},new string[]{Program.APP_PERMISION_READ,Program.APP_PERMISION_READ_WRITE})]
		public async Task<ActionResult> GetNames()
		{
			try
			{
				bool											ProgramMakingRequest=IsProgramMakingRequest();
				Guid?											UserID=GetUserID();
				string[]										Roles=GetRoles();

				LogOperation(nameof(GetNames),ProgramMakingRequest,UserID,Roles);

				CEntityName[]									Names=await MDBOperationsService.GetNames();
				CName[]											ResultContent=Names.Select(P => new CName(P.ID,P.FirstName,P.LastName,P.Age,P.Sex)).ToArray();

				ActionResult									Response=Ok(ResultContent);

				return(Response);
			}
			catch(Exception E)
			{
				MLogger.LogError(E,"OPERATION FAILED.");
				throw;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		[HttpGet("GetName")]
		// !!! PERMISSIONS, ktore musi CLIENT splnat.
		[RequiredScopeOrAppPermission(new string[]{Program.SCOPE_READ,Program.SCOPE_READ_WRITE},new string[]{Program.APP_PERMISION_READ,Program.APP_PERMISION_READ_WRITE})]
		public async Task<ActionResult<CName>> GetName(int ID)
		{
			try
			{
				bool											ProgramMakingRequest=IsProgramMakingRequest();
				Guid?											UserID=GetUserID();
				string[]										Roles=GetRoles();

				LogOperation(nameof(GetName),ProgramMakingRequest,UserID,Roles);

				CEntityName										Name=await MDBOperationsService.GetName(ID);

				if (Name!=null)
				{
					CName										ResultContent=new CName(Name.ID,Name.FirstName,Name.LastName,Name.Age,Name.Sex);
					ActionResult								Response=Ok(ResultContent);

					return(Response);
				}
				else
				{
					ActionResult								Response=NotFound();

					return(Response);
				}
			}
			catch(Exception E)
			{
				MLogger.LogError(E,"OPERATION FAILED.");
				throw;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		[HttpPost("InsertName")]
		// !!! PERMISSIONS, ktore musi CLIENT splnat.
		[RequiredScopeOrAppPermission(new string[]{Program.SCOPE_READ_WRITE},new string[]{Program.APP_PERMISION_READ_WRITE})]
		public async Task<ActionResult> InsertName(CName Name)
		{
			try
			{
				bool											ProgramMakingRequest=IsProgramMakingRequest();
				Guid?											UserID=GetUserID();
				string[]										Roles=GetRoles();

				LogOperation(nameof(InsertName),ProgramMakingRequest,UserID,Roles);

				CEntityName										NameToInsert=new CEntityName(Name.FirstName,Name.LastName,Name.Age,Name.Sex);
				CEntityName										InsertedName=await MDBOperationsService.InsertName(NameToInsert);
				CName											ResultContent=new CName(InsertedName.ID,InsertedName.FirstName,InsertedName.LastName,InsertedName.Age,InsertedName.Sex);

				ActionResult									Result=CreatedAtAction(nameof(GetName),ResultContent);

				return(Result);
			}
			catch(Exception E)
			{
				MLogger.LogError(E,"OPERATION FAILED.");
				throw;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		[HttpPut("UpdateName")]
		// !!! PERMISSIONS, ktore musi CLIENT splnat.
		[RequiredScopeOrAppPermission(new string[]{Program.SCOPE_READ_WRITE},new string[]{Program.APP_PERMISION_READ_WRITE})]
		public async Task<ActionResult> UpdateName(CName Name)
		{
			try
			{
				bool											ProgramMakingRequest=IsProgramMakingRequest();
				Guid?											UserID=GetUserID();
				string[]										Roles=GetRoles();

				LogOperation(nameof(UpdateName),ProgramMakingRequest,UserID,Roles);

				CEntityName										NameToUpdate=new CEntityName(Name.ID,Name.FirstName,Name.LastName,Name.Age,Name.Sex);
				CEntityName										NameFromDB=await MDBOperationsService.UpdateName(NameToUpdate);

				if (NameFromDB!=null)
				{
					ActionResult								Result=NoContent();

					return(Result);
				}
				else
				{
					ActionResult								Response=NotFound();

					return(Response);
				}
			}
			catch(Exception E)
			{
				MLogger.LogError(E,"OPERATION FAILED.");
				throw;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		[HttpDelete("DeleteName")]
		// !!! PERMISSIONS, ktore musi CLIENT splnat.
		[RequiredScopeOrAppPermission(new string[]{Program.SCOPE_READ_WRITE},new string[]{Program.APP_PERMISION_READ_WRITE})]
		public async Task<ActionResult> DeleteName(int ID)
		{
			try
			{
				bool											ProgramMakingRequest=IsProgramMakingRequest();
				Guid?											UserID=GetUserID();
				string[]										Roles=GetRoles();

				LogOperation(nameof(DeleteName),ProgramMakingRequest,UserID,Roles);

				bool											IsDeleted=await MDBOperationsService.DeleteName(ID);

				if (IsDeleted==true)
				{
					ActionResult								Response=NoContent();

					return(Response);
				}
				else
				{
					ActionResult								Response=NotFound();

					return(Response);
				}
			}
			catch(Exception E)
			{
				MLogger.LogError(E,"OPERATION FAILED.");
				throw;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------