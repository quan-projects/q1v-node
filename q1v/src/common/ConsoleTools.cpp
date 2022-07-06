/**
 * Copyright (c) 2012-2016, The CryptoNote developers, The Bytecoin developers
 * Copyright (c) 2021-2022, The Quan Project developers
 *
 * Full source's copyright information can be found in the "/full_copyright/bytecoin_copyright.txt"
*/

#include "ConsoleTools.h"

#include <stdio.h>

#include <iostream>
#include <unistd.h>

namespace Common {
    namespace Console {

        bool isConsoleTty() {
            static bool istty = 0 != isatty(fileno(stdout));
            return istty;
        }

        void setTextColor(Color color) {
            if (!isConsoleTty()) {
                return;
            }

            if (color > Color::BrightMagenta) {
                color = Color::Default;
            }
            static const char *ansiColors[] = {
                    // default
                    "\033[0m",
                    // main
                    "\033[0;34m", "\033[0;32m", "\033[0;31m", "\033[0;33m", "\033[0;37m", "\033[0;36m", "\033[0;35m",
                    // bright
                    "\033[1;34m", "\033[1;32m", "\033[1;31m", "\033[1;33m", "\033[1;37m", "\033[1;36m", "\033[1;35m"};

            std::cout << ansiColors[static_cast<size_t>(color)];

        }
    }
}
