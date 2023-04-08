using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace ScriptedHTTP
{
//-------------------------------------------------------------------------------------------------------
	public partial class GetASPXFormWithDataInURL:System.Web.UI.Page
	{
//-------------------------------------------------------------------------------------------------------
		protected void Page_Load(object Sender, EventArgs E)
		{
			// !!! Kedze data su zakodovane ako URL PARAMETER 'Name' QUERY STRING musim ziskat z QUERY STRING hodnotu PARAMETRA 'Name'.
			string												Value=Request.QueryString["Name"];

			// !!! LABEL nastavim na data nacitane z URL QUERY STRING.
			MLBLLabel.Text=string.Format("Name: [{0}] !",Value);
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------