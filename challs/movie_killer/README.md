# Movie Killer

- Category: `forensics`
- Challenge author: **Robert Teir**

## Description

Our copycat movie killer has been using a shared computer to research cool movie quotes. We have an image of the computer; can you find out what his favorite quote is?.

## Writeup

1. Extract the bmp files from the rdp cahce with a tool like ANSSI's BMC-Tools (https://github.com/ANSSI-FR/bmc-tools)
2. Use a tool like RdpCacheStitcher to put the image back together (https://github.com/BSI-Bund/RdpCacheStitcher)