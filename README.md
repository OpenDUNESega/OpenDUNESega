### About

OpenDUNESega is an open source re-creation of the game "Dune: The Battle for Arrakis" released for Sega Genesis and Sega Mega Drive.
OpenDUNESega is a project analogous to [OpenDUNE](https://github.com/OpenDUNE/OpenDUNE) and is heavily influenced by it.
The source code of [OpenDUNE](https://github.com/OpenDUNE/OpenDUNE) and Sega version of the original game seems to be slightly different and most of the functions and structures need to be adjusted.

### How to build

Place Dune ROM version `1.5-030394` (to check your version enter VERSIONNUM at the password screen) at `bin/dune.bin`.
Place [com68.exe](https://segaretro.org/Sierra_68000_C_Compiler), [asm68k.exe](https://github.com/sonicretro/s1disasm) and [fixheadr.exe](https://github.com/sonicretro/s1disasm) in your project root directory.
Install `python3`.
Download and unpack `DOSBox`. Add the path to `DOSBox.exe` to your Windows PATH variable. Start `DOSBox Options` (or open `dosbox.conf` manually) and paste the following lines at the end of the file:
```
MOUNT C D:\Project\Root\Directory
C:
com68 link.c out\out.s
```
Run `build.bat`. The resulting binary should be `out/out.bin`.
