rem Regeneruje DLL z prelozenych textov v CSV.
rem !!! Musi byt spolu s LocBaml.exe na v Bin\Debug adresari.
locbaml /generate en-US\LocalizationTest.resources.dll /trans:Edited_LocalizationTest.resources.CSV /cul:sk-SK /out:sk-SK
locbaml /generate en-US\LocalizationTestLibrary.resources.dll /trans:Edited_LocalizationTestLibrary.resources.CSV /cul:sk-SK /out:sk-SK