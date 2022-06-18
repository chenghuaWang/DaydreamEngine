/*!
 * @author  chenghua.wang
 * @brief   A API packaged for Qt-signal-slots like event transfer api.
 * */

#ifndef KALEIDOSCOPE_SIGNAL_SLOTS_HPP
#define KALEIDOSCOPE_SIGNAL_SLOTS_HPP

#if _MSC_VER > 1000
#pragma once
#endif //! _MSC_VER

#include "d_core/pch.hpp"
#include "Delegate.h"

using namespace Gallant;

#define slots   public
#define signal  public
#define emit
#define connect( a, signal, b, slot ) a.signal.Connect( &b, &slot )

namespace kaleidoscope {
    /*!
     * @brief the signal and slots implement.
     *
     * @details we use a 3rd party delegate system to implement the signal and slots
     * functions. The trigger of the delegate is not directly related to the listener,
     * and the two are indirectly connected through the delegate object. By binding the
     * response function to the delegate, the listener can immediately receive a notif-
     * ication when the delegate is triggered, and perform related logic processing.
     * */
    template< class Param0 = void >
    class Signal0 {
    public:
        typedef Delegate0< void > _Delegate;

    private:
        typedef std::set<_Delegate> DelegateList;
        typedef typename DelegateList::const_iterator DelegateIterator;
        DelegateList delegateList;

    public:
        void Connect( const _Delegate& delegate ){
            delegateList.insert( delegate );
        }

        template< class X, class Y >
        void Connect( Y * obj, void (X::*func)() ) {
            delegateList.insert( MakeDelegate( obj, func ) );
        }

        template< class X, class Y >
        void Connect( Y * obj, void (X::*func)() const ) {
            delegateList.insert( MakeDelegate( obj, func ) );
        }

        void Disconnect( const _Delegate& delegate ) {
            delegateList.erase( delegate );
        }

        template< class X, class Y >
        void Disconnect( Y * obj, void (X::*func)() ) {
            delegateList.erase( MakeDelegate( obj, func ) );
        }

        template< class X, class Y >
        void Disconnect( Y * obj, void (X::*func)() const ) {
            delegateList.erase( MakeDelegate( obj, func ) );
        }

        void Clear() {
            delegateList.clear();
        }

        void Emit() const {
            for (auto i = delegateList.begin(); i != delegateList.end(); ) {
                (*(i++))();
            }
        }

        void operator() () const {
            Emit();
        }

        [[nodiscard]] bool Empty() const {
            return delegateList.empty();
        }
    };

    template< class Param1 >
    class Signal1 {
    public:
        typedef Delegate1< Param1 > _Delegate;

    private:
        typedef std::set<_Delegate> DelegateList;
        typedef typename DelegateList::const_iterator DelegateIterator;
        DelegateList delegateList;

    public:
        void Connect( _Delegate delegate ) {
            delegateList.insert( delegate );
        }

        template< class X, class Y >
        void Connect( Y * obj, void (X::*func)( Param1 p1 ) ) {
            delegateList.insert( MakeDelegate( obj, func ) );
        }

        template< class X, class Y >
        void Connect( Y * obj, void (X::*func)( Param1 p1 ) const ) {
            delegateList.insert( MakeDelegate( obj, func ) );
        }

        void Disconnect( _Delegate delegate ) {
            delegateList.erase( delegate );
        }

        template< class X, class Y >
        void Disconnect( Y * obj, void (X::*func)( Param1 p1 ) ) {
            delegateList.erase( MakeDelegate( obj, func ) );
        }

        template< class X, class Y >
        void Disconnect( Y * obj, void (X::*func)( Param1 p1 ) const ) {
            delegateList.erase( MakeDelegate( obj, func ) );
        }

        void Clear() {
            delegateList.clear();
        }

        void Emit( Param1 p1 ) const {
            for (DelegateIterator i = delegateList.begin(); i != delegateList.end(); ) {
                (*(i++))( p1 );
            }
        }

        void operator() ( Param1 p1 ) const {
            Emit( p1 );
        }

        [[nodiscard]] bool Empty() const {
            return delegateList.empty();
        }
    };


    template< class Param1, class Param2 >
    class Signal2
    {
    public:
        typedef Delegate2< Param1, Param2 > _Delegate;

    private:
        typedef std::set<_Delegate> DelegateList;
        typedef typename DelegateList::const_iterator DelegateIterator;
        DelegateList delegateList;

    public:
        void Connect( _Delegate delegate ) {
            delegateList.insert( delegate );
        }

        template< class X, class Y >
        void Connect( Y * obj, void (X::*func)( Param1 p1, Param2 p2 ) ) {
            delegateList.insert( MakeDelegate( obj, func ) );
        }

        template< class X, class Y >
        void Connect( Y * obj, void (X::*func)( Param1 p1, Param2 p2 ) const ) {
            delegateList.insert( MakeDelegate( obj, func ) );
        }

        void Disconnect( _Delegate delegate ) {
            delegateList.erase( delegate );
        }

        template< class X, class Y >
        void Disconnect( Y * obj, void (X::*func)( Param1 p1, Param2 p2 ) ) {
            delegateList.erase( MakeDelegate( obj, func ) );
        }

        template< class X, class Y >
        void Disconnect( Y * obj, void (X::*func)( Param1 p1, Param2 p2 ) const ) {
            delegateList.erase( MakeDelegate( obj, func ) );
        }

        void Clear() {
            delegateList.clear();
        }

        void Emit( Param1 p1, Param2 p2 ) const {
            for (DelegateIterator i = delegateList.begin(); i != delegateList.end(); )
            {
                (*(i++))( p1, p2 );
            }
        }

        void operator() ( Param1 p1, Param2 p2 ) const {
            Emit( p1, p2 );
        }

        [[nodiscard]] bool Empty() const {
            return delegateList.empty();
        }
    };


    template< class Param1, class Param2, class Param3 >
    class Signal3
    {
    public:
        typedef Delegate3< Param1, Param2, Param3 > _Delegate;

    private:
        typedef std::set<_Delegate> DelegateList;
        typedef typename DelegateList::const_iterator DelegateIterator;
        DelegateList delegateList;

    public:
        void Connect( _Delegate delegate ) {
            delegateList.insert( delegate );
        }

        template< class X, class Y >
        void Connect( Y * obj, void (X::*func)( Param1 p1, Param2 p2, Param3 p3 ) ) {
            delegateList.insert( MakeDelegate( obj, func ) );
        }

        template< class X, class Y >
        void Connect( Y * obj, void (X::*func)( Param1 p1, Param2 p2, Param3 p3 ) const ) {
            delegateList.insert( MakeDelegate( obj, func ) );
        }

        void Disconnect( _Delegate delegate ) {
            delegateList.erase( delegate );
        }

        template< class X, class Y >
        void Disconnect( Y * obj, void (X::*func)( Param1 p1, Param2 p2, Param3 p3 ) ) {
            delegateList.erase( MakeDelegate( obj, func ) );
        }

        template< class X, class Y >
        void Disconnect( Y * obj, void (X::*func)( Param1 p1, Param2 p2, Param3 p3 ) const ) {
            delegateList.erase( MakeDelegate( obj, func ) );
        }

        void Clear() {
            delegateList.clear();
        }

        void Emit( Param1 p1, Param2 p2, Param3 p3 ) const {
            for (DelegateIterator i = delegateList.begin(); i != delegateList.end(); ) {
                (*(i++))( p1, p2, p3 );
            }
        }

        void operator() ( Param1 p1, Param2 p2, Param3 p3 ) const {
            Emit( p1, p2, p3 );
        }

        [[nodiscard]] bool Empty() const {
            return delegateList.empty();
        }
    };

}

#endif //KALEIDOSCOPE_SIGNAL_SLOTS_HPP
