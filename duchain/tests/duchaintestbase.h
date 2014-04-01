/*
 * This file is part of KDevelop
 * Copyright 2012  Miquel Sabaté <mikisabate@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Library General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with this program; if not, write to the
 * Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */


#ifndef RUBY_DUCHAINTESTBASE_H
#define RUBY_DUCHAINTESTBASE_H


// Qt + KDevelop
#include <QtCore/QObject>
#include <language/duchain/duchain.h>
#include <language/duchain/duchainlock.h>

// Ruby
#include <duchain/duchainexport.h>

/*
 * This macro is used to annotate that the only purpose of a test is to
 * check that the code does not crash.
 */
#define DOES_NOT_CRASH QVERIFY(true)


namespace Ruby
{

/**
 * Manage pointer to TopDUContexts and release them properly, even if a test
 * fails. Shamelessly copied from the PHP plugin :)
 */
struct DUChainReleaser {
    DUChainReleaser(KDevelop::TopDUContext *top) : m_top(top) {}
    ~DUChainReleaser()
    {
        KDevelop::DUChainWriteLocker lock(KDevelop::DUChain::lock());
        KDevelop::DUChain::self()->removeDocumentChain(m_top);
    }
    KDevelop::TopDUContext *m_top;
};


/**
 * @class DUChainTestBase
 * The base class for all DUChain Test classes.
 */
class KDEVRUBYDUCHAIN_EXPORT DUChainTestBase : public QObject
{
    Q_OBJECT

public:
    DUChainTestBase();

protected:
    /**
     * Parse the given @p code that belongs to the test identified by @p id.
     *
     * @returns the KDevelop::TopDUContext for the given code, or nullptr if
     * something failed (i.e. parse error).
     */
    virtual KDevelop::TopDUContext * parse(const QByteArray &code, const QString &id);


    /**
     * Get a builtin method declaration.
     *
     * @param name The name of the method in a format such as "String#bytesize"
     * @param top The TopDUContext that we've got from parsing.
     * @param ctx Optional DUContext. Set this when you don't want a child
     * context from the @p top to be used.
     * @returns the Declaration of the required builtin method.
     */
    KDevelop::Declaration * getBuiltinDeclaration(const QString &name, KDevelop::TopDUContext *top,
                                                  KDevelop::DUContext *ctx = nullptr);

public slots:
    void initTestCase();
    void cleanupTestCase();
};

} // End of namespace Ruby


#endif /* RUBY_DUCHAINTESTBASE_H */
