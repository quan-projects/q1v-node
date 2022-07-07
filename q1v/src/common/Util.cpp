/**
 * Copyright (c) 2012-2016, The CryptoNote developers, The Bytecoin developers
 * Copyright (c) 2021-2022, The Quan Project developers
 *
 * Full source's copyright information can be found in the "/full_copyright/bytecoin_copyright.txt"
*/

#include "Util.h"
#include <cstdio>

#include <boost/filesystem.hpp>

#include "CryptoNoteConfig.h"
#include <sys/utsname.h>

namespace Tools {
    std::string get_nix_version_display_string() {
        utsname un;

        if (uname(&un) < 0)
            return std::string("*nix: failed to get os version");
        return std::string() + un.sysname + " " + un.version + " " + un.release;
    }

    std::string get_os_version_string() {
        return get_nix_version_display_string();
    }

    std::string getDataDirectory(std::string name) {
        std::string config_folder;
        std::string pathRet;
        char *pszHome = getenv("HOME");
        if (pszHome == NULL || strlen(pszHome) == 0) {
            pathRet = "/";
        } else {
            pathRet = pszHome;
        }
        config_folder = (pathRet + "/" + name);
        return config_folder;
    }

    std::string getDefaultDataDirectory() {
        return getDataDirectory("quan-project");
    }

    std::string getRebrandDataDirectory() {
        namespace fs = boost::filesystem;
        boost::system::error_code ec;
        std::string config_folder = getDataDirectory("niobio");
        fs::path fs_path(config_folder);
        if ((config_folder.empty()) || (!fs::is_directory(fs_path, ec))) config_folder = getDataDirectory(".niobio");
        return config_folder;
    }

    bool create_directories_if_necessary(const std::string &path) {
        namespace fs = boost::filesystem;
        boost::system::error_code ec;
        fs::path fs_path(path);
        fs::path old_fs_path(getRebrandDataDirectory());
        if (!fs::is_directory(fs_path, ec) && fs::is_directory(old_fs_path, ec)) {
            fs::rename(old_fs_path, fs_path);
        }
        if (fs::is_directory(fs_path, ec)) {
            return true;
        } else {
            return fs::create_directories(fs_path, ec);
        }
    }

    std::error_code replace_file(const std::string &replacement_name, const std::string &replaced_name) {
        int code;
        bool ok = 0 == std::rename(replacement_name.c_str(), replaced_name.c_str());
        code = ok ? 0 : errno;
        return std::error_code(code, std::system_category());
    }

    bool directoryExists(const std::string &path) {
        boost::system::error_code ec;
        return boost::filesystem::is_directory(path, ec);
    }

} // namespace
