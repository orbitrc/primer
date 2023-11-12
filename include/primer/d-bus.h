#ifndef _PRIMER_D_BUS_H
#define _PRIMER_D_BUS_H

#include <stdint.h>

#include <exception>
#include <optional>
#include <memory>

#include <primer/string.h>
#include <primer/vector.h>

namespace pr {

class DBus
{
public:
    enum class BusType {
        Session,
        System,
    };

    enum class Type {
        Invalid,
        Byte,
        Int16,
        Uint16,
        Int32,
        Uint32,
        Int64,
        Uint64,
        Double,
        String,
        Boolean,
        Variant,
        Array,
        Struct,
        DictEntry,
    };

public:
    static const char* introspect_1_0_xml_doctype_decl_node();
};

class DBusError : public std::exception
{
public:
    DBusError(const char *message);

    const char* what() const noexcept;

private:
    pr::String _message;
};

class DBusVariant;

class DBusDictEntry;

class DBusArray
{
public:
    DBusArray();

    DBusArray(DBus::Type type);

    int32_t length() const;

    DBus::Type type() const;

    void push(int16_t value);

    void push(uint16_t value);

    void push(int32_t value);

    void push(uint32_t value);

    void push(int64_t value);

    void push(uint64_t value);

    void push(bool value);

    void push(const pr::String& value);

    void push(const pr::DBusVariant& value);

    void push(const pr::DBusDictEntry& value);

    /// Deprecated!
    template<typename T>
    const pr::Vector<T>& as_vector() const;

    template<typename T>
    pr::Vector<T> to_vector() const;

private:
    DBus::Type _type;

    pr::Vector<int64_t> _int_v;
    pr::Vector<uint64_t> _uint_v;
    pr::Vector<bool> _boolean_v;
    pr::Vector<pr::String> _string_v;
    pr::Vector<pr::DBusVariant> _variant_v;
    pr::Vector<pr::DBusDictEntry> _dict_entry_v;
};

class DBusVariant
{
public:
    /// Construct with type `Invalid`.
    DBusVariant();

    DBusVariant(DBus::Type type);

    DBusVariant(const pr::String& value);

    template<typename I>
    DBusVariant(I value);

    DBusVariant(bool value);

    DBusVariant(const pr::DBusArray& value);

    DBusVariant(const pr::DBusDictEntry& value);

    DBus::Type type() const;

    template<typename T>
    T value() const;

private:
    DBus::Type _type;

    pr::String _string;
    int64_t _int;
    uint64_t _uint;
    bool _boolean;
    pr::DBusArray _array;
    std::shared_ptr<pr::DBusDictEntry> _dict_entry;
};

class DBusDictEntry
{
public:
    DBusDictEntry();

    // DBusDictEntry(const DBusDictEntry& other);

    void set_key_type(DBus::Type type);
    void set_value_type(DBus::Type type);

    DBus::Type key_type() const;
    DBus::Type value_type() const;

    void set_key(const pr::String& k);
    template<typename I>
    void set_key(I k);
    void set_key(bool k);

    void set_value(const pr::String& v);
    template<typename I>
    void set_value(I v);
    void set_value(bool v);
    void set_value(const pr::DBusArray& v);
    void set_value(const pr::DBusVariant& v);

    /// Template getter for key.
    template<typename T>
    T key() const;

    /// Template getter for value.
    template<typename T>
    T value() const;

private:
    DBus::Type _key_type;
    DBus::Type _value_type;

    pr::String _key_string;
    int64_t _key_int;
    uint64_t _key_uint;
    bool _key_boolean;

    pr::String _value_string;
    int64_t _value_int;
    uint64_t _value_uint;
    bool _value_boolean;
    pr::DBusArray _value_array;
    pr::DBusVariant _value_variant;
};

/// A meta container for reply arguments. It can contains a plain type,
/// or a Variant type.
class DBusArgument
{
public:
    DBusArgument(DBus::Type type);

    DBusArgument(int16_t value);

    DBusArgument(uint16_t value);

    DBusArgument(int32_t value);

    DBusArgument(uint32_t value);

    DBusArgument(int64_t value);

    DBusArgument(uint64_t value);

    DBusArgument(const pr::String& value);

    DBusArgument(bool value);

    DBusArgument(const DBusVariant& value);

    DBusArgument(const DBusArray& value);

    DBus::Type type() const;

    template<typename T>
    T value() const;

private:
    DBus::Type _type;

    pr::String _string;
    int32_t _int32; // Deprecated!
    int64_t _int;
    uint64_t _uint;
    bool _boolean;
    DBusVariant _variant;
    DBusArray _array;
};

class DBusConnection;

class DBusMessage
{
    friend DBusConnection;
public:
    enum class Type {
        MethodCall,
        Signal,
    };

public:
    DBusMessage();

    DBusMessage(const DBusMessage& other);

    ~DBusMessage();

    pr::String interface() const;

    pr::String member() const;

    pr::String path() const;

    DBusMessage::Type type() const;

    DBusMessage new_method_return() const;

    DBusMessage new_signal(const pr::String& path,
                           const pr::String& interface,
                           const pr::String& name) const;

    pr::Vector<DBusArgument> arguments() const;

    bool append(const DBusVariant& variant);

    bool append(const pr::String& value);

    DBusMessage& operator=(const DBusMessage& other);

public:
    static DBusMessage new_method_call(const pr::String& dest,
                                       const pr::String& path,
                                       const pr::String& interface,
                                       const pr::String& method);

private:
    class Impl;

    Impl *_impl;
};

class DBusConnection
{
public:
    DBusConnection();

    DBusConnection(const DBusConnection& other);

    ~DBusConnection();

    bool request_name(const pr::String& name);

    bool read_write_dispatch(int32_t timeout = -1);

    /// Send message and get reply. Blocking mode. Timeout in milliseconds.
    /// Timeout -1 for default or infinite.
    /// It throws an exception on error.
    DBusMessage send_with_reply(const DBusMessage& message,
                                int32_t timeout = -1);

    std::optional<DBusMessage> pop_message();

    bool send(const DBusMessage& message) const;

    DBusConnection& operator=(const DBusConnection& other);

public:
    static DBusConnection bus_get(DBus::BusType bus_type);

private:
    class Impl;

    Impl *_impl;
};

} // namespace pr

#endif /* _PRIMER_D_BUS_H */
