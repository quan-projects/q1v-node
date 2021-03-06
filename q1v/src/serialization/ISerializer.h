/**
 * Copyright (c) 2012-2016, The CryptoNote developers, The Bytecoin developers
 * Copyright (c) 2021-2022, The Quan Project developers
 *
 * Full source's copyright information can be found in the "/full_copyright/bytecoin_copyright.txt"
*/

#pragma once

#include <string>
#include <cstdint>

#include <common/StringView.h>

namespace Q1v {

    class ISerializer {
    public:

        enum SerializerType {
            INPUT, OUTPUT
        };

        virtual ~ISerializer() = default;

        virtual SerializerType type() const = 0;

        virtual bool beginObject(Common::StringView name) = 0;

        virtual void endObject() = 0;

        virtual bool beginArray(size_t &size, Common::StringView name) = 0;

        virtual void endArray() = 0;

        virtual bool operator()(uint8_t &value, Common::StringView name) = 0;

        virtual bool operator()(int16_t &value, Common::StringView name) = 0;

        virtual bool operator()(uint16_t &value, Common::StringView name) = 0;

        virtual bool operator()(int32_t &value, Common::StringView name) = 0;

        virtual bool operator()(uint32_t &value, Common::StringView name) = 0;

        virtual bool operator()(int64_t &value, Common::StringView name) = 0;

        virtual bool operator()(uint64_t &value, Common::StringView name) = 0;

        virtual bool operator()(double &value, Common::StringView name) = 0;

        virtual bool operator()(bool &value, Common::StringView name) = 0;

        virtual bool operator()(std::string &value, Common::StringView name) = 0;

        // read/write binary block
        virtual bool binary(void *value, size_t size, Common::StringView name) = 0;

        virtual bool binary(std::string &value, Common::StringView name) = 0;

        template<typename T>
        bool operator()(T &value, Common::StringView name);
    };

    template<typename T>
    bool ISerializer::operator()(T &value, Common::StringView name) {
        return serialize(value, name, *this);
    }

    template<typename T>
    bool serialize(T &value, const Common::StringView &name, ISerializer &serializer) {
        if (!serializer.beginObject(name)) {
            return false;
        }

        serialize(value, serializer);
        serializer.endObject();
        return true;
    }

    template<typename T>
    void serialize(T &value, ISerializer &serializer) {
        value.serialize(serializer);
    }

#ifdef __clang__
    template<> inline
    bool ISerializer::operator()(size_t& value, Common::StringView name) {
      return operator()(*reinterpret_cast<uint64_t*>(&value), name);
    }
#endif

#define KV_MEMBER(member) s(member, #member);

}
