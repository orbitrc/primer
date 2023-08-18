#include <primer/d-bus.h>

#include <stdio.h> // REMOVE AFTER DEBUG!!!!

#include <type_traits>

#include <dbus/dbus.h>

namespace pr {

DBusArray::DBusArray()
{
    this->_type = DBus::Type::Invalid;
}

DBusArray::DBusArray(DBus::Type type)
{
    this->_type = type;
}

int32_t DBusArray::length() const
{
    switch (this->_type) {
    case DBus::Type::Int32:
        return this->_int_v.length();
        break;
    case DBus::Type::String:
        return this->_string_v.length();
        break;
    case DBus::Type::Boolean:
        return this->_boolean_v.length();
        break;
    case DBus::Type::Variant:
        return this->_variant_v.length();
        break;
    case DBus::Type::Array:
    case DBus::Type::Invalid:
    default:
        return 0;
    }
}

DBus::Type DBusArray::type() const
{
    return this->_type;
}

void DBusArray::push(int16_t value)
{
    this->_int_v.push(value);
}

void DBusArray::push(uint16_t value)
{
    this->_uint_v.push(value);
}

void DBusArray::push(int32_t value)
{
    this->_int_v.push(value);
}

void DBusArray::push(uint32_t value)
{
    this->_uint_v.push(value);
}

void DBusArray::push(int64_t value)
{
    this->_int_v.push(value);
}

void DBusArray::push(uint64_t value)
{
    this->_uint_v.push(value);
}

void DBusArray::push(bool value)
{
    this->_boolean_v.push(value);
}

void DBusArray::push(const pr::String& value)
{
    this->_string_v.push(value);
}

void DBusArray::push(const pr::DBusVariant& value)
{
    this->_variant_v.push(value);
}

template<>
const pr::Vector<bool>& DBusArray::as_vector() const
{
    return this->_boolean_v;
}

template<>
const pr::Vector<pr::String>& DBusArray::as_vector() const
{
    return this->_string_v;
}

template<>
const pr::Vector<pr::DBusVariant>& DBusArray::as_vector() const
{
    return this->_variant_v;
}

/// Convert a Vector of int64_t or uint64_t to target type.
template<typename Source, typename Target>
pr::Vector<Target> i_vector_convert(const pr::Vector<Source>& origin)
{
    pr::Vector<Target> v;

    for (auto& i: origin) {
        v.push(static_cast<Target>(i));
    }

    return v;
}

template<>
pr::Vector<int16_t> DBusArray::to_vector() const
{
    // Note: Map method returning different template type?
    /*
    auto v = this->_int_v.map([](int64_t i) {
        return static_cast<int16_t>(i);
    });
    */

    return i_vector_convert<int64_t, int16_t>(this->_int_v);
}

template<>
pr::Vector<uint16_t> DBusArray::to_vector() const
{
    return i_vector_convert<uint64_t, uint16_t>(this->_uint_v);
}

template<>
pr::Vector<int32_t> DBusArray::to_vector() const
{
    return i_vector_convert<int64_t, int32_t>(this->_int_v);
}

template<>
pr::Vector<uint32_t> DBusArray::to_vector() const
{
    return i_vector_convert<uint64_t, uint32_t>(this->_uint_v);
}

template<>
pr::Vector<int64_t> DBusArray::to_vector() const
{
    return this->_int_v;
}

template<>
pr::Vector<uint64_t> DBusArray::to_vector() const
{
    return this->_uint_v;
}


DBusVariant::DBusVariant()
{
    this->_type = DBus::Type::Invalid;
}

DBusVariant::DBusVariant(DBus::Type type)
{
    this->_type = type;
}

DBusVariant::DBusVariant(const pr::String& value)
{
    this->_type = DBus::Type::String;
    this->_string = value;
}

template<>
DBusVariant::DBusVariant(int16_t value)
{
    this->_type = DBus::Type::Int16;
    this->_int = value;
}

template<>
DBusVariant::DBusVariant(uint16_t value)
{
    this->_type = DBus::Type::Uint16;
    this->_uint = value;
}

template<>
DBusVariant::DBusVariant(int32_t value)
{
    this->_type = DBus::Type::Int32;
    this->_int = value;
}

template<>
DBusVariant::DBusVariant(uint32_t value)
{
    this->_type = DBus::Type::Uint32;
    this->_uint = value;
}

template<>
DBusVariant::DBusVariant(int64_t value)
{
    this->_type = DBus::Type::Int64;
    this->_int = value;
}

template<>
DBusVariant::DBusVariant(uint64_t value)
{
    this->_type = DBus::Type::Uint64;
    this->_uint = value;
}

DBusVariant::DBusVariant(bool value)
{
    this->_type = DBus::Type::Boolean;
    this->_boolean = value;
}

DBusVariant::DBusVariant(const pr::DBusArray& value)
{
    this->_type = DBus::Type::Array;
    this->_array = value;
}

DBus::Type DBusVariant::type() const
{
    return this->_type;
}

template<>
pr::String DBusVariant::value<pr::String>() const
{
    return this->_string;
}

template<>
int16_t DBusVariant::value() const
{
    return static_cast<int16_t>(this->_int);
}

template<>
uint16_t DBusVariant::value() const
{
    return static_cast<uint16_t>(this->_uint);
}

template<>
int32_t DBusVariant::value() const
{
    return static_cast<int32_t>(this->_int);
}

template<>
uint32_t DBusVariant::value() const
{
    return static_cast<uint32_t>(this->_uint);
}

template<>
int64_t DBusVariant::value() const
{
    return this->_int;
}

template<>
uint64_t DBusVariant::value() const
{
    return this->_uint;
}

template<>
bool DBusVariant::value<bool>() const
{
    return this->_boolean;
}

template<>
DBusArray DBusVariant::value<DBusArray>() const
{
    return this->_array;
}

template<>
DBusDictEntry DBusVariant::value<DBusDictEntry>() const
{
    return *(this->_dict_entry);
}


DBusDictEntry::DBusDictEntry()
{
    this->_key_type = DBus::Type::Invalid;
    this->_value_type = DBus::Type::Invalid;
}

void DBusDictEntry::set_key_type(DBus::Type type)
{
    this->_key_type = type;
}

void DBusDictEntry::set_value_type(DBus::Type type)
{
    this->_value_type = type;
}

DBus::Type DBusDictEntry::key_type() const
{
    return this->_key_type;
}

DBus::Type DBusDictEntry::value_type() const
{
    return this->_value_type;
}

void DBusDictEntry::set_key(const pr::String& k)
{
    this->_key_string = k;
}

template<typename I>
void DBusDictEntry::set_key(I k)
{
    if (std::is_signed<I>::value) {
        this->_key_int = k;
    } else {
        this->_key_uint = k;
    }
}

template void DBusDictEntry::set_key(int16_t k);
template void DBusDictEntry::set_key(uint16_t k);
template void DBusDictEntry::set_key(int32_t k);
template void DBusDictEntry::set_key(uint32_t k);
template void DBusDictEntry::set_key(int64_t k);
template void DBusDictEntry::set_key(uint64_t k);

void DBusDictEntry::set_key(bool k)
{
    this->_key_boolean = k;
}

void DBusDictEntry::set_value(const pr::String& v)
{
    this->_value_string = v;
}

void DBusDictEntry::set_value(bool v)
{
    this->_value_boolean = v;
}

template<typename I>
void DBusDictEntry::set_value(I v)
{
    if (std::is_signed<I>::value) {
        this->_value_int = v;
    } else {
        this->_value_uint = v;
    }
}

template void DBusDictEntry::set_value(int16_t v);
template void DBusDictEntry::set_value(uint16_t v);
template void DBusDictEntry::set_value(int32_t v);
template void DBusDictEntry::set_value(uint32_t v);
template void DBusDictEntry::set_value(int64_t v);
template void DBusDictEntry::set_value(uint64_t v);

void DBusDictEntry::set_value(const DBusArray& v)
{
    this->_value_array = v;
}

void DBusDictEntry::set_value(const DBusVariant& v)
{
    this->_value_variant = v;
}

template<>
pr::String DBusDictEntry::key() const
{
    return this->_key_string;
}


DBusArgument::DBusArgument(DBus::Type type)
{
    this->_type = type;
}

DBusArgument::DBusArgument(int32_t value)
{
    this->_type = DBus::Type::Int32;
    this->_int32 = value;
}

DBusArgument::DBusArgument(const pr::String& value)
{
    this->_type = DBus::Type::String;
    this->_string = value;
}

DBusArgument::DBusArgument(bool value)
{
    this->_type = DBus::Type::Boolean;
    this->_boolean = value;
}

DBusArgument::DBusArgument(const DBusVariant& value)
{
    this->_type = DBus::Type::Variant;
    this->_variant = value;
}

template<>
int32_t DBusArgument::value() const
{
    return this->_int32;
}

template<>
pr::String DBusArgument::value() const
{
    return this->_string;
}

template<>
bool DBusArgument::value() const
{
    return this->_boolean;
}

template<>
DBusVariant DBusArgument::value() const
{
    return this->_variant;
}

DBus::Type DBusArgument::type() const
{
    return this->_type;
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
    /*
    if (this->_impl->message_count == 0) {
        dbus_message_unref(this->_impl->message);
    }
    */
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

DBusMessage::Type DBusMessage::type() const
{
    auto t = dbus_message_get_type(this->_impl->message);

    if (t == DBUS_MESSAGE_TYPE_METHOD_CALL) {
        return DBusMessage::Type::MethodCall;
    } else if (t == DBUS_MESSAGE_TYPE_SIGNAL) {
        return DBusMessage::Type::Signal;
    }

    return DBusMessage::Type::MethodCall; // TODO: Must invalid type.
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

static DBusArray _process_array(::DBusMessageIter *iter)
{
    DBusArray array;

    auto type = dbus_message_iter_get_element_type(iter);
    auto len = dbus_message_iter_get_element_count(iter);

    ::DBusMessageIter array_iter;
    dbus_message_iter_recurse(iter, &array_iter);

    if (type == DBUS_TYPE_INT32) {
        array = DBusArray(DBus::Type::Int32);
        void *value;
        for (int i = 0; i < len; ++i) {
            dbus_message_iter_get_basic(&array_iter, &value);
            array.push(*(static_cast<int32_t*>(value)));
            dbus_message_iter_next(&array_iter);
        }
    } else if (type == DBUS_TYPE_STRING) {
        array = DBusArray(DBus::Type::String);
        void *value;
        for (int i = 0; i < len; ++i) {
            dbus_message_iter_get_basic(&array_iter, &value);
            array.push(pr::String(static_cast<const char*>(value)));
            dbus_message_iter_next(&array_iter);
        }
    } else if (type == DBUS_TYPE_BOOLEAN) {
        array = DBusArray(DBus::Type::Boolean);
        void *value;
        for (int i = 0; i < len; ++i) {
            dbus_message_iter_get_basic(&array_iter, &value);
            array.push(static_cast<bool>(*(static_cast<int32_t*>(value))));
            dbus_message_iter_next(&array_iter);
        }
    }

    return array;
}

static DBusVariant _process_variant(::DBusMessageIter *iter)
{
    auto variant_type = dbus_message_iter_get_arg_type(iter);
    if (variant_type == DBUS_TYPE_INT32) {
        void *value;
        dbus_message_iter_get_basic(iter, &value);
        DBusVariant variant(*(static_cast<int32_t*>(value)));
        return variant;
    } else if (variant_type == DBUS_TYPE_STRING) {
        void *value;
        dbus_message_iter_get_basic(iter, &value);
        DBusVariant variant(pr::String(static_cast<const char*>(value)));
        return variant;
    } else if (variant_type == DBUS_TYPE_BOOLEAN) {
        void *value;
        dbus_message_iter_get_basic(iter, &value);
        bool bool_value = (*(static_cast<int32_t*>(value)));
        DBusVariant variant(bool_value);
        return variant;
    } else if (variant_type == DBUS_TYPE_ARRAY) {
        DBusArray array = _process_array(iter);
        DBusVariant variant(array);
        return variant;
    }

    return DBusVariant();
}

pr::Vector<DBusArgument> DBusMessage::arguments() const
{
    pr::Vector<DBusArgument> v;

    ::DBusMessageIter iter;
    dbus_message_iter_init(this->_impl->message, &iter);

    do {
        auto type = dbus_message_iter_get_arg_type(&iter);

        if (type == DBUS_TYPE_STRING) {
            void *arg = nullptr;
            dbus_message_iter_get_basic(&iter, &arg);
            v.push(pr::String(((const char*)arg)));
        } else if (type == DBUS_TYPE_VARIANT) {
            ::DBusMessageIter variant_iter;
            dbus_message_iter_recurse(&iter, &variant_iter);
            DBusVariant variant = _process_variant(&variant_iter);
            v.push(variant);
        } else if (type == DBUS_TYPE_BOOLEAN) {
            void *arg = nullptr;
            dbus_message_iter_get_basic(&iter, &arg);
            v.push(DBusArgument(*(static_cast<bool*>(arg))));
        } else if (type == DBUS_TYPE_ARRAY) {
            DBusArray array = _process_array(&iter);
            v.push(DBusArgument(array));
        } else {
            // TODO: Other types.
        }
    } while (dbus_message_iter_next(&iter));

    return v;
}

bool DBusMessage::append(const DBusVariant& variant)
{
    DBusMessageIter iter;
    dbus_message_iter_init_append(this->_impl->message, &iter);

    const char *type_as_string = "";
    switch (variant.type()) {
    case DBus::Type::String:
        type_as_string = DBUS_TYPE_STRING_AS_STRING;
        break;
    case DBus::Type::Int32:
        type_as_string = DBUS_TYPE_INT32_AS_STRING;
        break;
    case DBus::Type::Boolean:
        type_as_string = DBUS_TYPE_BOOLEAN_AS_STRING;
        break;
    default:
        break;
    }

    DBusMessageIter variant_iter;
    dbus_message_iter_open_container(&iter,
        DBUS_TYPE_VARIANT, type_as_string,
        &variant_iter);

    if (variant.type() == DBus::Type::String) {
        auto string_value = variant.value<pr::String>();
        const char *c_str = string_value.c_str();
        dbus_message_iter_append_basic(&variant_iter,
            DBUS_TYPE_STRING, &c_str);
    } else if (variant.type() == DBus::Type::Int32) {
        auto int32_value = variant.value<int32_t>();
        dbus_message_iter_append_basic(&variant_iter,
            DBUS_TYPE_INT32, &int32_value);
    } else if (variant.type() == DBus::Type::Boolean) {
        auto boolean_value = static_cast<int>(variant.value<bool>());
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

DBusMessage DBusMessage::new_method_call(const pr::String& dest,
                                         const pr::String& path,
                                         const pr::String& interface,
                                         const pr::String& method)
{
    DBusMessage message;

    ::DBusMessage *msg = dbus_message_new_method_call(
        dest.c_str(), path.c_str(), interface.c_str(), method.c_str());

    message._impl->message = msg;

    return message;
}


DBusConnection::DBusConnection()
{
    this->_impl = new DBusConnection::Impl();
}

DBusConnection::DBusConnection(const DBusConnection& other)
{
    this->_impl = new DBusConnection::Impl();
    this->_impl->connection = other._impl->connection;
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

DBusMessage DBusConnection::send_with_reply(const DBusMessage& message,
                                            int32_t timeout)
{
    ::DBusError err;
    dbus_error_init(&err);

    ::DBusMessage *msg = dbus_connection_send_with_reply_and_block(
        this->_impl->connection, message._impl->message, timeout, &err);

    if (dbus_error_is_set(&err)) {
        pr::String error_message = err.message;
        dbus_error_free(&err);
        throw DBusError(error_message.c_str());
    }

    DBusMessage reply;
    reply._impl->message = msg;

    return reply;
}

std::optional<DBusMessage> DBusConnection::pop_message()
{
    ::DBusMessage *msg = dbus_connection_pop_message(this->_impl->connection);
    if (msg == NULL) {
        return std::nullopt;
    }
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


DBusConnection DBusConnection::bus_get(DBus::BusType bus_type)
{
    DBusConnection conn;

    DBusBusType t;
    if (bus_type == DBus::BusType::Session) {
        t = DBUS_BUS_SESSION;
    } else if (bus_type == DBus::BusType::System) {
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

DBusConnection& DBusConnection::operator=(const DBusConnection& other)
{
    delete this->_impl;
    this->_impl = new DBusConnection::Impl();
    this->_impl->connection = other._impl->connection;

    return *this;
}

} // namespace pr
