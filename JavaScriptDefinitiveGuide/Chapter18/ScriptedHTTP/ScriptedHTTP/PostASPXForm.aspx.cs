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
	public partial class PostASPXForm:System.Web.UI.Page
	{
//-------------------------------------------------------------------------------------------------------
		protected void Page_Load(object Sender, EventArgs E)
		{
			// Ziskam VELKOST HTTP REQUEST BODY.
			byte[]												Content=new byte[Request.ContentLength];

			// !!! Nacitam HTTP REQUEST BODY.
			Request.InputStream.Read(Content,0,Request.ContentLength);

			Encoding											ContentEncoding=Request.ContentEncoding;
			string												DecodedContent=ContentEncoding.GetString(Content);

			// !!! LABEL nastavim na spracovany HTTP REQUEST BODY.
			MLBLLabel.Text=DecodedContent.ToUpper();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------