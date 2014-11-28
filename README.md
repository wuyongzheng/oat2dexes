= Extracting .dex files from Android ART .oat/.odex files

== How it works?

DEX files are embeded in Android ART .oat/.odex files. `oat2dexes` looks for
DEX magic "dex\n035\0".

== How to use?

    $ gcc -o oat2dexes -Wall oat2dexes.c
    $ ./oat2dexes file.odex
    Writing 12345 bytes to dex01.dex
    $ java -jar baksmali.jar -o outdir dex01.dex
