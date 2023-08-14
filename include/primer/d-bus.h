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
    enum class Type {
        Session,
        System,
    };

    class Variant
    {
    public:
        enum class Type {
            Int32,
            String,
            Boolean,
        };

    public:
        Variant(DBus::Variant::Type type);

        Variant(const pr::String& value);

        Variant(int32_t value);

        Variant(bool value);

        DBus::Variant::Type type() const;

        template<typename T>
        T value() const;

    private:
        DBus::Variant::Type _type;

        pr::String _string;
        int32_t _int32;
        bool _boolean;
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

    pr::Vector<DBus::Variant> arguments() const;

    bool append(const DBus::Variant& variant);

    bool append(const pr::String& value);

private:
    class Impl;

    Impl *_impl;
};

class DBusConnection
{
public:
    ~DBusConnection();

    bool request_name(const pr::String& name);

    bool read_write_dispatch(int32_t timeout = -1);

    std::optional<DBusMessage> pop_message();

    bool send(const DBusMessage& message) const;

public:
    static DBusConnection bus_get(DBus::Type bus_type);

private:
    class Impl;

    Impl *_impl;
};

} // namespace pr

#endif /* _PRIMER_D_BUS_H */
