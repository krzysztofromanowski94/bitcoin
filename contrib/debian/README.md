
Debian
====================
This directory contains files used to package detkcoind/detkcoin-qt
for Debian-based Linux systems. If you compile detkcoind/detkcoin-qt yourself, there are some useful files here.

## detkcoin: URI support ##


detkcoin-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install detkcoin-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your detkcoin-qt binary to `/usr/bin`
and the `../../share/pixmaps/detkcoin128.png` to `/usr/share/pixmaps`

detkcoin-qt.protocol (KDE)

