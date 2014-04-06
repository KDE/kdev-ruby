/*
 * This file is part of KDevelop
 * Copyright (C) 2012-2014 Miquel Sabaté Solà <mikisabate@gmail.com>
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


#ifndef MODULE_DECLARATION_H
#define MODULE_DECLARATION_H


#include <duchain/duchainexport.h>
#include <language/duchain/declaration.h>
#include <language/duchain/declarationdata.h>


namespace Ruby
{

/// Struct used in the appended list in the MethodDeclarationData.
struct KDEVRUBYDUCHAIN_EXPORT ModuleMixin {
    KDevelop::IndexedType module;
    bool included;
};

KDEVPLATFORMLANGUAGE_EXPORT DECLARE_LIST_MEMBER_HASH(ModuleDeclarationData, moduleMixins, ModuleMixin)
KDEVPLATFORMLANGUAGE_EXPORT DECLARE_LIST_MEMBER_HASH(ModuleDeclarationData, mixers, ModuleMixin)

/**
 * @class ModuleDeclarationData
 *
 * Private data structure for ModuleDeclaration. It contains an appended list
 * of module mix-ins and another one for the mixers.
 */
class KDEVRUBYDUCHAIN_EXPORT ModuleDeclarationData : public KDevelop::DeclarationData
{
public:
    /// Constructor.
    explicit ModuleDeclarationData() : isModule(true), eigenClass(nullptr)
    {
        initializeAppendedLists();
    }

    /// Copy constructor.
    explicit ModuleDeclarationData(const ModuleDeclarationData &rhs)
        : KDevelop::DeclarationData(rhs)
    {
        initializeAppendedLists();
        copyListsFrom(rhs);
        isModule = rhs.isModule;
        baseClass = rhs.baseClass;
        eigenClass = rhs.eigenClass;
    }

    /// Destructor.
    ~ModuleDeclarationData()
    {
        freeAppendedLists();
    }

    // List of module mixins.
    START_APPENDED_LISTS_BASE(ModuleDeclarationData, KDevelop::DeclarationData);
    APPENDED_LIST_FIRST(ModuleDeclarationData, ModuleMixin, moduleMixins);
    APPENDED_LIST(ModuleDeclarationData, ModuleMixin, mixers, moduleMixins);
    END_APPENDED_LISTS(ModuleDeclarationData, mixers);

    /// True if it's a module, false if it's a class.
    bool isModule;

    /// The eigen class for this module/class.
    KDevelop::DUContext *eigenClass;

    /// The base class type (if this is actually a class).
    KDevelop::IndexedType baseClass;
};

/**
 * @class ModuleDeclaration
 *
 * This class represents a module declaration. It defines methods to access to
 * the list of module mixins and the list of the mixers.
 */
class KDEVRUBYDUCHAIN_EXPORT ModuleDeclaration : public KDevelop::Declaration
{
public:
    /**
     * Constructor.
     *
     * @param data The data for this ModuleDeclaration.
     * @param range The range of this declaration.
     */
    explicit ModuleDeclaration(ModuleDeclarationData &data, const KDevelop::RangeInRevision &range);

    /**
     * Constructor.
     * @param range The range of this declaration.
     * @param ctx The context of this declaration.
     */
    explicit ModuleDeclaration(const KDevelop::RangeInRevision &range,
                               KDevelop::DUContext *context);

    /// Copy constructor.
    explicit ModuleDeclaration(const ModuleDeclaration &rhs);

    /**
     * Copy constructor.
     * @param data The data to be copied.
     */
    explicit ModuleDeclaration(ModuleDeclarationData &data);

    /// Clean the list of module mix-ins.
    void clearModuleMixins();

    /// @returns the size of the list of module mix-ins.
    uint moduleMixinsSize();

    /// @returns the list of module mix-ins.
    const ModuleMixin * moduleMixins() const;

    /// Add a new module mix-in @p module to the list of module mix-ins.
    void addModuleMixin(ModuleMixin module);

    /// Clean the list of mixers.
    void clearMixers();

    /// @returns the size of the list of mixers.
    uint mixersSize();

    /// @returns the list of mixers.
    const ModuleMixin * mixers() const;

    /// Add a new module mix-in @p module to the mixers list.
    void addMixer(ModuleMixin module);

    /// @returns true if this is a module, false if it's a class.
    bool isModule() const;

    /**
     * Set @p isModule to true if this is a module declaration, set to false
     * if this is a class declaration.
     */
    void setIsModule(bool isModule);

    /// Set the type @p base as the new base class for this class declaration.
    void setBaseClass(KDevelop::IndexedType base);

    /// Set @p ctx as the new context for the eigenclass.
    void setEigenClass(KDevelop::DUContext *ctx);

    /// Invalidate the current base class.
    void clearBaseClass();

    /// @returns the base class for this class declaration.
    KDevelop::IndexedType baseClass() const;

    /// @returns the eigen class for this module/class declaration.
    KDevelop::DUContext *eigenClass() const;

    /// Re-implemented from KDevelop::Declaration.
    QString toString() const;

    enum { Identity = 44 /** The id of this Type. */ };

private:
    /**
     * Check whether a module exists or not in one of the selected lists.
     *
     * @param module The given module.
     * @param who set to true if the mixers list is to be picked, and set to
     * false if the moduleMixins list is the one to be picked.
     * @returns true if the module exists, false otherwise.
     */
    bool mixinExists(ModuleMixin module, bool who);

private:
    /// Re-implemented from KDevelop::Declaration.
    virtual KDevelop::Declaration * clonePrivate() const;
    DUCHAIN_DECLARE_DATA(ModuleDeclaration)
};

} // End of namespace Ruby

Q_DECLARE_TYPEINFO(Ruby::ModuleMixin, Q_MOVABLE_TYPE);


#endif /* MODULE_DECLARATION_H */
