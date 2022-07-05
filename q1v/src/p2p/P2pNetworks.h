/**
 * Copyright (c) 2012-2016, The CryptoNote developers, The Bytecoin developers
 * Copyright (c) 2017, The Niobio Cash developers
 * Copyright (c) 2021-2022, The Quan Project developers
 *
 * Full source's copyright information can be found in the "/full_copyright/old_niobiocash_1_copyright.txt"
*/

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include "../CryptoNoteConfig.h"

#pragma once

namespace Q1v
{
	namespace
	{
		boost::uuids::uuid name;
		boost::uuids::name_generator gen(name);
		boost::uuids::uuid u = gen(GENESIS_COINBASE_TX_HEX);
	}
	const static boost::uuids::uuid Q1V_NETWORK = { { 0x95, 0x8B, 0x44, 0x59, 0xC4, 0x96, 0x6B, 0x98, 0x24, 0xBA, 0x90, 0x6D, 0x89, 0xEF, 0xCE, 0x2A } };
}
