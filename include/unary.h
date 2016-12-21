#ifndef SPACE_UNARY_H
#define SPACE_UNARY_H

#include "basis.h"
#include "blade.h"
#include "brigand/algorithms/count.hpp"
#include "brigand/sequences/size.hpp"
#include "brigand/types/integer.hpp"

namespace space {
    namespace unary {
        namespace detail {
            template <class Op,
                      class Algebra,
                      template <class...> class Multivector,
                      template <class...> class Basis,
                      class... Blades>
            constexpr auto UnaryOp(Op, const Multivector<Algebra, Basis<Blades...>>& m)
            {
                using Basis_ = Basis<Blades...>;
                return Multivector<Algebra, Basis_>(
                    (Op::Sign(Blades{}) * m[basis::BladeIndex<Basis_, Blades>::value])...);
            }
        }

        namespace op {
            template <class T>
            struct Negate {
                template <class Blade>
                static constexpr auto Sign(Blade)
                {
                    return T(-1);
                }
            };

            template <class T>
            struct Reverse {
                template <class Blade>
                static constexpr auto Sign(Blade)
                {
                    return blade::ReverseHasSignFlip(Blade::value) ? T(-1) : T(1);
                }
            };

            template <class T>
            struct Involute {
                template <class Blade>
                static constexpr auto Sign(Blade)
                {
                    return blade::InvoluteHasSignFlip(Blade::value) ? T(-1) : T(1);
                }
            };

            template <class T>
            struct Conjugate {
                template <class Blade>
                static constexpr auto Sign(Blade)
                {
                    return blade::ConjugateHasSignFlip(Blade::value) ? T(-1) : T(1);
                }
            };
        }

        template <class Algebra, template <class...> class Multivector, class Basis>
        constexpr auto Negate(const Multivector<Algebra, Basis>& m)
        {
            using ScalarValue = typename Algebra::ScalarValue;
            return detail::UnaryOp(op::Negate<ScalarValue>{}, m);
        }

        template <class Algebra, template <class...> class Multivector, class Basis>
        constexpr auto Reverse(const Multivector<Algebra, Basis>& m)
        {
            using ScalarValue = typename Algebra::ScalarValue;
            return detail::UnaryOp(op::Reverse<ScalarValue>{}, m);
        }

        template <class Algebra, template <class...> class Multivector, class Basis>
        constexpr auto Involute(const Multivector<Algebra, Basis>& m)
        {
            using ScalarValue = typename Algebra::ScalarValue;
            return detail::UnaryOp(op::Involute<ScalarValue>{}, m);
        }

        template <class Algebra, template <class...> class Multivector, class Basis>
        constexpr auto Conjugate(const Multivector<Algebra, Basis>& m)
        {
            using ScalarValue = typename Algebra::ScalarValue;
            return detail::UnaryOp(op::Conjugate<ScalarValue>{}, m);
        }
    }
}

#endif
