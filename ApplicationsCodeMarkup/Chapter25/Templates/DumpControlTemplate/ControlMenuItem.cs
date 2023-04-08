using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Reflection;
using System.Windows;
using System.Windows.Controls;
//-------------------------------------------------------------------------------------------------------
namespace NamespaceDumpControlTemplate
{
//-------------------------------------------------------------------------------------------------------
	public class ControlMenuItem : MenuItem
	{
//-------------------------------------------------------------------------------------------------------
        public ControlMenuItem()
        {
            Assembly						LAssembly=Assembly.GetAssembly(typeof(Control));
            Type[]							AType=LAssembly.GetTypes();
            SortedList<string, MenuItem>	SortList=new SortedList<string, MenuItem>();

            Header="Control";
            Tag=typeof(Control);
            SortList.Add("Control", this);

            foreach (Type LTyp in AType)
            {
                if (LTyp.IsPublic==true && (LTyp.IsSubclassOf(typeof(Control))==true))
                {
                    MenuItem		Item=new MenuItem();

                    Item.Header=LTyp.Name;
                    Item.Tag=LTyp;
                    SortList.Add(LTyp.Name, Item);
                }
            }

            foreach (KeyValuePair<string, MenuItem> KVP in SortList)
            {
                if (KVP.Key!="Control")
                {
                    string			StrParent=((Type)KVP.Value.Tag).BaseType.Name;
                    MenuItem		ItemParent=SortList[StrParent];

                    ItemParent.Items.Add(KVP.Value);
                }
            }

            foreach (KeyValuePair<string, MenuItem> KVP in SortList)
            {
                Type				LType=(Type) KVP.Value.Tag;

                if (LType.IsAbstract==true && KVP.Value.Items.Count==0)
                    KVP.Value.IsEnabled=false;

                if (LType.IsAbstract==false && KVP.Value.Items.Count>0)
                {
                    MenuItem		Item=new MenuItem();

                    Item.Header=KVP.Value.Header as string;
                    Item.Tag=LType;
                    KVP.Value.Items.Insert(0, Item);
                }
            }
        }
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------