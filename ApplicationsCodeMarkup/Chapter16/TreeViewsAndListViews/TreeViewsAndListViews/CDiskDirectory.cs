using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
//------------------------------------------------------------------------------
namespace TreeViewsAndListViews
{
//------------------------------------------------------------------------------
	// Trieda sa pouziva ako DATA SOURCE pre HierarchicalDataTemplate .
	public class CDiskDirectory
	{
//------------------------------------------------------------------------------
        private DirectoryInfo									MDirInfo;
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
        public CDiskDirectory(DirectoryInfo DirInfo)
        {
            this.MDirInfo=DirInfo;
        }
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
        // Property, ktora sa bude zobrazovat ako v ITEMS v TREE VIEW.
        public string											Name
        {
            get
			{
				return(MDirInfo.Name);
			}
        }
//------------------------------------------------------------------------------
        // Property sa pouzije na VIAZANIE SA na CHILD ITEMS v HierarchicalDataTemplate a tym vytvori hierarchicku strukturu objektov.
        public List<CDiskDirectory>								Subdirectories
        {
            get
            {
                List<CDiskDirectory>	Dirs=new List<CDiskDirectory>();
                DirectoryInfo[]			SubDirs;

                try
                {
                    SubDirs=MDirInfo.GetDirectories();
                }
                catch
                {
                    return Dirs;
                }

                foreach (DirectoryInfo SubDir in SubDirs)
                    Dirs.Add(new CDiskDirectory(SubDir));

                return(Dirs);
            }
//------------------------------------------------------------------------------
        }
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------