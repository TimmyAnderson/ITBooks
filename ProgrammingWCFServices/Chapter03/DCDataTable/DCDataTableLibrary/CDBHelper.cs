using System;
using System.Collections.Generic;
using System.Text;
using System.Data;
//-------------------------------------------------------------------------------------------------------
namespace DCDataTableLibrary
{
//-------------------------------------------------------------------------------------------------------
	public static class CDBHelper
	{
//-------------------------------------------------------------------------------------------------------
		public static DataTable GetDataTable()
		{
			DataTable		DT=new DataTable("Names");
			DataColumn		DC1=new DataColumn("FirstName",typeof(string));
			DataColumn		DC2=new DataColumn("LastName",typeof(string));
			DataColumn		DC3=new DataColumn("Age",typeof(int));

			DT.Columns.Add(DC1);
			DT.Columns.Add(DC2);
			DT.Columns.Add(DC3);

			DataRow			DR1=DT.NewRow();
			DataRow			DR2=DT.NewRow();

			DR1["FirstName"]="Timmy";
			DR1["LastName"]="Anderson";
			DR1["Age"]=12;

			DR2["FirstName"]="Jenny";
			DR2["LastName"]="Thompson";
			DR2["Age"]=13;

			DT.Rows.Add(DR1);
			DT.Rows.Add(DR2);

			return(DT);
		}
//-------------------------------------------------------------------------------------------------------
		public static string DataTableToString(DataTable DT)
		{
			StringBuilder			SB=new StringBuilder();

			foreach(DataRow DR in DT.Rows)
			{
				foreach(DataColumn DC in DT.Columns)
					SB.AppendLine(string.Format("{0}: {1} !",DC.ColumnName,DR[DC]));

				SB.AppendLine();
			}

			return(SB.ToString());
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------