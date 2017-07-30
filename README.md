# TR2Draw by Arsunt

This is a dynamic library for the classic Tomb Raider II game (Windows version). The purpose of the library is to implement all the graphics procedures performed by the game. In this case, the game reserves the control of the basic logic and other algorithms. This is not a wrapper, it's a full-fledged solution that solves a bunch of compatibility issues, and also allows to natively improve the game's graphics, and even easily translate it to any other 3D engine.

At the moment, only part of the library is on the repository. It has the implementation of the inventory wallpaper rendering. Nevertheless, the code includes a previously unpublished feature - animated waving wallpaper for the PlayStation Tomb Raider II. This fragment of the source code is completely recreated with the help of assembler and many weeks of routine work.

The goal of this project is to maximally recreate the code of the original game, gradually transferring its various aspects to dynamic libraries that are linked to the modified original EXE. In this case, main code remains in the game, but graphics, sounds and controls will be in the separate DLL files.

[Here](http://www.tombraiderforums.com/showthread.php?p=7770487) you can read article about how it works.

## Getting Started

Sorry, there is no simple way to link this DLL with your TR2 game EXE. Until now, I've written all the interfaces in my copy of the game directly in assembler. With the release of the modified game you will have the opportunity to fully test this library. This is just code demo right now.

## Built With

* [Code::Blocks](http://www.codeblocks.org) - C/C++ IDE used
* [lcc-win32](https://www.cs.virginia.edu/~lcc-win32/) - C/C++ compiler
* [Doxygen](http://www.doxygen.org) - documentation

## Authors

* **Michael Chaban** \([Arsunt](https://github.com/Arsunt)\). E-mail: (arsunt@gmail.com)

## License

This project is licensed under the GNU General Public License - see the [COPYING.md](COPYING.md) file for details

## Acknowledgments

If you are inspired by my project and decided to borrow some of the ideas found in the code, do not forget to specify my name. It took me years to decompile and understand the details necessary for this project. Thank you for understanding!
