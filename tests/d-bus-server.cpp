#include <primer/string.h>
#include <primer/d-bus.h>
#include <primer/io.h>

#include <stdio.h>

int main(int argc, char *argv[])
{
    pr::String introspection =
        pr::String(pr::DBus::introspect_1_0_xml_doctype_decl_node())
        + "<node>\n"_S
        + "  <interface name='org.freedesktop.DBus.Introspectable'>\n"_S
        + "    <method name='Introspect'>\n"_S
        + "      <arg name='data' type='s' direction='out' />\n"_S
        + "    </method>\n"_S
        + "  </interface>\n"_S
        + "  <node name='Test' />"_S
        + "</node>"_S;

    pr::String test_introspection =
        pr::String(pr::DBus::introspect_1_0_xml_doctype_decl_node())
        + "<node>\n"_S
        + "  <interface name='org.example.Test'>\n"_S
        + "    <property name='Greeting' type='s' access='read' />\n"_S
        + "    <method name='SetName'>\n"_S
        + "      <arg name='name' direction='in' type='s' />\n"_S
        + "    </method>\n"_S
        + "    <signal name='NameChanged' />\n"_S
        + "  </interface>\n"_S
        + "</node>"_S;

    auto conn = pr::DBusConnection::bus_get(pr::DBus::Type::Session);

    conn.request_name("org.example.Test"_S);

    while (conn.read_write_dispatch()) {
        auto message_opt = conn.pop_message();
        if (message_opt == std::nullopt) {
            fprintf(stderr, "pop_message() returned null.\n");
            continue;
        }
        auto message = message_opt.value();

        auto interface = message.interface();
        auto member = message.member();
        auto path = message.path();

        pr::println(interface);
        pr::println(member);
        pr::println(path);
        pr::println("-----------"_S);

        if (interface == "org.freedesktop.DBus.Introspectable"_S &&
                member == "Introspect"_S) {
            printf(" * Introspection\n");
            if (path == "/"_S) {
                auto ret = message.new_method_return();

                ret.append(introspection);

                conn.send(ret);
            } else if (path == "/Test"_S) {
                auto ret = message.new_method_return();

                ret.append(test_introspection);

                conn.send(ret);
            }
        } else if (interface == "org.freedesktop.DBus.Properties"_S &&
                member == "Get"_S) {
            printf(" * Property Get\n");
            auto ret = message.new_method_return();
            auto vec = message.arguments();
            printf(" - Length: %ld\n", vec.length());

            if (vec.length() < 2) {
                // Error
            }

            auto property = vec[1].value<pr::String>();
            if (property == "Greeting"_S) {
                ret.append(pr::DBus::Variant("Hello!"_S));

                conn.send(ret);
            }
        } else if (member == "SetName"_S) {
            printf(" * Method Call\n");
            auto args = message.arguments();
            printf("  - Length: %ld\n", args.length());
            auto name = args[0].value<pr::String>();
            printf("  - Argument: %s\n", name.c_str());

            auto signal = message.new_signal("/Test"_S,
                "org.example.Test"_S,
                "NameChanged"_S);

            conn.send(signal);
        }
    }

    return 0;
}
