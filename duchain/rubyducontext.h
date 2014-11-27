/* This file is part of KDevelop
 *
 * Copyright (C) 2011-2014 Miquel Sabaté Solà <mikisabate@gmail.com>
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


#include <language/duchain/ducontext.h>


namespace KDevelop
{
    class Declaration;
    class TopDUContext;
}

namespace ruby {

template<class BaseContext>
class RubyDUContext : public BaseContext
{	
public:
    template<class Data>
    explicit RubyDUContext(Data &data) : BaseContext(data)
    {
        /* There's nothing to do here */
    };

    /**
     * Parameters will be reached to the base-class.
     */
    template<class Param1, class Param2>
    explicit RubyDUContext(const Param1 &p1, const Param2 &p2,
                           bool isInstantiationContext)
		: BaseContext(p1, p2, isInstantiationContext)
    {
        static_cast<KDevelop::DUChainBase*>(this)->d_func_dynamic()->setClassId(this);
    }

    /**
     * Both parameters will be reached to the base-class. This fits TopDUContext.
     */
    template<class Param1, class Param2, class Param3>
    explicit RubyDUContext(const Param1 &p1, const Param2 &p2, const Param3 &p3)
        : BaseContext(p1, p2, p3)
    {
        static_cast<KDevelop::DUChainBase*>(this)->d_func_dynamic()->setClassId(this);
    }

    template<class Param1, class Param2>
    explicit RubyDUContext(const Param1 &p1, const Param2 &p2)
        : BaseContext(p1, p2)
    {
        static_cast<KDevelop::DUChainBase*>(this)->d_func_dynamic()->setClassId(this);
    }

    /**
     * Create a Navigation Widget for user-interaction within the quickopen list.
     *
     * @param decl A member-declaration of this context the navigation-widget should be created for. Zero to create a widget for this context.
     * @param topContext Top-context from where the navigation-widget is triggered.
     * @param htmlPrefix Html-formatted text that should be prepended before any information shown by this widget
     * @param htmlSuffix Html-formatted text that should be appended to any information shown by this widget
     */
    virtual QWidget* createNavigationWidget(KDevelop::Declaration *decl = nullptr,
                                            KDevelop::TopDUContext *topContext = nullptr,
                                            const QString &htmlPrefix = QString(),
                                            const QString &htmlSuffix = QString()) const override;

public:
    enum { Identity = BaseContext::Identity + 41 };
};

typedef RubyDUContext<KDevelop::TopDUContext> RubyTopDUContext;
typedef RubyDUContext<KDevelop::DUContext> RubyNormalDUContext;

}

#endif // RUBYDUCONTEXT_H
