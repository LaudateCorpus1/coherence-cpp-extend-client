/*
 * Copyright (c) 2000, 2020, Oracle and/or its affiliates.
 *
 * Licensed under the Universal Permissive License v 1.0 as shown at
 * http://oss.oracle.com/licenses/upl.
 */
#ifndef COH_CLASS_SPEC_HPP
#define COH_CLASS_SPEC_HPP

#include "coherence/lang/compatibility.hpp"

#include "coherence/lang/lang_spec.hpp"
#include "coherence/lang/TypedHandle.hpp"
#include "coherence/lang/TypedHolder.hpp"

COH_OPEN_NAMESPACE2(coherence,lang)

class Object;

extern COH_EXPORT void coh_throw_clone_not_supported(const std::type_info&);

/**
* Helper for defining a non-cloneable concrete managed class.
*
* Managed classes are implementations of coherence::lang::Object, and include
* a set of well known features, which are auto-generated by this helper class:
*
* - Handle/View/Holder definitions
* - super class definition
* - virtual interface inheritance of up to 16 interfaces
* - public static create methods which delegate to protected constructors with
*   up to sixteen arguments
* - automatic sizeOf() definition
*
* The template takes three parameters:
*
* - The name of the class being defined
* - The defined classes parent class, indicated as extends<parent>
* - An optional list of interfaces to implement, indicated as
*   implements<i1, i2, ...>
*
* A normal class definition would be:
* @code
* class Foo
*   : public class_spec<Foo,
*       extends<Bar>,
*       implements<SomeInterface, SomeOtherInterface> >
*   {
*   // add support for auto-generated static create methods
*   friend class factory<Foo>;
*
*   protected:
*       // Constructors are defined as protected, and access via
*       // auto-generated create methods, with matching signatures
*       Foo()
*           : super() // calls Bar()
*           {
*           }
*
*   public:
*       // normal class definition....
*   };
* @endcode
*
* @see extends
* @see implements
*
* @author mf 2008.07.14
*/
template<class T, class E = extends<Object, void>, class I = implements<> >
class COH_EXPORT_SPEC class_spec
    : public E, public E::inherited, public virtual I::implements_chain
    {
    // ----- typedefs -------------------------------------------------------

    public:
        /**
        * Specification definition
        */
        typedef class_spec this_spec;

        /**
        * Factory for this class
        */
        typedef factory<T> factory_spec;

        /**
        * Definition T's actual parent class
        */
        typedef class_spec super;

        /**
        * Definition of the spec's parent class
        */
        typedef typename E::inherited super_spec;

        /**
        * Definition T's logical parent class
        */
        typedef typename E::inherited_literal inherited;

        /**
        * @internal
        *
        * Definition T's alias
        */
        typedef typename E::alias alias;

        /**
        * Standard Handle definition
        */
        typedef TypedHandle<T> Handle;

        /**
        * Standard View definition
        */
        typedef TypedHandle<const T> View;

        /**
        * Standard Holder definition
        */
        typedef TypedHolder<T> Holder;

        /**
         * implemented interface typedefs
         */
        typedef typename I::interface_1  interface_1;
        typedef typename I::interface_2  interface_2;
        typedef typename I::interface_3  interface_3;
        typedef typename I::interface_4  interface_4;
        typedef typename I::interface_5  interface_5;
        typedef typename I::interface_6  interface_6;
        typedef typename I::interface_7  interface_7;
        typedef typename I::interface_8  interface_8;
        typedef typename I::interface_9  interface_9;
        typedef typename I::interface_10 interface_10;
        typedef typename I::interface_11 interface_11;
        typedef typename I::interface_12 interface_12;
        typedef typename I::interface_13 interface_13;
        typedef typename I::interface_14 interface_14;
        typedef typename I::interface_15 interface_15;
        typedef typename I::interface_16 interface_16;


    // ----- constructors ---------------------------------------------------

    protected:
        /**
        * Generate a set of proxy constructors matching the signatures of the
        * parent class's constructors.
        *
        * NOTE: Compilation errors referencing this line likely indicate that
        *       class being defined by this spec makes calls a "super"
        *       constructor supplying a set of parameters for which there is
        *       no exact match on the parent class.
        */
        COH_DEFINE_PROXY_CONSTRUCTORS(class_spec)

    public:
        /**
        * Generate a set of static "create" methods matching the signatures of
        * class T's constructors.
        *
        * NOTE: Compilation errors referencing this line likely indicate that
        *       the parameters supplied by the caller to the create method did
        *       not match one of the constructors.
        */
        COH_DEFINE_CREATE_METHODS(Handle, factory_spec::create)

        virtual TypedHandle<Object> clone() const
            {
            coh_throw_clone_not_supported(typeid(T));
            return NULL;
            }

        virtual size64_t sizeOf(bool fDeep = false) const
            {
            return fDeep
                    ? inherited::sizeOf(/*fDeep*/ true)
                    : sizeof(T);
            }

        virtual void* _cast(coh_class_id pInfo) const
            {
            // first check if this class has the class id in question
            // if not do a breadth first search across directly implemented
            // interfaces, and then finally tail recurse up the inheritance
            // hierarchy
            void* p = COH_CLASS_ID(T) == pInfo
                    ? (void*) static_cast<const T*>(this)
                    : I::implements_chain::_icast(pInfo);
            return p ? p : super_spec::_cast(pInfo);
            }


        COH_GENERATE_CLASS_ID(T)

        /**
         * @internal
         *
         * Return the class id of an object.
         */
        virtual coh_class_id _getClassId() const
            {
            return COH_CLASS_ID(T);
            }

    protected:
        /**
        * @internal
        *
        * Protect access to create method generated for the copy constructor.
        */
        static inline Handle create(const T& that)
            {
            return Handle(factory_spec::create(that));
            }
    };

COH_CLOSE_NAMESPACE2

#endif // COH_CLASS_SPEC_HPP