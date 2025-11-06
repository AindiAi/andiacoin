// Copyright (c) 2011-2020 The Andiacoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef ANDIACOIN_QT_ANDIACOINADDRESSVALIDATOR_H
#define ANDIACOIN_QT_ANDIACOINADDRESSVALIDATOR_H

#include <QValidator>

/** Base58 entry widget validator, checks for valid characters and
 * removes some whitespace.
 */
class AndiacoinAddressEntryValidator : public QValidator
{
    Q_OBJECT

public:
    explicit AndiacoinAddressEntryValidator(QObject *parent);

    State validate(QString &input, int &pos) const override;
};

/** Andiacoin address widget validator, checks for a valid andiacoin address.
 */
class AndiacoinAddressCheckValidator : public QValidator
{
    Q_OBJECT

public:
    explicit AndiacoinAddressCheckValidator(QObject *parent);

    State validate(QString &input, int &pos) const override;
};

#endif // ANDIACOIN_QT_ANDIACOINADDRESSVALIDATOR_H
