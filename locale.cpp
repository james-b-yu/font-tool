#define INTERNAL_VERSION "1.1.4"
#define CREATOR "James Yu"
#define YEAR "2017-2018"

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
#define COPYRIGHT                                                                                                              \
	"Copyright " YEAR " " CREATOR                                                                                              \
	"\n\nPermission is hereby granted, free of charge, to any person obtaining a copy of this software and associated "        \
	"documentation files (the \"Software\"), to deal in the Software without restriction, including without limitation the "   \
	"rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit "  \
	"persons to whom the Software is furnished to do so, subject to the following conditions:\n\nThe above copyright notice "  \
	"and this permission notice shall be included in all copies or substantial portions of the Software.\n\nTHE SOFTWARE IS "  \
	"PROVIDED \"AS IS\", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF "    \
	"MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT "       \
	"HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, "       \
	"ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE."
#define VERSION INTERNAL_VERSION "EN"
#define BUSY_NAME NAME ": Busy"
#define UPDATE_AVAILABLE_NAME NAME ": Update Available"
#define INFORMATION "About"
#define CLOSE "Close"
#define DESTROY "Destroy"
#define WILL_IT_DESTROY "Will it destroy?"
#define UPDATE "Update"
#define CHECKING_UPDATES "Checking for updates"
#define DOWNLOADING_VERSION "Downloading version"
#define VERSION_STR "Version"
#define UP_TO_DATE "All up to date!"
#define MESSAGE_UPDATED "Update will take effect upon next run."
#define UPDATE_READY "Update ready!"
#define E_UPDATE_INFO "Error retrieving update information."
#define E_UPDATE_DOWNLOAD "Error downloading update."
#define PRERELEASE_VERSION "You are using a pre-release version."
#define UPDATE_AVAILABLE_MESSAGE "Update available: use the tray icon to update."
#define ABOUT_NAME "About " NAME

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
#define RECURSIVE "Rekursiv"
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
#define LG "hinzufügen"
#define LD "hinzugefügt"
#define ULG "entfernen"
#define ULD "entfernt"
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
#define COPYRIGHT                                                                                                               \
	"Copyright " YEAR " " CREATOR                                                                                               \
	"\n\nHiermit wird unentgeltlich jeder Person, die eine Kopie der Software und der zugehörigen Dokumentationen (die "       \
	"\"Software\") erhält, die Erlaubnis erteilt, sie uneingeschränkt zu nutzen, inklusive und ohne Ausnahme mit dem Recht, " \
	"sie zu verwenden, zu kopieren, zu verändern, zusammenzufügen, zu veröffentlichen, zu verbreiten, zu unterlizenzieren "  \
	"und/oder zu verkaufen, und Personen, denen diese Software überlassen wird, diese Rechte zu verschaffen, unter den "       \
	"folgenden Bedingungen:\n\nDer obige Urheberrechtsvermerk und dieser Erlaubnisvermerk sind in allen Kopien oder "           \
	"Teilkopien der Software beizulegen.\n\nDIE SOFTWARE WIRD OHNE JEDE AUSDRÜCKLICHE ODER IMPLIZIERTE GARANTIE "              \
	"BEREITGESTELLT, EINSCHLIEẞLICH DER GARANTIE ZUR BENUTZUNG FÜR DEN VORGESEHENEN ODER EINEM BESTIMMTEN ZWECK SOWIE "      \
	"JEGLICHER RECHTSVERLETZUNG, JEDOCH NICHT DARAUF BESCHRÄNKT. IN KEINEM FALL SIND DIE AUTOREN ODER COPYRIGHTINHABER FÜR "  \
	"JEGLICHEN SCHADEN ODER SONSTIGE ANSPRÜCHE HAFTBAR ZU MACHEN, OB INFOLGE DER ERFÜLLUNG EINES VERTRAGES, EINES DELIKTES "  \
	"ODER ANDERS IM ZUSAMMENHANG MIT DER SOFTWARE ODER SONSTIGER VERWENDUNG DER SOFTWARE ENTSTANDEN."

#define VERSION INTERNAL_VERSION "DE"
#define BUSY_NAME NAME ": tätig"
#define UPDATE_AVAILABLE_NAME NAME ": Aktualisierung vergübar"
#define INFORMATION "Informationen"
#define CLOSE "Program Schließen"
#define DESTROY "Program Zerstören"
#define WILL_IT_DESTROY "Wird's sich zerstören?"
#define UPDATE "Aktualisieren"
#define CHECKING_UPDATES "Aktualisierungen suchen"
#define DOWNLOADING "herunterladen"
#define VERSION_STR "Fassung"
#define UP_TO_DATE "Schon aktualisiert!"
#define UPDATE_READY "Aktualisierung heruntergeladen!"
#define MESSAGE_UPDATED "Änderungen werden bei dir nächsten Öffnung in Kraft sein."
#define E_UPDATE_INFO "Fehler beim Wiederherstellen der Informationen der Aktualisierung."
#define E_UPDATE_DOWNLOAD "Fehler beim Herunterladen der Aktualisierung."
#define PRERELEASE_VERSION "Die jetzt installierte Fassung ist ein Vorschau."
#define UPDATE_AVAILABLE_MESSAGE "Aktualisierung: den Tray-Menü benutzen um zu aktualisieren."
#define ABOUT_NAME "Über " NAME

#endif // LANG == 0 || 1

#endif // INITIALIZED_LOCALE
       // wxString::FromUTF8()