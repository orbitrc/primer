#include <stdio.h>

#include <primer/d-bus.h>

const char* type_to_string(pr::DBus::Type type)
{
    switch (type) {
    case pr::DBus::Type::Invalid:
        return "Invalid";
    case pr::DBus::Type::Int32:
        return "Int32";
    case pr::DBus::Type::String:
        return "String";
    case pr::DBus::Type::Boolean:
        return "Boolean";
    case pr::DBus::Type::Variant:
        return "Variant";
    case pr::DBus::Type::Array:
        return "Array";
    case pr::DBus::Type::DictEntry:
        return "DictEntry";
    default:
        break;
    }

    return "Unknown";
}

pr::String string_to_string(const pr::String& string)
{
    return pr::String("\""_S + string + "\"");
}

pr::String variant_to_string(const pr::DBusVariant& variant)
{
    pr::String s = "Variant<"_S;
    s = s + type_to_string(variant.type());
    s = s + ">"_S;

    return s;
}

pr::String dict_entry_to_string(const pr::DBusDictEntry& dict_entry)
{
    pr::String s = "{ "_S;
    // Key to string.
    if (dict_entry.key_type() == pr::DBus::Type::String) {
        s = s + string_to_string(dict_entry.key<pr::String>());
    } else {
        fprintf(stderr, "Type %d is not implemented!\n", dict_entry.key_type());
        s = s + "*Not implemented*"_S;
    }
    s = s + " = "_S;

    // Value to string.
    if (dict_entry.value_type() == pr::DBus::Type::Variant) {
        s = s + variant_to_string(dict_entry.value<pr::DBusVariant>());
    } else {
        s = s + "*Not implemented*"_S;
    }

    s = s + " }"_S;

    return s;
}

pr::String array_to_string(const pr::DBusArray& array)
{
    pr::String s = "Array<"_S;
    s = s + type_to_string(array.type());
    s = s + "> ["_S;

    if (array.type() == pr::DBus::Type::DictEntry) {
        auto vec = array.to_vector<pr::DBusDictEntry>();
        for (auto& item: vec) {
            s = s + dict_entry_to_string(item);
        }
    }

    s = s + "]"_S;

    return s;
}

int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv;

    auto conn = pr::DBusConnection::bus_get(pr::DBus::BusType::Session);

    pr::DBusMessage message = pr::DBusMessage::new_method_call(
        "org.kde.StatusNotifierWatcher"_S,
        "/StatusNotifierWatcher"_S,
        "org.freedesktop.DBus.Properties"_S,
        "GetAll"_S);

    message.append(""_S);
    // message.append("RegisteredStatusNotifierItems"_S);

    pr::DBusMessage reply;
    try {
        reply = conn.send_with_reply(message);
    } catch (const pr::DBusError& e) {
        fprintf(stderr, "%s\n", e.what());
        return 1;
    }

    fprintf(stderr, "Before get args.\n");
    auto args = reply.arguments();
    fprintf(stderr, "Got args. length: %ld\n", args.length());

    for (auto& arg: args) {
        printf("Argument: (%s)\n", type_to_string(arg.type()));
        if (arg.type() == pr::DBus::Type::Array) {
            printf("%s\n", array_to_string(arg.value<pr::DBusArray>()).c_str());
        }
    }

    return 0;
}
