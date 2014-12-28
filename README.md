rotary-device
=============

A platform hack to dynamically load/unload rotary encoder devices at runtime

Support 1 or 2 rotaries per board.

## Why?

Loads/unloads a rotary_encoder device at runtime using modprobe. Device Tree would be better, but Raspberry Pi default kernels don't use Device Tree, and I needed to use default Raspberry kernel configurations on this project.

## Building

There's a makfile. You'll want to override PATH and KDIR.

i.e
```sh
make KDIR=/path/to/kernel-sources PATH=$PATH:/path/to/arm-linux-gnueabi/toolchain
```


## Usage

Where A and B are the A and B signal lines

```sh
modprobe rotary_device rotary_1=a,b rotary_2=a',b'
```


## Limitations

This was a quick hack, so it doesn't support passing in all the parameters of the rotary_encoder module (i.e. steps, axis, relative_axis, inverted_a/b), but it could.

It also only supports 1 < n < 2 rotaries, but with some linked list stuff and some kzalloc it could support an indefinite number.

## Copyright

GNU GPL 2 

* (c) 2009 Daniel Mack <daniel@caiaq.de>
* Copyright (C) 2011 Johan Hovold <jhovold@gmail.com>
* Copyright (C) 2013, Noralf Tronnes
* Copyright (c) 2014 ken restivo <ken@restivo.org>

