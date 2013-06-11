/*  This file is part of the Vc library. {{{

    Copyright (C) 2009-2012 Matthias Kretz <kretz@kde.org>

    Vc is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as
    published by the Free Software Foundation, either version 3 of
    the License, or (at your option) any later version.

    Vc is distributed in the hope that it will be useful, but
    WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with Vc.  If not, see <http://www.gnu.org/licenses/>.

}}}*/

#ifndef VC_MIC_STOREMIXIN_H
#define VC_MIC_STOREMIXIN_H

#include <type_traits>

Vc_NAMESPACE_BEGIN(Vc_IMPL_NAMESPACE)

template<typename Parent, typename T> class StoreMixin
{
private:
    typedef typename VectorTypeHelper<T>::Type VectorType;
    typedef typename DetermineEntryType<T>::Type EntryType;
    typedef typename DetermineVectorEntryType<T>::Type VectorEntryType;
    typedef Vc_IMPL_NAMESPACE::Mask<64 / sizeof(VectorEntryType)> Mask;

    // helper that specializes on VectorType
    typedef VectorHelper<VectorType> HV;

    // helper that specializes on T
    typedef VectorHelper<VectorEntryType> HT;

    template<typename MemType> using UpDownC = UpDownConversion<VectorEntryType, typename std::remove_cv<MemType>::type>;

    VectorType  data() const { return static_cast<const Parent *>(this)->data(); }
    VectorType &data()       { return static_cast<      Parent *>(this)->data(); }

public:
    template<typename T2> void store(T2 *mem) const;
    template<typename T2> void store(T2 *mem, Mask mask) const;
    template<typename T2, typename A> void store(T2 *mem, A) const;
    template<typename T2, typename A> void store(T2 *mem, Mask mask, A) const;
    // the following store overloads are here to support classes that have a cast operator to T.
    // Without this overload GCC complains about not finding a matching store function.
    inline void store(T *mem) const { store<T>(mem); }
    inline void store(T *mem, Mask mask) const { store<T>(mem, mask); }
    template<typename A> inline void store(T *mem, A align) const { store<T, A>(mem, align); }
    template<typename A> inline void store(T *mem, Mask mask, A align) const { store<T, A>(mem, mask, align); }
};

Vc_NAMESPACE_END
#endif // VC_MIC_STOREMIXIN_H