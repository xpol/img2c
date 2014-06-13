# Image to C Array Util

[![Build Status](https://travis-ci.org/xpol/img2c.png)](https://travis-ci.org/xpol/img2c)

Converts a image to C array.

## Build

```
cmake -H. -Bbuild
cmake --build build --target img2c --config Release
```

## Usage

```
img2c (RGB565|RGBA4444) <FILE> > <OUTPUT>.c
```

Eg. `img2c RGB565 bg.png > bg.c`
