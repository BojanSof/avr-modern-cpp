#ifndef _MMIO_MMIO_HPP
#define _MMIO_MMIO_HPP

#include "Mmio/Register.hpp"

namespace Mmio
{
    template<typename AddressType, typename ValueType>
    class Mmio
    {
        using RegType = Register<AddressType, ValueType>;
        public:
            explicit constexpr Mmio(const AddressType& baseAddr)
                : baseAddr_{baseAddr} { }
            constexpr auto operator[](const AddressType& offset) const
            {
                return RegType{baseAddr_ + offset};
            }
        private:
            const AddressType baseAddr_;
    }; 
}

#endif //_MMIO_MMIO_HPP