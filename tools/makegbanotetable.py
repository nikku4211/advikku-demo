#!/usr/bin/env python3
#
# Lookup table generator for Concentration Room
# Copyright 2010 Damian Yerrick
#
# Copying and distribution of this file, with or without
# modification, are permitted in any medium without royalty
# provided the copyright notice and this notice are preserved.
# This file is offered as-is, without any warranty.
#
from __future__ import with_statement, division, print_function
import sys

GBAClockFreq = 16777216
GBAPSGClockFreq = 131072

def generatePeriodTable (filename, maxoctave=8):
    # tracker musicians would know 65 as C-2
    etfrequencies = [65 * (1.05946**i) for i in range(12*maxoctave)]
    etdmaperiods = [round(65536 - (GBAClockFreq) / (etfrequencies[i]*32)) for i in range(12*maxoctave)]
    etpsgperiods = [round(2048 - (GBAPSGClockFreq) / (etfrequencies[i])) for i in range(12*maxoctave)]
    systemName = "GBA"
    with open(filename, 'wt') as outfp:
        outfp.write("""//generated by Nikku4211's makegbanotetable.py
const uint16_t snd_freqs[]=
{
""")
        for i in range(maxoctave):
            outfp.write('   '+','.join('0x%04x' % (i)
                                   for i in etpsgperiods[i*12:(i*12)+12])
                        + ',\n')
        outfp.write("""};\n""")
        outfp.write("""//also generated by Nikku4211's makegbanotetable.py
const uint16_t dma_snd_freqs[]=
{
""")
        for i in range(maxoctave):
            outfp.write('   '+','.join('0x%04x' % (i)
                                   for i in etdmaperiods[i*12:(i*12)+12])
                        + ',\n')
        outfp.write("""};""")
    
    return etdmaperiods

def main(argv):
    if len(argv) >= 2 and argv[1] in ('/?', '-?', '-h', '--help'):
        print("usage: %s FILENAME" % argv[0])
    elif len(argv) < 2:
        print("mktables: too few arguments; try %s --help" % argv[0],
              file=sys.stderr)
        sys.exit(1)
    else:
        generatePeriodTable(argv[1])
    

if __name__=='__main__':
    main(sys.argv)