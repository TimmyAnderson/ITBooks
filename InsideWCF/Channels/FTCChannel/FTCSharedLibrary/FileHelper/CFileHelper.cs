using System;
using System.Collections.Generic;
using System.Text;
using System.IO;
using System.Threading;
//-------------------------------------------------------------------------------------------------------
namespace FTCSharedLibrary
{
//-------------------------------------------------------------------------------------------------------
/*
	Helper trieda realizujuca citanie a zapis suborov.
	Obsah za zapisuje a cita z MemoryStream.
*/
//-------------------------------------------------------------------------------------------------------
	public static class CFileHelper
	{
//-------------------------------------------------------------------------------------------------------
		// Precita cely obsah suboru a ulozi ho do MemoryStream.
		public static MemoryStream ReadFileToStream(string FileName)
		{
			CSettings.Log.Write(CDebugHelper.GetMethodCallString(),ELogRecordType.E_LRT_METHOD_CALL);

			FileStream				FS=null;

			try
			{
				MemoryStream		MS=new MemoryStream();
				FileInfo			FI=new FileInfo(FileName);

				FS=FI.Open(FileMode.Open,FileAccess.Read);

				MS.SetLength(FS.Length);

				FS.Read(MS.GetBuffer(),0,(int) FS.Length);

				return(MS);
			}
			catch(Exception E)
			{
				CSettings.Log.Write(CDebugHelper.GetExceptionString(E),ELogRecordType.E_LRT_EXCEPTION);
				throw;
			}
			finally
			{
				if (FS!=null)
				{
					FS.Close();
					FS=null;
				}
			}
		}
//-------------------------------------------------------------------------------------------------------
		// Precita obsah MemoryStream do suboru.
		public static void WriteFileFromStream(string FileName, MemoryStream MS)
		{
			CSettings.Log.Write(CDebugHelper.GetMethodCallString(),ELogRecordType.E_LRT_METHOD_CALL);

			FileStream				FS=null;

			try
			{
				FileInfo			FI=new FileInfo(FileName);

				FS=FI.Open(FileMode.Create,FileAccess.Write);

				FS.Write(MS.GetBuffer(),0,(int) MS.Length);
				FS.Flush();
			}
			catch(Exception E)
			{
				CSettings.Log.Write(CDebugHelper.GetExceptionString(E),ELogRecordType.E_LRT_EXCEPTION);
				throw;
			}
			finally
			{
				if (FS!=null)
				{
					FS.Close();
					FS=null;
				}
			}
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------