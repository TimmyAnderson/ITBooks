using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
//------------------------------------------------------------------------
// 1. Program demonstruje pouzitie Annotations.
// 2. Annotations umoznuju uzivatelovi Annotations do dokumentu komentare a zvyraznit text.
// 3. Existuju 2 typy Annotations.
//    A. Highlighting - umoznuje zvyraznit urcitu cast textu.
//    B. Sticky notes - umozuju pridat do textu komentar fo form maleho okienka, ktore sa zobrazi na danom texte.
// 4. WPF ma 3 kludove triedy na realizaciu Annotations.
//    A. AnnotationService - klucova sluzba implemntujuca Annotation service.
//    B. AnnotationStore - umoznuej vytvarat a mazat jednotlive Annotations. Je to abstraktna trieda, ktorej jedina impementacia je XmlStreamStore. Tato serializuje Annotations do XML odkial ho mozem ulozit do lubovolneho persistent store.
//    C. AnnotationHelper - podporna trieda sluziaca ako birdge medzi AnnotationService a AnnotationStore.
// !!! 5. Predtym, nez mozem Annotations pouzit, musim aktivovat pre Document Container (FlowDocumentReader, FlowDocumentScrollViewer, FlowDocumentPageViewer a DocumentViewer) aktivovat AnnotationService. AnnotationService musi mat ako parameter konstruktora Document a takisto musim pri vytvoreni predat odkaz na AnnotationStore. Ked ukoncujem Document mal by som data zo stremu ulozit, naprikald do nejakeho persistent store.
// !!! 6. Vytvorit Annotations je mozne dvoma sposobmi.
//     A. Pomocou AnnotationHelper volanim prislusnej metody, ktora nad SELECTED TESTOM vytvori prislusnu Annotation.
//     B. Pouzit Commands, ktore poskytuje trieda AnnotationService.
// 7. Ak chcem do StickyNote zaradit aj autora potom staci jeho meno preniest ako CommandParameter. V pripade vytvorenia cez metodu AnnotationHelper sa predava ako parameter metody.
// 8. Ak chcem zaradit Highlight Note potom jej musim do CommandParameter dat Brush. Tento Brush ale MUSI BYT SEMITRANSPARENTNY, inak by zakryl povodny text.
// 9. K jednotlivym Annotations je mozne pristupovat pomocou AnnotationStore.GetAnnonations() metody, ktora vracia kolekciu objektov Annotation. Tieto objekty obsahuju vsekty informacie o Annotations, ale DOST ZLE SA S NIMI PRACUJE.
// !!! 10. Sticky Notes - teda okienko na ktorom sa zobrazuju Anotations je moze customizovat cez CT. Kedze toto okienko je zdedeny z StickyNoteControl tak je mozne nastavit Style AUTOMATICKY APLIKOVANY na tuto triedu. Tym sa bude moj novy Style pomocou ktoreho implementuje CT vztahovat na KAZDY STICKY NOTE. Jedinou vecou na ktoru treba davat, ze musim rozlisit Ink a Text Notes. Pre Ink Note je treba pouzit InkCanvas a AKO NAME MU DAT "PART_ContentControl", zatial co pri Text Note je treba pouzit RichTextBox a AKO NAME MU DAT "PART_ContentControl".
// !!! 11. V pripade FlowDocument mozem Annotations ukladat IBA DO CUSTOM STORE. Ale v pripade Fixed Documents mozem ich ukladat PRIAMO DO XPS suboru vyuzitim triedy Package. XPS DOKUEMNT MUSI BYT POCAS EDITACIE V PROGRAME STALE OTVORENY na ReadWrite.
// !!! 12. AnnotationStore ma mnozstvo Eventov, ktore su volane ak napriklad pridam, alebo zmenim Annotation.
//------------------------------------------------------------------------
namespace AnnotationTest
{
//------------------------------------------------------------------------
	public partial class MainWindow:Window
	{
//------------------------------------------------------------------------
		public MainWindow()
		{
			InitializeComponent();
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		private void Button_Click1(object Sender, RoutedEventArgs E)
		{
			SimpleAnnotation			Win=new SimpleAnnotation();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
		private void Button_Click2(object Sender, RoutedEventArgs E)
		{
			CustomStickyNotes			Win=new CustomStickyNotes();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
		private void Button_Click3(object Sender, RoutedEventArgs E)
		{
			XpsAnnotations				Win=new XpsAnnotations();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------