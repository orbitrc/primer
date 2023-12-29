Primer
========

A base C++ library collections for Application.

It contains DateTime, JSON, Unicode etc. all-in-one.

Perpose
-------

It is for providing syntactic sugars and abstract classes used in
applications. Primer doesn't care about performance until a
decent API is done.
This means that it is suitable for use in applications where
performance is not critical, which makes it unsuitable for use
in libraries.

Namespaces
----------

All Primer objects begin with `pr::` C++ namespace.

libprimer-core
--------------

The core implementation of Primer is written in Rust. This will be
built as a static library and included in Primer.

~~Primer's version is same as **libprimer-core**.~~

Before build Primer, you should build **libprimer-core**.

**libprimer-core** requires `cargo` command which is package manager for Rust.
Check it by,

```
$ cargo --version
```

Build
-----

To build, you need the following.

- C++ compiler (usually g++)
- GNU Make
- CMake
- pkg-config
- libdbus-1 with it's headers

For build,

### Old Instruction (Below 0.5.0)

```sh
$ make
```

### New Instruction

```sh
$ mkdir build
$ cd build
$ cmake \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=/usr \
    ..
$ make
```

For install,

```sh
$ sudo make install
```

### Arch Linux (old)

```sh
$ sudo make PREFIX=/usr install
```

### Ubuntu (old)

```sh
$ sudo make PREFIX=/usr LIBDIR=/lib/x86_64-linux-gnu install
```

