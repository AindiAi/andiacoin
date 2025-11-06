// Copyright (c) 2023 Andiacoin Developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "logprintf.h"

#include <clang-tidy/ClangTidyModule.h>
#include <clang-tidy/ClangTidyModuleRegistry.h>

class AndiacoinModule final : public clang::tidy::ClangTidyModule
{
public:
    void addCheckFactories(clang::tidy::ClangTidyCheckFactories& CheckFactories) override
    {
        CheckFactories.registerCheck<andiacoin::LogPrintfCheck>("andiacoin-unterminated-logprintf");
    }
};

static clang::tidy::ClangTidyModuleRegistry::Add<AndiacoinModule>
    X("andiacoin-module", "Adds andiacoin checks.");

volatile int AndiacoinModuleAnchorSource = 0;
