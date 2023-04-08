using System;
using System.Reflection;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Media;
using System.IO;
using System.ComponentModel;
using System.Windows.Data;
//------------------------------------------------------------------------------
namespace TreeViewsAndListViews
{
//------------------------------------------------------------------------------
	public class CSimpleListView : Window
	{
//------------------------------------------------------------------------------
        public CSimpleListView(bool ResetViewToNULL)
		{
            Title = "List System Parameters";

            ListView			LListView=new ListView();

            Content=LListView;

            // !!! Vytvorim GridView.
            GridView			LGridView=new GridView();

            LListView.View=LGridView;

            // Definujem stlpce pre GridView.
            GridViewColumn		Col=new GridViewColumn();

            Col.Header="Property Name";
            Col.Width=200;
            Col.DisplayMemberBinding=new Binding("Name");
            LGridView.Columns.Add(Col);

            Col=new GridViewColumn();
            Col.Header="Value";
            Col.Width=200;
            Col.DisplayMemberBinding=new Binding("Value");
            LGridView.Columns.Add(Col);

            PropertyInfo[]		Props=typeof(SystemParameters).GetProperties();

            foreach (PropertyInfo Prop in Props)
			{
                if (Prop.PropertyType!=typeof(ResourceKey))
                {
                    CSystemParam		SysParam=new CSystemParam();

                    SysParam.Name=Prop.Name;
                    SysParam.Value=Prop.GetValue(null, null);
                    LListView.Items.Add(SysParam);
                }
			}
			
			// Vypnem View.
			if (ResetViewToNULL==true)
				LListView.View=null;
		}
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------