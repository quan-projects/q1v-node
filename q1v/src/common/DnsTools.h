/**
 * Copyright (c) 2016-2019, The Karbo developers
 * Copyright (c) 2021-2022, The Quan Project developers
 *
 * Full source's copyright information can be found in the "/full_copyright/karbo_copyright.txt"
*/

#pragma once

#include <string>
#include <vector>

namespace Common {

    bool fetch_dns_txt(const std::string domain, std::vector<std::string> &records);

}
