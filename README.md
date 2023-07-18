Primer
========

A base C++ library collections for Application.

It contains DateTime, JSON, Unicode etc. all-in-one.

Perpose
-------

It is for providing syntactic sugars and abstract classes used in
applications. Primer doesn't care about performance ultil a
decent API is done.
This means that it is suitable for use in applications where
performance is not critical, which makes it unsuitable for use
in libraries.

Namespaces
----------

All Primer objects begin with `pr::` C++ namespace.

libprimer-core
--------------

The core implementation of Primer is written in Rust. This is separated to
another library because of some limits.

Primer's version is same as **libprimer-core**.

Before build Primer, you should build **libprimer-core** and install.

**libprimer-core** requires `cargo` command which is package manager for Rust.
Check it by,

```
$ cargo --version
```

Build
-----

For build,

```sh
$ make
```

For install,

### Arch Linux

```sh
$ sudo make PREFIX=/usr install
```

