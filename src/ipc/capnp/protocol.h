// Copyright (c) 2009-2025 The Bitcoin Core developers
// Copyright (c) 2025 The Andiacoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef ANDIACOIN_IPC_CAPNP_PROTOCOL_H
#define ANDIACOIN_IPC_CAPNP_PROTOCOL_H

#include <memory>

namespace ipc {
class Protocol;
namespace capnp {
std::unique_ptr<Protocol> MakeCapnpProtocol();
} // namespace capnp
} // namespace ipc

#endif // ANDIACOIN_IPC_CAPNP_PROTOCOL_H
