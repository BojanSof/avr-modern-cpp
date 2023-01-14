#ifndef _HW_REG_TYPE_HELPER_HPP
#define _HW_REG_TYPE_HELPER_HPP

#include "stdint.h"

namespace HwReg
{
    template<typename AddressType, typename ValueType>
    struct TypeHelper
    {
        public:
            explicit constexpr TypeHelper(const AddressType& addr)
                : addr_{addr} { }
            operator ValueType () const
            {
                return *reinterpret_cast<volatile ValueType*>(addr_);
            }
            void operator=(const ValueType val) const
            {
                *reinterpret_cast<volatile ValueType*>(addr_) = val;
            }
        private:
            const AddressType addr_;
    };

    template<typename AddressType>
    using Byte = TypeHelper<AddressType, uint8_t>;

    template<typename AddressType>
    using HalfWord = TypeHelper<AddressType, uint16_t>;

    template<typename AddressType>
    using Word = TypeHelper<AddressType, uint32_t>;
}

#endif //_HW_REG_TYPE_HELPER_HPP