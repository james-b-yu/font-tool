# Font Tool
## What?
Font Tool is a small utility to help people who operate on many workstations use their fonts in a portable way. This removes the necessity of having administrator privileges: the fonts are loaded into memory temporarily and are unloaded once the user logs off or closes the application. No changes to the disk are made, save for a small `fonts` file which acts as a database to store locations of added fonts.


## Why?
Font Tool has been designed especially with portability and ease of use in mind. The executable weighs in at only ~1MB, is statically-linked, operating within a single executable which can be renamed and placed anywhere, and makes no permanent changes to the computer. However, for the most portability, it is recommended to place the executable in a folder on the *same drive* as the user's font files to remove the dependency of a changing drive letter.

A minimal UI has been created to make it as easy as possible to load and unload fonts. One can load fonts by using the dedicated button, through drag-and-drop onto the window, through drag-and-drop onto the executable, as well as through a menu in the system tray for easy access. This vast array of methods is part of a struggle to make the application as intuitive to use as possible.

Although the application is not a font manager (see Why Not?), it tries display fonts in folders as they are arranged on the disk. Fonts can be revealed by activating their corresponding item in the tree view.

One aspect that makes this application much better for font loading than other font-loading applications, apart from its easy-to-use interface, is the multi-threaded approach to loading fonts. Instead of waiting `n * t` time for fonts to load, one must only wait `t` time as fonts are loaded in parallel, further boosting productivity and ease-of-use.