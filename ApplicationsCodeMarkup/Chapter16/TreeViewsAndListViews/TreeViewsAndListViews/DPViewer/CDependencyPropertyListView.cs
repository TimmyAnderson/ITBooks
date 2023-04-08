using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Reflection;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
//------------------------------------------------------------------------------
namespace TreeViewsAndListViews
{
//------------------------------------------------------------------------------
	public class CDependencyPropertyListView : ListView
	{
//------------------------------------------------------------------------------
        public static DependencyProperty						TypeProperty;
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
        static CDependencyPropertyListView()
        {
            TypeProperty=DependencyProperty.Register("Type", typeof(Type), typeof(CDependencyPropertyListView), new PropertyMetadata(null, new PropertyChangedCallback(OnTypePropertyChanged)));
        }
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
        public CDependencyPropertyListView()
        {
            GridView					LGridView=new GridView();

            this.View=LGridView;

            GridViewColumn				Col=new GridViewColumn();

            Col.Header="Name";
            Col.Width=150;
            Col.DisplayMemberBinding=new Binding("Name");
            LGridView.Columns.Add(Col);

            Col=new GridViewColumn();
            Col.Header="Owner";
            Col.Width=100;
            LGridView.Columns.Add(Col);

			// Vytvorim CELL TEMPLATE.
            DataTemplate				LTemplate=new DataTemplate();

            Col.CellTemplate=LTemplate;

			// TextBlock je zakladom CELL TEMPLATE.
            FrameworkElementFactory		ElTextBlock=new FrameworkElementFactory(typeof(TextBlock));

            LTemplate.VisualTree=ElTextBlock;

            Binding						LBind=new Binding("OwnerType");

			// !!! Nastavim CONVERTER.
            LBind.Converter=new CTypeToString();

            ElTextBlock.SetBinding(TextBlock.TextProperty, LBind);

            Col=new GridViewColumn();
            Col.Header="Type";
            Col.Width=100;
            LGridView.Columns.Add(Col);

            LTemplate=new DataTemplate();
            Col.CellTemplate=LTemplate;
            ElTextBlock=new FrameworkElementFactory(typeof(TextBlock));
            LTemplate.VisualTree=ElTextBlock;

            LBind=new Binding("PropertyType");
            LBind.Converter=new CTypeToString();
            ElTextBlock.SetBinding(TextBlock.TextProperty, LBind);

            Col=new GridViewColumn();
            Col.Header="Default";
            Col.Width=75;
            Col.DisplayMemberBinding=new Binding("DefaultMetadata.DefaultValue");
            LGridView.Columns.Add(Col);

            Col=new GridViewColumn();
            Col.Header="Read-Only";
            Col.Width=75;
            Col.DisplayMemberBinding=new Binding("DefaultMetadata.ReadOnly");
            LGridView.Columns.Add(Col);

            Col=new GridViewColumn();
            Col.Header="Usage";
            Col.Width=75;
            Col.DisplayMemberBinding=new Binding("DefaultMetadata.AttachedPropertyUsage");
            LGridView.Columns.Add(Col);

            Col=new GridViewColumn();
            Col.Header="Flags";
            Col.Width=250;
            LGridView.Columns.Add(Col);

            LTemplate=new DataTemplate();
            Col.CellTemplate=LTemplate;
            ElTextBlock = new FrameworkElementFactory(typeof(TextBlock));
            LTemplate.VisualTree=ElTextBlock;

            LBind=new Binding("DefaultMetadata");
			// !!! Nastavim CONVERTER.
            LBind.Converter=new CMetadataToFlags();
            ElTextBlock.SetBinding(TextBlock.TextProperty, LBind);
        }
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
        public Type												Type
        {
            get
			{
				return((Type)GetValue(TypeProperty));
			}
            set
			{
				SetValue(TypeProperty, value);
			}
        }
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
        public static void OnTypePropertyChanged(DependencyObject Obj, DependencyPropertyChangedEventArgs Args)
        {
            CDependencyPropertyListView					LValue=Obj as CDependencyPropertyListView;
            Type										LType=Args.NewValue as Type;

            LValue.ItemsSource=null;

            if (LType!=null)
            {
                SortedList<string, DependencyProperty>	LList=new SortedList<string, DependencyProperty>();
                FieldInfo[]								Infos=LType.GetFields();

                foreach (FieldInfo Info in Infos)
                    if (Info.FieldType==typeof(DependencyProperty))
                        LList.Add(Info.Name, (DependencyProperty)Info.GetValue(null));

                LValue.ItemsSource=LList.Values;
            }
        }
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------