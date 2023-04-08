using System;
using System.Reflection;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Shapes;
using System.Windows.Media.Imaging;
//------------------------------------------------------------------------------
namespace TreeViewsAndListViews
{
//------------------------------------------------------------------------------
	public class CSimpleTreeView : Window
	{
//------------------------------------------------------------------------------
        public CSimpleTreeView()
		{
            Title = "Manually Populate TreeView";

            TreeView		MyTree=new TreeView();

            Content=MyTree;

            TreeViewItem	ItemAnimal=new TreeViewItem();

            ItemAnimal.Header="Animal";
			// !!! Ako CHILD moze byt LUBOVOLNY OBJEKT.
            MyTree.Items.Add(ItemAnimal);

            TreeViewItem	ItemDog=new TreeViewItem();

            ItemDog.Header="Dog";
            ItemDog.Items.Add("Poodle");
            ItemDog.Items.Add("Irish Setter");
            ItemDog.Items.Add("German Shepherd");
            ItemAnimal.Items.Add(ItemDog);

            TreeViewItem	ItemCat=new TreeViewItem();

            ItemCat.Header="Cat";
            ItemCat.Items.Add("Calico");

            TreeViewItem	Item=new TreeViewItem();

            Item.Header="Alley Cat";
            ItemCat.Items.Add(Item);

            Button			TreeButton=new Button();

            TreeButton.Content="Noodles";
			// Pridam BUTTON ako LEAF TreeView.
            ItemCat.Items.Add(TreeButton);

            ItemCat.Items.Add("Siamese");
            ItemAnimal.Items.Add(ItemCat);

            TreeViewItem	ItemPrimate=new TreeViewItem();

            ItemPrimate.Header="Primate";
            ItemPrimate.Items.Add("Chimpanzee");
            ItemPrimate.Items.Add("Bonobo");
            ItemPrimate.Items.Add("Human");
            ItemAnimal.Items.Add(ItemPrimate);

            TreeViewItem	ItemMineral=new TreeViewItem();

            ItemMineral.Header="Mineral";
            ItemMineral.Items.Add("Calcium");
            ItemMineral.Items.Add("Zinc");
            ItemMineral.Items.Add("Iron");
            MyTree.Items.Add(ItemMineral);

            TreeViewItem	ItemVegetable=new TreeViewItem();

            ItemVegetable.Header="Vegetable";
            ItemVegetable.Items.Add("Carrot");
            ItemVegetable.Items.Add("Asparagus");
            ItemVegetable.Items.Add("Broccoli");
            MyTree.Items.Add(ItemVegetable);
		}
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------