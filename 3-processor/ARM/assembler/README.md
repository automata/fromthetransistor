# Assembler
- two-pass assembler: first passs builds the symbol table, second one generated machine code
- generates relocatable object files that then can be linked and loaded in memory at a base address by a loader
- due the ARM's instruction encoding, determining the instruction sizes is straightforward since they're all 32 bits, regardless of the number of operands
- non-unique labels in symbol table leads to fatal errors
- missing labels are assumed to be resolved by the linker
- no macros, no directives (except linker directives) to keep things simple
- full static linking, no dynamic linking support (so all labels are linked at load time, hence resolved when the ELF file is generated)

## Labels
For:
- PC relative addresses
- for register relative addresses
- for absolute addresses

## Subroutine calls
```Assembly
bl <destination> ; <destination> = label for the first instruction of the subroutine
```
- **bl**: 
    - places the return address in the link register
    - sets the PC to the address of the subroutine


# Resources
- [Object/ELF files](http://www.sco.com/developers/gabi/latest/contents.html)
- [Linkers and Loaders](https://www.iecc.com/linker/)
- [Assemblers](http://www.davidsalomon.name/assem.advertis/asl.pdf)
- [Structure of ARM assembly](https://developer.arm.com/documentation/dui0473/i/structure-of-assembly-language-modules?lang=en)
- [Encodings](https://www.intel.com/content/dam/www/programmable/us/en/pdfs/literature/third-party/archives/ddi0100e_arm_arm.pdf)
