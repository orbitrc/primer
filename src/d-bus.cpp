#include <primer/d-bus.h>

#include <dbus/dbus.h>

namespace pr {
DBus::Variant::Variant(DBus::Variant::Type type)
{
    this->_type = type;
}

DBus::Variant::Variant(const pr::String& value)
{
    this->_type = DBus::Variant::Type::String;
    this->_string = value;
}

DBus::Variant::Variant(int32_t value)
{
    this->_type = DBus::Variant::Type::Int32;
    this->_int32 = value;
}

DBus::Variant::Variant(bool value)
{
    this->_type = DBus::Variant::Type::Boolean;
    this->_boolean = value;
}

DBus::Variant::Type DBus::Variant::type() const
{
    return this->_type;
}

template<>
pr::String DBus::Variant::value<pr::String>() const
{
    return this->_string;
}

template<>
int32_t DBus::Variant::value<int32_t>() const
{
    return this->_int32;
}

template<>
bool DBus::Variant::value<bool>() const
{
    return this->_boolean;
}


const char* DBus::introspect_1_0_xml_doctype_decl_node()
{
    return DBUS_INTROSPECT_1_0_XML_DOCTYPE_DECL_NODE;
}


DBusError::DBusError(const char *message)
{
    this->_message = message;
}

const char* DBusError::what() const noexcept
{
    return (pr::String("D-Bus error: ") + this->_message).c_str();
}


class DBusConnection::Impl
{
public:
    ::DBusConnection *connection;
};


class DBusMessage::Impl
{
public:
    ::DBusMessage *message;
    uint32_t message_count;
};


DBusMessage::DBusMessage()
{
    this->_impl = new DBusMessage::Impl();
    this->_impl->message = nullptr;
    this->_impl->message_count = 1;
}

DBusMessage::DBusMessage(const DBusMessage& other)
{
    this->_impl = new DBusMessage::Impl();
    this->_impl->message = other._impl->message;
    this->_impl->message_count = other._impl->message_count + 1;
}

DBusMessage::~DBusMessage()
{
    this->_impl->message_count -= 1;
    if (this->_impl->message_count == 0) {
        dbus_message_unref(this->_impl->message);
    }
    delete this->_impl;
}

pr::String DBusMessage::interface() const
{
    const char *iface = dbus_message_get_interface(this->_impl->message);
    return pr::String(iface);
}

pr::String DBusMessage::member() const
{
    const char *member = dbus_message_get_member(this->_impl->message);
    if (member == NULL) {
        return ""_S;
    }

    return pr::String(member);
}

pr::String DBusMessage::path() const
{
    return pr::String(dbus_message_get_path(this->_impl->message));
}

DBusMessage DBusMessage::new_method_return() const
{
    ::DBusMessage *ret;
    ret = dbus_message_new_method_return(this->_impl->message);

    DBusMessage message;
    message._impl->message = ret;

    return message;
}

DBusMessage DBusMessage::new_signal(const pr::String& path,
                                    const pr::String& interface,
                                    const pr::String& name) const
{
    ::DBusMessage *sig = dbus_message_new_signal(path.c_str(),
        interface.c_str(),
        name.c_str());

    DBusMessage message;
    message._impl->message = sig;

    return message;
}

pr::Vector<DBus::Variant> DBusMessage::arguments() const
{
    pr::Vector<DBus::Variant> v;

    ::DBusMessageIter iter;
    dbus_message_iter_init(this->_impl->message, &iter);

    do {
        auto type = dbus_message_iter_get_arg_type(&iter);
        void *arg = nullptr;
        dbus_message_iter_get_basic(&iter, &arg);

        if (type == DBUS_TYPE_STRING) {
            v.push(pr::String(((const char*)arg)));
        } else {
            // TODO: Other types.
        }
    } while (dbus_message_iter_next(&iter));

    return v;
}

bool DBusMessage::append(const DBus::Variant& variant)
{
    DBusMessageIter iter;
    dbus_message_iter_init_append(this->_impl->message, &iter);

    const char *type_as_string = "";
    switch (variant.type()) {
    case DBus::Variant::Type::String:
        type_as_string = DBUS_TYPE_STRING_AS_STRING;
        break;
    case DBus::Variant::Type::Int32:
        type_as_string = DBUS_TYPE_INT32_AS_STRING;
        break;
    case DBus::Variant::Type::Boolean:
        type_as_string = DBUS_TYPE_BOOLEAN_AS_STRING;
        break;
    default:
        break;
    }

    DBusMessageIter variant_iter;
    dbus_message_iter_open_container(&iter,
        DBUS_TYPE_VARIANT, type_as_string,
        &variant_iter);

    if (variant.type() == DBus::Variant::Type::String) {
        auto string_value = variant.value<pr::String>();
        const char *c_str = string_value.c_str();
        dbus_message_iter_append_basic(&variant_iter,
            DBUS_TYPE_STRING, &c_str);
    } else if (variant.type() == DBus::Variant::Type::Int32) {
        auto int32_value = variant.value<int32_t>();
        dbus_message_iter_append_basic(&variant_iter,
            DBUS_TYPE_INT32, &int32_value);
    } else if (variant.type() == DBus::Variant::Type::Boolean) {
        auto boolean_value = variant.value<bool>();
        dbus_message_iter_append_basic(&variant_iter,
            DBUS_TYPE_BOOLEAN, &boolean_value);
    }

    dbus_message_iter_close_container(&iter, &variant_iter);

    return false;
}

bool DBusMessage::append(const pr::String& value)
{
    const char *c_str = value.c_str();
    auto result = dbus_message_append_args(this->_impl->message,
        DBUS_TYPE_STRING, &c_str,
        DBUS_TYPE_INVALID);

    if (!result) {
        return false;
    }

    return true;
}


DBusConnection::~DBusConnection()
{
    delete this->_impl;
}

bool DBusConnection::request_name(const pr::String& name)
{
    ::DBusError err;
    dbus_error_init(&err);

    dbus_bus_request_name(this->_impl->connection,
        name.c_str(), DBUS_NAME_FLAG_DO_NOT_QUEUE, &err);

    if (dbus_error_is_set(&err)) {
        return false;
    }

    return true;
}

bool DBusConnection::read_write_dispatch(int32_t timeout)
{
    auto result = dbus_connection_read_write_dispatch(this->_impl->connection,
        timeout);
    if (result) {
        return true;
    }

    return false;
}

DBusMessage DBusConnection::pop_message()
{
    ::DBusMessage *msg = dbus_connection_pop_message(this->_impl->connection);
    DBusMessage message;
    message._impl->message = msg;

    return message;
}

bool DBusConnection::send(const DBusMessage& message) const
{
    auto result = dbus_connection_send(this->_impl->connection,
        message._impl->message, NULL);
    dbus_connection_flush(this->_impl->connection);

    if (!result) {
        return false;
    }

    return true;
}


DBusConnection DBusConnection::bus_get(DBus::Type bus_type)
{
    DBusConnection conn;

    DBusBusType t;
    if (bus_type == DBus::Type::Session) {
        t = DBUS_BUS_SESSION;
    } else if (bus_type == DBus::Type::System) {
        t = DBUS_BUS_SYSTEM;
    } else {
        t = DBUS_BUS_SESSION;
    }

    ::DBusError err;
    dbus_error_init(&err);

    conn._impl = new DBusConnection::Impl();
    conn._impl->connection = dbus_bus_get(t, &err);

    if (dbus_error_is_set(&err)) {
        DBusError error(err.message);
        dbus_error_free(&err);
        throw error;
    }

    return conn;
}

} // namespace pr
