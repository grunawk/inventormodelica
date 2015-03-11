  Translator Sample
  =======================
  
 This sample demonstrates how to use the Inventor API to integrate
  a file translator.  

  
  How to run this sample:
 
  1) Copy Autodesk.Translator.Inventor.addin into ...\Autodesk\Inventor 20XX\Addins folder.
     For XP: C:\Documents and Settings\All Users\Application Data\Autodesk\Inventor 20XX\Addins.
     For Vista/Win7: C:\ProgramData\Autodesk\Inventor 20XX\Addins.

  2) Copy bin\Translator.dll into Inventor bin folder(For example: C:\Program Files\Autodesk\Inventor 20XX\Bin).

  3) Startup Inventor, and follow below steps to use the translator addin.
  
  The file types supported by the translator will now
  be displayed by Inventor in the Open and Save Copy As dialogs.

  If the user selects the file type supported by the Add-In from the
  Open dialog, Inventor notifies the Add-In and supplies the filename
  of the selected file.  The Add-In can then open the file, perform
  whatever's needed to produce a SAT file and then use the Inventor
  API to create a new document and read in the SAT file.

  If the user selects the file type from the Save Copy As dialog, Inventor
  notifies the Add-In and supplies the name of the file to save to.
  The Add-In can then use the Inventor API to query the model and then
  write the model in the new format to the specified file.
 
  This sample demonstrates this concept by supporting a simple
  translator that translates spheres in Part documents.
  

  Language/Compiler: C++
  Executable /DLL : Translator.dll
  Server: Inventor.

 