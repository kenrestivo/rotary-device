rotary-device
=============

A platform hack to dynamically load/unload [rotary encoder](https://www.kernel.org/doc/Documentation/input/rotary-encoder.txt) devices at runtime, inspired by [fbtft_device](https://github.com/notro/fbtft/wiki/fbtft_device "fbtft_device").

Supports 1 or 2 rotaries per board.

Does not set pullups; you have to do that separately using an external tool like gpio.

## Why?

Loads/unloads a rotary_encoder device at runtime using modprobe. Device Tree would be better, but Raspberry Pi kernels don't use Device Tree by default, and I didn't have the option to experiment with DT on Pi for this project.

## Building

There's a makfile. You'll want to override PATH and KDIR.

i.e
```sh
make KDIR=/path/to/kernel-sources PATH=$PATH:/path/to/arm-linux-gnueabi/toolchain
```


## Usage

Where 'a' and 'b' are the GPIO signal lines, and rotary_2 is optional:

```sh
modprobe rotary_device rotary_1=a,b [rotary_2=a2,b2]
```



## Limitations

This was a quick hack, so it doesn't support passing in all the parameters of the rotary_encoder module (i.e. steps, axis, relative_axis, inverted_a/b), but it could.

It also only supports 0 < n < 2 rotaries, but with some linked list stuff and some kzalloc it could support an indefinite number.

## Copyright

GNU GPL 2 

* (c) 2009 Daniel Mack <daniel@caiaq.de>
* Copyright (C) 2011 Johan Hovold <jhovold@gmail.com>
* Copyright (C) 2013, Noralf Tronnes
* Copyright (c) 2014 ken restivo <ken@restivo.org>

