using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.JsonPatch;
using DocumentationUsingOpenAPI.Model;
//----------------------------------------------------------------------------------------------------------------------
namespace DocumentationUsingOpenAPI.Database
{
//----------------------------------------------------------------------------------------------------------------------
	public interface INameProvider
	{
//----------------------------------------------------------------------------------------------------------------------
		CName AddName(CName Name);
		CName UpdateName(CName Name);
		bool PatchName(int ID, JsonPatchDocument<CName> Patch);
		void RemoveName(int ID);
		CName GetName(int ID);
		CName[] GetNames();
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------