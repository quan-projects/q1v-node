/**
 * Copyright (c) 2012-2016, The CryptoNote developers, The Bytecoin developers
 * Copyright (c) 2021-2022, The Quan Project developers
 *
 * Full source's copyright information can be found in the "/full_copyright/bytecoin_copyright.txt"
*/

#include "PathTools.h"
#include <algorithm>

namespace {

    const char GENERIC_PATH_SEPARATOR = '/';

    const char NATIVE_PATH_SEPARATOR = '/';

    std::string::size_type findExtensionPosition(const std::string &filename) {
        auto pos = filename.rfind('.');

        if (pos != std::string::npos) {
            auto slashPos = filename.rfind(GENERIC_PATH_SEPARATOR);
            if (slashPos != std::string::npos && slashPos > pos) {
                return std::string::npos;
            }
        }

        return pos;
    }

} // anonymous namespace

namespace Common {

    std::string NativePathToGeneric(const std::string &nativePath) {
        return nativePath;
    }

    std::string GetPathDirectory(const std::string &path) {
        auto slashPos = path.rfind(GENERIC_PATH_SEPARATOR);
        if (slashPos == std::string::npos) {
            return std::string();
        }
        return path.substr(0, slashPos);
    }

    std::string GetPathFilename(const std::string &path) {
        auto slashPos = path.rfind(GENERIC_PATH_SEPARATOR);
        if (slashPos == std::string::npos) {
            return path;
        }
        return path.substr(slashPos + 1);
    }

    void SplitPath(const std::string &path, std::string &directory, std::string &filename) {
        directory = GetPathDirectory(path);
        filename = GetPathFilename(path);
    }

    std::string CombinePath(const std::string &path1, const std::string &path2) {
        return path1 + GENERIC_PATH_SEPARATOR + path2;
    }

    std::string ReplaceExtenstion(const std::string &path, const std::string &extension) {
        return RemoveExtension(path) + extension;
    }

    std::string GetExtension(const std::string &path) {
        auto pos = findExtensionPosition(path);
        if (pos != std::string::npos) {
            return path.substr(pos);
        }
        return std::string();
    }

    std::string RemoveExtension(const std::string &filename) {
        auto pos = findExtensionPosition(filename);
        if (pos == std::string::npos) {
            return filename;
        }
        return filename.substr(0, pos);
    }

    bool HasParentPath(const std::string &path) {
        return path.find(GENERIC_PATH_SEPARATOR) != std::string::npos;
    }
}
