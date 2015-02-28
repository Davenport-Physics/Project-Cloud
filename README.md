Project Cloud
=============

Description
-----------

Project Cloud is an ascii based roleplaying game, that hearken backs to the days of old, where rpgs were incredibly complex and in depth experiences. However, there will also be the inclusion of more modern gameplay mechanics that add to the overall experience of playing a character.

This code is released under the GPL v2, which will hopefully facilitate community interaction with the game as it becomes closer to release. However this is not the primary motivation to releasing the game under a free software license. The motivation stems from an inherent frustration with the state of contemporary corporate negligence when it comes to older titles. They no longer support an older title for obvious reasons, however at the same time, they don't release the source code so that players who still enjoy their video games can fix any flaws left behind. Releasing the primary components of this game under the GPL v2 will allow players years from now to make the game they loved, even better than it was before.

This project has goals to an eventual commercial release as paid software. With that in mind, there are some components that will have to be bought such as music, levels, campaigns etc. However the primary component, the glue if you will, is released under GPL. So anyone may be able to purchase the complete package online, or make their own package and release it for free. The choice is up to you.


Dependencies
------------

SDL2

SDL2_mixer

SDL2_ttf

Sqlite3 (This dependency may be removed later on however)


Build Instructions
------------------

I have provided a make file which will hopefully allow for easy compilation. The dependencies listed above need to have their respective development packages installed in your current system in order to build properly.

cd Src

make

From here you'll want to copy the executable to the above directory. Make sure you have the following directories created

Data/Saves

Data/Music

Data/Fonts

from here you should be able to run the game fine.
