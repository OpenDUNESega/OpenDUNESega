dosbox
python3 fix_asm_directives.py
asm68k /p link.s, out/out.bin
fixheadr.exe out/out.bin
timeout /t -1
