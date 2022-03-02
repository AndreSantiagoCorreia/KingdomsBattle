import argparse
from PIL import Image

argParser = argparse.ArgumentParser(description='convert a png file to mif format')
argParser.add_argument('inputPath', metavar='InPath', type=str, help='the path to input png file')
argParser.add_argument('outputPath', metavar='OutPath', type=str, help='the path to output mif file')
args = argParser.parse_args()
inputPath = args.inputPath
outputPath = args.outputPath

im = Image.open(inputPath)
pix = im.load()
hexDigits = len(hex(im.size[0] * im.size[1] - 1)) - 2

outFile = open(outputPath, 'w')
outFile.truncate(0)
outFile.write('DEPTH = ' + str(im.size[0] * im.size[1]) + ';\n')
outFile.write('WIDTH = 24;\nADDRESS_RADIX = HEX;\nDATA_RADIX = HEX;\nCONTENT\nBEGIN\n')
for x in range(im.size[1]):
    for y in range(im.size[0]):
        index = hex(x * im.size[1] + y)[2:].zfill(hexDigits)
        r = hex(pix[y,x][0])[2:].zfill(2)
        g = hex(pix[y,x][1])[2:].zfill(2)
        b = hex(pix[y,x][2])[2:].zfill(2)
        outFile.write(index + ' : ' + r + g + b + ';\n')
outFile.write('END;')