#ifndef _HW_REG_IO_REG_HPP
#define _HW_REG_IO_REG_HPP

#include "HwReg/TypeHelper.hpp"

namespace HwReg
{
    template<typename AddressType, typename ValueType>
    class IoReg
    {
        using RegType = TypeHelper<AddressType, ValueType>;
        public:
            explicit constexpr IoReg(const AddressType& baseAddr)
                : baseAddr_{baseAddr} { }
            constexpr auto operator[](const AddressType& offset) const
            {
                return RegType{baseAddr_ + offset};
            }
        private:
            const AddressType baseAddr_;
    }; 
}

#endif //_HW_REG_IO_REG_HPP