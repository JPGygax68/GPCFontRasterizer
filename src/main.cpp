#include <iostream>
#include <stdexcept>
#include <string>

#include <boost/filesystem.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_GLYPH_H
#include FT_ERRORS_H

typedef std::pair<std::string, std::string> NameValuePair;

static auto splitParam(const std::string &param) -> NameValuePair {

    auto p = param.find_first_of('=');
    std::string name, value;

    if (p != std::string::npos) {
        name = param.substr(0, p);
        value = param.substr(p + 1);
    }
    else {
        name = param;
    }

    return std::move( NameValuePair(name, value) );
}

static auto findFontFile(const std::string &file) -> std::string {

    using namespace std;
    using namespace boost::filesystem;

    path file_path(file);

    // If the unaltered path leads to an existing file, there's nothing to do
    if (exists(file_path)) return file_path.string();

    // If the path is not absolute, try OS-dependent prefixes
    if (!file_path.is_absolute()) {
#ifdef _WIN32
        const char *system_root = getenv("SystemRoot");
        if (system_root == nullptr) system_root = "C:\\Windows";
        path full_path = path(system_root) / "Fonts" / file_path;
        if (!exists(full_path)) throw runtime_error(string("Couldn't find font file \"")+file+"\" at any known location");
        return full_path.string();
#else
#endif
    }
    else throw runtime_error(string("Font file \"") + file + "\" doesn't exist");
}

int main(int argc, const char *argv[])
{
    using namespace std;

    int exit_code = -1;

    try {

        // Get command-line arguments
        for (auto i = 1; i < argc; i ++) {
            auto name_value = splitParam(argv[i]);
            if (name_value.first == "file") {
                cout << "file = " << name_value.second << endl;
                std::string full_path = findFontFile(name_value.second);
                cout << "full path = " << full_path << endl;
            }
            else {
                throw runtime_error(string("invalid parameter \"") + argv[i] + "\"");
            }
        }
    }
    catch(exception &e) {
        cerr << "Error: " << e.what() << endl;
    }

    cout << "Press RETURN to terminate" << endl;
    cin.ignore();

    return exit_code;
}