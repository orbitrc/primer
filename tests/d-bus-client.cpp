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
    default:
        break;
    }

    return "Unknown";
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
        "Get"_S);

    message.append(""_S);
    message.append("RegisteredStatusNotifierItems"_S);

    pr::DBusMessage reply = conn.send_with_reply(message);

    auto args = reply.arguments();

    for (auto& arg: args) {
        printf("Argument: (%s)\n", type_to_string(arg.type()));
    }

    return 0;
}
