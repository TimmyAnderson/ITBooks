using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IdentityModel.Selectors;
using System.ServiceModel;
//-------------------------------------------------------------------------------------------------------
namespace SecurityWithPrivateQueuesService
{
//-------------------------------------------------------------------------------------------------------
	public class CCustomAuthentication : UserNamePasswordValidator
	{
//-------------------------------------------------------------------------------------------------------
		public override void Validate(string UserName, string Password)
		{
			Console.WriteLine(string.Format("UserName: [{0}], Password: [{1}] !",UserName,Password));
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------