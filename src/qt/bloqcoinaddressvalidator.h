// Copyright (c) 2011-2014 The Bloqcoin developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BLOQCOIN_QT_BLOQCOINADDRESSVALIDATOR_H
#define BLOQCOIN_QT_BLOQCOINADDRESSVALIDATOR_H

#include <QValidator>

/** Base58 entry widget validator, checks for valid characters and
 * removes some whitespace.
 */
class BloqcoinAddressEntryValidator : public QValidator
{
    Q_OBJECT

public:
    explicit BloqcoinAddressEntryValidator(QObject *parent);

    State validate(QString &input, int &pos) const;
};

/** Bloqcoin address widget validator, checks for a valid bloqcoin address.
 */
class BloqcoinAddressCheckValidator : public QValidator
{
    Q_OBJECT

public:
    explicit BloqcoinAddressCheckValidator(QObject *parent);

    State validate(QString &input, int &pos) const;
};

#endif // BLOQCOIN_QT_BLOQCOINADDRESSVALIDATOR_H
