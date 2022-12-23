#!/usr/bin/python3
import sys, os

infilename = sys.argv[1]
outfilename = 'temp'

infile = open(infilename)
outfile = open(outfilename, 'w')

for line in infile:
    if ((line.find('fp_text reference') != -1) or (line.find('fp_text value') != -1)) and (line.find('hide') == -1):
        outfile.write('{} hide\n'.format(line.rstrip()))
    else:
        outfile.write(line)

infile.close()
outfile.close()

