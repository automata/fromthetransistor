# Assembler
- two-pass assembler: first passs builds the symbol table, second one generates machine code
- generates relocatable object files that then can be linked and loaded in memory at a base address
- all instructions are encoded in 32-bits
- currently no macros, no directives
- currently only outputs plain object (*.o*) files

# Resources
- [Assemblers](http://www.davidsalomon.name/assem.advertis/asl.pdf)
- [Structure of ARM assembly](https://developer.arm.com/documentation/dui0473/i/structure-of-assembly-language-modules?lang=en)
- [Linkers and Loaders](https://www.iecc.com/linker/)
- [Encodings](https://www.intel.com/content/dam/www/programmable/us/en/pdfs/literature/third-party/archives/ddi0100e_arm_arm.pdf)
- [Object/ELF files](http://www.sco.com/developers/gabi/latest/contents.html)
