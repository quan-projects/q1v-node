/**
 * Copyright (c) 2012-2016, The CryptoNote developers, The Bytecoin developers
 * Copyright (c) 2021-2022, The Quan Project developers
 *
 * Full source's copyright information can be found in the "/full_copyright/bytecoin_copyright.txt"
*/

#pragma once

#include "common/IOutputStream.h"
#include "ISerializer.h"
#include "SerializationOverloads.h"

namespace Q1v {

    class BinaryOutputStreamSerializer : public ISerializer {
    public:
        BinaryOutputStreamSerializer(Common::IOutputStream &strm) : stream(strm) {}

        virtual ~BinaryOutputStreamSerializer() {}

        virtual ISerializer::SerializerType type() const override;

        virtual bool beginObject(Common::StringView name) override;

        virtual void endObject() override;

        virtual bool beginArray(size_t &size, Common::StringView name) override;

        virtual void endArray() override;

        virtual bool operator()(uint8_t &value, Common::StringView name) override;

        virtual bool operator()(int16_t &value, Common::StringView name) override;

        virtual bool operator()(uint16_t &value, Common::StringView name) override;

        virtual bool operator()(int32_t &value, Common::StringView name) override;

        virtual bool operator()(uint32_t &value, Common::StringView name) override;

        virtual bool operator()(int64_t &value, Common::StringView name) override;

        virtual bool operator()(uint64_t &value, Common::StringView name) override;

        virtual bool operator()(double &value, Common::StringView name) override;

        virtual bool operator()(bool &value, Common::StringView name) override;

        virtual bool operator()(std::string &value, Common::StringView name) override;

        virtual bool binary(void *value, size_t size, Common::StringView name) override;

        virtual bool binary(std::string &value, Common::StringView name) override;

        template<typename T>
        bool operator()(T &value, Common::StringView name) {
            return ISerializer::operator()(value, name);
        }

    private:
        void checkedWrite(const char *buf, size_t size);

        Common::IOutputStream &stream;
    };

}
