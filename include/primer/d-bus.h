#ifndef _PRIMER_D_BUS_H
#define _PRIMER_D_BUS_H

#include <stdint.h>

#include <exception>
#include <optional>

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
        Int32,
        String,
        Boolean,
        Variant,
    };

    class Variant;

    class Array
    {
    public:
        Array();

    private:
        DBus::Type _type;

        pr::Vector<int32_t> _int32_v;
        pr::Vector<bool> _boolean_v;
        pr::Vector<pr::String> _string_v;
        pr::Vector<pr::DBus::Variant> _variant_v;
    };

    class Variant
    {
    public:
        /// Construct with type `Invalid`.
        Variant();

        Variant(DBus::Type type);

        Variant(const pr::String& value);

        Variant(int32_t value);

        Variant(bool value);

        DBus::Type type() const;

        template<typename T>
        T value() const;

    private:
        DBus::Type _type;

        pr::String _string;
        int32_t _int32;
        bool _boolean;
    };

    template<typename K, typename V>
    class DictEntry
    {
    public:
        DictEntry(const K& key, const V& value)
        {
            this->_key = key;
            this->_value = value;
        }

    private:
        K _key;
        V _value;
    };

    /// A meta container for reply arguments. It can contains a plain type,
    /// or a Variant type.
    class Argument
    {
    public:
        Argument(DBus::Type type);

        Argument(int32_t value);

        Argument(const pr::String& value);

        Argument(bool value);

        Argument(const Variant& value);

        DBus::Type type() const;

        template<typename T>
        T value() const;

    private:
        DBus::Type _type;

        pr::String _string;
        int32_t _int32;
        bool _boolean;
        Variant _variant;
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

    pr::Vector<DBus::Argument> arguments() const;

    bool append(const DBus::Variant& variant);

    bool append(const pr::String& value);

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
