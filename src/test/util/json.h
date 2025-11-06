// Copyright (c) 2023 The Andiacoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef ANDIACOIN_TEST_UTIL_JSON_H
#define ANDIACOIN_TEST_UTIL_JSON_H

#include <string>

#include <univalue.h>

UniValue read_json(const std::string& jsondata);

#endif // ANDIACOIN_TEST_UTIL_JSON_H
