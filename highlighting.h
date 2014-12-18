/* This file is part of KDevelop
 *
 * Copyright (C) 2011-2014 Miquel Sabaté Solà <mikisabate@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef RUBY_HIGHLIGHTING_H
#define RUBY_HIGHLIGHTING_H

#include <language/highlighting/codehighlighting.h>

namespace ruby {

/**
 * @class HighlightingInstance
 *
 * The HighlightingInstance to be applied in a Ruby file.
 */
class HighlightingInstance : public KDevelop::CodeHighlightingInstance
{
public:
    explicit HighlightingInstance(const KDevelop::CodeHighlighting *h);

    /**
     * Return type of highlighting to be applied according
     * to the given declaration.
     *
     * @param decl The involved declaration.
     * @param ctx The context from where the declaration is used.
     */
    virtual Types typeForDeclaration(KDevelop::Declaration *decl,
                                     KDevelop::DUContext *ctx) const override;

    /**
     * Re-implemented from CodeHighlightingInstance to decide whether to
     * apply auto-generated rainbow colors or not.
     *
     * @param dec The involved declaration.
     */
    virtual bool useRainbowColor(KDevelop::Declaration *dec) const override;
};

/**
 * @class Highlighting
 *
 * This is a subclass of KDevelop::CodeHighlighting and it
 * represents the code highlighting for the Ruby language.
 */
class Highlighting : public KDevelop::CodeHighlighting
{
    Q_OBJECT

public:
    explicit Highlighting(QObject *parent);

private:
    /**
     * Extends base class CodeHighlighting's createInstance() method to use
     * this plugin's defined one.
     */
    virtual KDevelop::CodeHighlightingInstance * createInstance() const override;
};

}

#endif // RUBYHIGHLIGHTING_H

