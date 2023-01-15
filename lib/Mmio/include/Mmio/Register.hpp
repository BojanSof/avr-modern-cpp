#ifndef _MMIO_REGISTER_HPP
#define _MMIO_REGISTER_HPP

#include <stdint.h>

namespace Mmio
{
    template<typename AddressType, typename ValueType>
    struct Register
    {
        public:
            explicit constexpr Register(const AddressType& addr)
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
    using ByteRegister = Register<AddressType, uint8_t>;

    template<typename AddressType>
    using HalfWordRegister = Register<AddressType, uint16_t>;

    template<typename AddressType>
    using WordRegister = Register<AddressType, uint32_t>;
}

#endif //_MMIO_REGISTER_HPP