/**
 * Copyright (c) 2012-2016, The CryptoNote developers, The Bytecoin developers
 * Copyright (c) 2021-2022, The Quan Project developers
 *
 * Full source's copyright information can be found in the "/full_copyright/bytecoin_copyright.txt"
*/

#pragma once

#include <vector>
#include <common/IOutputStream.h>
#include "ISerializer.h"
#include "MemoryStream.h"

namespace Q1v {

    class KVBinaryOutputStreamSerializer : public ISerializer {
    public:

        KVBinaryOutputStreamSerializer();

        virtual ~KVBinaryOutputStreamSerializer() {}

        void dump(Common::IOutputStream &target);

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

        void writeElementPrefix(uint8_t type, Common::StringView name);

        void checkArrayPreamble(uint8_t type);

        void updateState(uint8_t type);

        MemoryStream &stream();

        enum class State {
            Root, Object, ArrayPrefix, Array
        };

        struct Level {
            State state;
            std::string name;
            size_t count;

            Level(Common::StringView nm) : name(nm), state(State::Object), count(0) {}

            Level(Common::StringView nm, size_t arraySize) : name(nm), state(State::ArrayPrefix), count(arraySize) {}

            Level(Level &&rv) {
                state = rv.state;
                name = std::move(rv.name);
                count = rv.count;
            }

        };

        std::vector<MemoryStream> m_objectsStack;
        std::vector<Level> m_stack;
    };

}
