# Libraries

| Name                     | Description |
|--------------------------|-------------|
| *libandiacoin_cli*         | RPC client functionality used by *andiacoin-cli* executable |
| *libandiacoin_common*      | Home for common functionality shared by different executables and libraries. Similar to *libandiacoin_util*, but higher-level (see [Dependencies](#dependencies)). |
| *libandiacoin_consensus*   | Stable, backwards-compatible consensus functionality used by *libandiacoin_node* and *libandiacoin_wallet* and also exposed as a [shared library](../shared-libraries.md). |
| *libandiacoinconsensus*    | Shared library build of static *libandiacoin_consensus* library |
| *libandiacoin_kernel*      | Consensus engine and support library used for validation by *libandiacoin_node* and also exposed as a [shared library](../shared-libraries.md). |
| *libandiacoinqt*           | GUI functionality used by *andiacoin-qt* and *andiacoin-gui* executables |
| *libandiacoin_ipc*         | IPC functionality used by *andiacoin-node*, *andiacoin-wallet*, *andiacoin-gui* executables to communicate when [`--enable-multiprocess`](multiprocess.md) is used. |
| *libandiacoin_node*        | P2P and RPC server functionality used by *andiacoind* and *andiacoin-qt* executables. |
| *libandiacoin_util*        | Home for common functionality shared by different executables and libraries. Similar to *libandiacoin_common*, but lower-level (see [Dependencies](#dependencies)). |
| *libandiacoin_wallet*      | Wallet functionality used by *andiacoind* and *andiacoin-wallet* executables. |
| *libandiacoin_wallet_tool* | Lower-level wallet functionality used by *andiacoin-wallet* executable. |
| *libandiacoin_zmq*         | [ZeroMQ](../zmq.md) functionality used by *andiacoind* and *andiacoin-qt* executables. |

## Conventions

- Most libraries are internal libraries and have APIs which are completely unstable! There are few or no restrictions on backwards compatibility or rules about external dependencies. Exceptions are *libandiacoin_consensus* and *libandiacoin_kernel* which have external interfaces documented at [../shared-libraries.md](../shared-libraries.md).

- Generally each library should have a corresponding source directory and namespace. Source code organization is a work in progress, so it is true that some namespaces are applied inconsistently, and if you look at [`libandiacoin_*_SOURCES`](../../src/Makefile.am) lists you can see that many libraries pull in files from outside their source directory. But when working with libraries, it is good to follow a consistent pattern like:

  - *libandiacoin_node* code lives in `src/node/` in the `node::` namespace
  - *libandiacoin_wallet* code lives in `src/wallet/` in the `wallet::` namespace
  - *libandiacoin_ipc* code lives in `src/ipc/` in the `ipc::` namespace
  - *libandiacoin_util* code lives in `src/util/` in the `util::` namespace
  - *libandiacoin_consensus* code lives in `src/consensus/` in the `Consensus::` namespace

## Dependencies

- Libraries should minimize what other libraries they depend on, and only reference symbols following the arrows shown in the dependency graph below:

<table><tr><td>

```mermaid

%%{ init : { "flowchart" : { "curve" : "basis" }}}%%

graph TD;

andiacoin-cli[andiacoin-cli]-->libandiacoin_cli;

andiacoind[andiacoind]-->libandiacoin_node;
andiacoind[andiacoind]-->libandiacoin_wallet;

andiacoin-qt[andiacoin-qt]-->libandiacoin_node;
andiacoin-qt[andiacoin-qt]-->libandiacoinqt;
andiacoin-qt[andiacoin-qt]-->libandiacoin_wallet;

andiacoin-wallet[andiacoin-wallet]-->libandiacoin_wallet;
andiacoin-wallet[andiacoin-wallet]-->libandiacoin_wallet_tool;

libandiacoin_cli-->libandiacoin_util;
libandiacoin_cli-->libandiacoin_common;

libandiacoin_common-->libandiacoin_consensus;
libandiacoin_common-->libandiacoin_util;

libandiacoin_kernel-->libandiacoin_consensus;
libandiacoin_kernel-->libandiacoin_util;

libandiacoin_node-->libandiacoin_consensus;
libandiacoin_node-->libandiacoin_kernel;
libandiacoin_node-->libandiacoin_common;
libandiacoin_node-->libandiacoin_util;

libandiacoinqt-->libandiacoin_common;
libandiacoinqt-->libandiacoin_util;

libandiacoin_wallet-->libandiacoin_common;
libandiacoin_wallet-->libandiacoin_util;

libandiacoin_wallet_tool-->libandiacoin_wallet;
libandiacoin_wallet_tool-->libandiacoin_util;

classDef bold stroke-width:2px, font-weight:bold, font-size: smaller;
class andiacoin-qt,andiacoind,andiacoin-cli,andiacoin-wallet bold
```
</td></tr><tr><td>

**Dependency graph**. Arrows show linker symbol dependencies. *Consensus* lib depends on nothing. *Util* lib is depended on by everything. *Kernel* lib depends only on consensus and util.

</td></tr></table>

- The graph shows what _linker symbols_ (functions and variables) from each library other libraries can call and reference directly, but it is not a call graph. For example, there is no arrow connecting *libandiacoin_wallet* and *libandiacoin_node* libraries, because these libraries are intended to be modular and not depend on each other's internal implementation details. But wallet code is still able to call node code indirectly through the `interfaces::Chain` abstract class in [`interfaces/chain.h`](../../src/interfaces/chain.h) and node code calls wallet code through the `interfaces::ChainClient` and `interfaces::Chain::Notifications` abstract classes in the same file. In general, defining abstract classes in [`src/interfaces/`](../../src/interfaces/) can be a convenient way of avoiding unwanted direct dependencies or circular dependencies between libraries.

- *libandiacoin_consensus* should be a standalone dependency that any library can depend on, and it should not depend on any other libraries itself.

- *libandiacoin_util* should also be a standalone dependency that any library can depend on, and it should not depend on other internal libraries.

- *libandiacoin_common* should serve a similar function as *libandiacoin_util* and be a place for miscellaneous code used by various daemon, GUI, and CLI applications and libraries to live. It should not depend on anything other than *libandiacoin_util* and *libandiacoin_consensus*. The boundary between _util_ and _common_ is a little fuzzy but historically _util_ has been used for more generic, lower-level things like parsing hex, and _common_ has been used for andiacoin-specific, higher-level things like parsing base58. The difference between util and common is mostly important because *libandiacoin_kernel* is not supposed to depend on *libandiacoin_common*, only *libandiacoin_util*. In general, if it is ever unclear whether it is better to add code to *util* or *common*, it is probably better to add it to *common* unless it is very generically useful or useful particularly to include in the kernel.


- *libandiacoin_kernel* should only depend on *libandiacoin_util* and *libandiacoin_consensus*.

- The only thing that should depend on *libandiacoin_kernel* internally should be *libandiacoin_node*. GUI and wallet libraries *libandiacoinqt* and *libandiacoin_wallet* in particular should not depend on *libandiacoin_kernel* and the unneeded functionality it would pull in, like block validation. To the extent that GUI and wallet code need scripting and signing functionality, they should be get able it from *libandiacoin_consensus*, *libandiacoin_common*, and *libandiacoin_util*, instead of *libandiacoin_kernel*.

- GUI, node, and wallet code internal implementations should all be independent of each other, and the *libandiacoinqt*, *libandiacoin_node*, *libandiacoin_wallet* libraries should never reference each other's symbols. They should only call each other through [`src/interfaces/`](`../../src/interfaces/`) abstract interfaces.

## Work in progress

- Validation code is moving from *libandiacoin_node* to *libandiacoin_kernel* as part of [The libandiacoinkernel Project #24303](https://github.com/andiacoin/andiacoin/issues/24303)
- Source code organization is discussed in general in [Library source code organization #15732](https://github.com/andiacoin/andiacoin/issues/15732)
