#define INTERNAL_VERSION "1.1"

#ifndef INITIALIZED_LOCALE
#define INITIALIZED_LOCALE

#ifndef LANG
#define LANG 0
#endif // LANG

#if LANG == 0
#ifdef _M_X64
#pragma message("x64")
#define SERVER_FILE_NAME "font-tool-x86_64-en.exe"
#else
#pragma message("x86")
#define SERVER_FILE_NAME "font-tool-x86-en.exe"
#endif // _M_X64
#pragma message("Compiling in English")
#pragma setlocale("en-GB")
#define ADD_FILES "Add Files"
#define ADD_FOLDER "Add Folder"
#define R "Remove"
#define R_ALL "Remove All"
#define FONTS "Fonts"
#define FOLDERS "Folders"
#define FILES "Files"
#define ERRORS "Errors"
#define RECURSIVE "Recursive"
#define LD_FONT_FOLDERS "Loaded Font Folders"
#define LD_FONT_FILES "Loaded Font Files"
#define E_ITEMS "Erroneous Items"
#define READING_FILESYSTEM "Reading Filesystem"
#define UPDATING_DATABASE "Updating Database"
#define A_FONT_FILES "Add Font Files"
#define A_FONT_FOLDERS "Add Font Folders"
#define FONT_FILES "Font Files"
#define READY "Ready"
#define LG_FONTS "Loading Fonts"
#define INDEXING "Indexing"
#define LG "Loading"
#define LD "Loaded"
#define ULG "Unloading"
#define ULD "Unloaded"
#define ABOUT_TO_CLOSE "About to Close"
#define R_SELECTIONS "Remove Selections"
#define R_FOLDER "Remove Folder"
#define R_FONT "Remove Font"
#define R_E "Remove Erroneous Item"
#define R_A_E "Remove All Erroneous Items"
#define R_A_Files "Remove All Files"
#define R_A_Folders "Remove All Folders"
#define OPEN "Open"
#define NAME "Font Tool"
#define DESC_NAME NAME ": Use fonts without administrator rights!"
#define DESC_DESC "Written in C++ with the WxWidgets GUI library.\n"
#define DESC_COPYRIGHT                                                                                                         \
	"2018. You may modify or distribute this software as you wish. Contact James Yu in person for the source code."
#define VERSION INTERNAL_VERSION "EN"
#define BUSY NAME ": Busy"
#define INFORMATION "About"
#define CLOSE "Close"
#define DESTROY "Destroy"
#define WILL_IT_DESTROY "Will it destroy?"
#define UPDATE "Update"
#define CHECKING_UPDATES "Checking for updates"
#define DOWNLOADING_VERSION "Downloading version"
#define UP_TO_DATE "All up to date!"
#define MESSAGE_UPDATED "All updated! Changes will take effect upon next run."

#elif LANG == 1
#ifdef _M_X64
#pragma message("x64")
#define SERVER_FILE_NAME "font-tool-x86_64-de.exe"
#else
#pragma message("x86")
#define SERVER_FILE_NAME "font-tool-x86-de.exe"
#endif // _M_X64
#pragma setlocale("de-LI")
#pragma message("Auf Deutsch kompilieren...")
#define ADD_FILES "Schriftdateien"
#define ADD_FOLDER "Ordner"
#define R "Entfernen"
#define R_ALL "Alle Schriften entfernen"
#define FONTS "Schriften"
#define FOLDERS "Ordner"
#define FILES "Schriftdateien"
#define ERRORS "Fehler"
#define RECURSIVE "Rekusiv"
#define LD_FONT_FOLDERS "Hinzugefügte Schriftordner"
#define LD_FONT_FILES "Hinzugefügte Schriftdateien"
#define E_ITEMS "Falsche Artikel"
#define READING_FILESYSTEM "Dateisystem lesen"
#define UPDATING_DATABASE "Datenbank aktualisieren"
#define A_FONT_FILES "Schriftdateien hinzufügen"
#define A_FONT_FOLDERS "Schriftordner hinzufügen"
#define FONT_FILES "Schriftdateien"
#define READY "Fertig"
#define LG_FONTS "Schriften hinzufügen"
#define INDEXING "Indizieren"
#define LG "Hinzufügen"
#define LD "Hinzugefügt"
#define ULG "Entfernen"
#define ULD "Entfernte"
#define ABOUT_TO_CLOSE "Program ist bereit, sich zu schließen"
#define R_SELECTIONS "Ausgewälte Artikel entfernen"
#define R_FOLDER "Ordner entfernen"
#define R_FONT "Schrift entfernen"
#define R_E "Falschen Artikel entfernen"
#define R_A_E "Alle falschen Artikel entfernen"
#define R_A_Files "Alle Schriftdateien entfernen"
#define R_A_Folders "Alle Ornder entfernen"
#define OPEN "Öffnen"
#define NAME "Schrifthilfsprogramm"
#define DESC_NAME NAME ": Benutzen Sie Schriften ohne Rechte eines Administrators!"
#define DESC_DESC "Auf C++ mit der WxWidgets-Bibliothek geschrieben.\n"
#define DESC_COPYRIGHT                                                                                                         \
	"2018. Sie dürfen frei dieses Program teilen oder ändern. Für den Quell-Code den James Yu persönlich kontaktieren."

#define VERSION INTERNAL_VERSION "DE"
#define BUSY NAME ": tätig"
#define INFORMATION "Informationen"
#define CLOSE "Program Schließen"
#define DESTROY "Program Zerstören"
#define WILL_IT_DESTROY "Wird's sich zerstören?"
#define UPDATE "Aktualisieren"
#define CHECKING_UPDATES "Aktualisierungen suchen"
#define DOWNLOADING "herunterladen"
#define VERSION_STR "Fassung"
#define UP_TO_DATE "Schon aktualisiert!"
#define MESSAGE_UPDATED "Die Änderungen werden im Anschluss an die nächste Öffnung in Kraft sein."

#endif // LANG == 0 || 1

#endif // INITIALIZED_LOCALE
       // wxString::FromUTF8()