/* This file is part of KDevelop
 *
 * Copyright (C) 2011 Miquel Sabaté <mikisabate@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */


#ifndef RUBYDUCONTEXT_H
#define RUBYDUCONTEXT_H


/*
 * TODO: This file is still under development.
 */


#include <QString>
#include <language/duchain/ducontext.h>
class QWidget;

namespace KDevelop
{
    class Declaration;
    class TopDUContext;
}

namespace Ruby
{

// TODO: Python also has int IdentityT, that is passed to enum Identity, why?
template<class BaseContext>
class RubyDUContext : public BaseContext
{	
public:
    template<class Data>
    RubyDUContext(Data &data) : BaseContext(data) {};

    ///Parameters will be reached to the base-class
    template<class Param1, class Param2>
    RubyDUContext(const Param1 &p1, const Param2 &p2, bool isInstantiationContext)
		: BaseContext(p1, p2, isInstantiationContext)
    {
        static_cast<KDevelop::DUChainBase*>(this)->d_func_dynamic()->setClassId(this);
    }

    ///Both parameters will be reached to the base-class. This fits TopDUContext.
    template<class Param1, class Param2, class Param3>
    RubyDUContext(const Param1 &p1, const Param2 &p2, const Param3 &p3)
        : BaseContext(p1, p2, p3)
    {
        static_cast<KDevelop::DUChainBase*>(this)->d_func_dynamic()->setClassId(this);
    }

    template<class Param1, class Param2>
    RubyDUContext(const Param1 &p1, const Param2 &p2)
        : BaseContext(p1, p2)
    {
        static_cast<KDevelop::DUChainBase*>(this)->d_func_dynamic()->setClassId(this);
    }

    virtual QWidget* createNavigationWidget(KDevelop::Declaration *decl,
                                            KDevelop::TopDUContext *topContext,
                                            const QString &htmlPrefix,
                                            const QString &htmlSufix);

    //TODO: Both Php and Python define an enum called Identity as follows: Why? :S
    enum { Identity = BaseContext::Identity + 51 };
};

}

#endif // RUBYDUCONTEXT_H
