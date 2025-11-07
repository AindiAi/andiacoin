// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2022 The Andiacoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef ANDIACOIN_KERNEL_MESSAGESTARTCHARS_H
#define ANDIACOIN_KERNEL_MESSAGESTARTCHARS_H

#include <array>
#include <cstdint>

using MessageStartChars = std::array<uint8_t, 4>;

/** Message start magic values for different networks */
static constexpr MessageStartChars MAIN_NET_MESSAGE_START = {0xa1, 0xb2, 0xc3, 0xd4};
static constexpr MessageStartChars TEST_NET_MESSAGE_START = {0xaa, 0xbb, 0xcc, 0xdd};
static constexpr MessageStartChars SIGNET_MESSAGE_START = {0xee, 0xff, 0xaa, 0xbb};
static constexpr MessageStartChars REG_TEST_MESSAGE_START = {0xfa, 0xbf, 0xb5, 0xda};

#endif // ANDIACOIN_KERNEL_MESSAGESTARTCHARS_H