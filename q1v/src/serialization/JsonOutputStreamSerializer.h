/**
 * Copyright (c) 2012-2016, The CryptoNote developers, The Bytecoin developers
 * Copyright (c) 2021-2022, The Quan Project developers
 *
 * Full source's copyright information can be found in the "/full_copyright/bytecoin_copyright.txt"
*/

#pragma once

#include <iostream>
#include "../common/JsonValue.h"
#include "ISerializer.h"

namespace Q1v {

    class JsonOutputStreamSerializer : public ISerializer {
    public:
        JsonOutputStreamSerializer();

        virtual ~JsonOutputStreamSerializer();

        SerializerType type() const override;

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

        const Common::JsonValue &getValue() const {
            return root;
        }

        friend std::ostream &operator<<(std::ostream &out, const JsonOutputStreamSerializer &enumerator);

    private:
        Common::JsonValue root;
        std::vector<Common::JsonValue *> chain;
    };

}
