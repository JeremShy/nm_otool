ft_nm:
Mach header
      magic cputype cpusubtype  caps    filetype ncmds sizeofcmds      flags
 0xfeedfacf 16777223          3  0x80           2    15       1360 0x00200085
Load command 0
      cmd LC_SEGMENT_64
  cmdsize 72
  segname __PAGEZERO
   vmaddr 0x0000000000000000
   vmsize 0x0000000100000000
  fileoff 0
 filesize 0
  maxprot 0x00000000
 initprot 0x00000000
   nsects 0
    flags 0x0
Load command 1
      cmd LC_SEGMENT_64
  cmdsize 552
  segname __TEXT
   vmaddr 0x0000000100000000
   vmsize 0x0000000000008000
  fileoff 0
 filesize 32768
  maxprot 0x00000007
 initprot 0x00000005
   nsects 6
    flags 0x0
Section
  sectname __text
   segname __TEXT
      addr 0x0000000100000930
      size 0x000000000000746c
    offset 2352
     align 2^4 (16)
    reloff 0
    nreloc 0
     flags 0x80000400
 reserved1 0
 reserved2 0
Section
  sectname __stubs
   segname __TEXT
      addr 0x0000000100007d9c
      size 0x000000000000003c
    offset 32156
     align 2^1 (2)
    reloff 0
    nreloc 0
     flags 0x80000408
 reserved1 0 (index into indirect symbol table)
 reserved2 6 (size of stubs)
Section
  sectname __stub_helper
   segname __TEXT
      addr 0x0000000100007dd8
      size 0x0000000000000074
    offset 32216
     align 2^2 (4)
    reloff 0
    nreloc 0
     flags 0x80000400
 reserved1 0
 reserved2 0
Section
  sectname __cstring
   segname __TEXT
      addr 0x0000000100007e4c
      size 0x0000000000000161
    offset 32332
     align 2^0 (1)
    reloff 0
    nreloc 0
     flags 0x00000002
 reserved1 0
 reserved2 0
Section
  sectname __const
   segname __TEXT
      addr 0x0000000100007fad
      size 0x0000000000000002
    offset 32685
     align 2^0 (1)
    reloff 0
    nreloc 0
     flags 0x00000000
 reserved1 0
 reserved2 0
Section
  sectname __unwind_info
   segname __TEXT
      addr 0x0000000100007fb0
      size 0x0000000000000048
    offset 32688
     align 2^2 (4)
    reloff 0
    nreloc 0
     flags 0x00000000
 reserved1 0
 reserved2 0
Load command 2
      cmd LC_SEGMENT_64
  cmdsize 312
  segname __DATA
   vmaddr 0x0000000100008000
   vmsize 0x0000000000001000
  fileoff 32768
 filesize 4096
  maxprot 0x00000007
 initprot 0x00000003
   nsects 3
    flags 0x0
Section
  sectname __got
   segname __DATA
      addr 0x0000000100008000
      size 0x0000000000000008
    offset 32768
     align 2^3 (8)
    reloff 0
    nreloc 0
     flags 0x00000006
 reserved1 10 (index into indirect symbol table)
 reserved2 0
Section
  sectname __nl_symbol_ptr
   segname __DATA
      addr 0x0000000100008008
      size 0x0000000000000010
    offset 32776
     align 2^3 (8)
    reloff 0
    nreloc 0
     flags 0x00000006
 reserved1 11 (index into indirect symbol table)
 reserved2 0
Section
  sectname __la_symbol_ptr
   segname __DATA
      addr 0x0000000100008018
      size 0x0000000000000050
    offset 32792
     align 2^3 (8)
    reloff 0
    nreloc 0
     flags 0x00000007
 reserved1 13 (index into indirect symbol table)
 reserved2 0
Load command 3
      cmd LC_SEGMENT_64
  cmdsize 72
  segname __LINKEDIT
   vmaddr 0x0000000100009000
   vmsize 0x0000000000003000
  fileoff 36864
 filesize 12196
  maxprot 0x00000007
 initprot 0x00000001
   nsects 0
    flags 0x0
Load command 4
            cmd LC_DYLD_INFO_ONLY
        cmdsize 48
     rebase_off 36864
    rebase_size 8
       bind_off 36872
      bind_size 48
  weak_bind_off 0
 weak_bind_size 0
  lazy_bind_off 36920
 lazy_bind_size 152
     export_off 37072
    export_size 1400
Load command 5
     cmd LC_SYMTAB
 cmdsize 24
  symoff 38664
   nsyms 384
  stroff 44900
 strsize 4160
Load command 6
            cmd LC_DYSYMTAB
        cmdsize 80
      ilocalsym 0
      nlocalsym 290
     iextdefsym 290
     nextdefsym 82
      iundefsym 372
      nundefsym 12
         tocoff 0
           ntoc 0
      modtaboff 0
        nmodtab 0
   extrefsymoff 0
    nextrefsyms 0
 indirectsymoff 44808
  nindirectsyms 23
      extreloff 0
        nextrel 0
      locreloff 0
        nlocrel 0
Load command 7
          cmd LC_LOAD_DYLINKER
      cmdsize 32
         name /usr/lib/dyld (offset 12)
Load command 8
     cmd LC_UUID
 cmdsize 24
    uuid DFA8A7AA-6651-3806-8C4C-A2D2025CC509
Load command 9
      cmd LC_VERSION_MIN_MACOSX
  cmdsize 16
  version 10.11
      sdk 10.11
Load command 10
      cmd LC_SOURCE_VERSION
  cmdsize 16
  version 0.0
Load command 11
       cmd LC_MAIN
   cmdsize 24
  entryoff 2704
 stacksize 0
Load command 12
          cmd LC_LOAD_DYLIB
      cmdsize 56
         name /usr/lib/libSystem.B.dylib (offset 24)
   time stamp 2 Thu Jan  1 01:00:02 1970
      current version 1226.10.1
compatibility version 1.0.0
Load command 13
      cmd LC_FUNCTION_STARTS
  cmdsize 16
  dataoff 38472
 datasize 192
Load command 14
      cmd LC_DATA_IN_CODE
  cmdsize 16
  dataoff 38664
 datasize 0
