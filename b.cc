export module b;

export import : a;
export import c;
import std;

export std::string_view message = { b_message_string };