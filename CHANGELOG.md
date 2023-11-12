# Change Log

## [main] - 20xx-xx-xx

### Added

- ByteArray class.
- Unicode encoder class.
- Unicode decoder class.
- DBusMessage assignment operator.

### Changed

- Unicode::Scalar class now throws in constructor for invalid code point range.

### Fixed

- Errors in getter methods in Range are fixed.
- String from not null-terminated C-style string error fixed.
- DBusError broken error message fixed.


## [0.4.1] - 2023-09-10

### Added

### Changed

### Fixed

- Range start/end/exclusive methods.


## [0.4.0] - 2023-09-08

D-Bus API has been added but it's not complete and still experimental.
This is discouraged that using in product.

### Added

- String comparison functions.
- Vector sort method.
- HashMap class.
- std::hash for String type. For using as key of HashMap.
- Vector `c_ptr` method.

### Changed

- Vector `find` method now implemented.

### Fixed

- Unicode version to 15.0 which as it was.
