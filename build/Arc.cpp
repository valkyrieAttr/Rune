#include <iostream>

template<typename Tp_, typename Ep_>
class Expect {
    public:
        Tp_ value;
        Ep_ error;
        bool is_error;

        explicit constexpr Expect
            ( Tp_ ok, bool ) noexcept ( true )
        : value(std::move(ok)), error{}, is_error{false} {}

        explicit constexpr Expect
            ( Ep_ err ) noexcept ( true )
        : value{}, error(std::move(err)), is_error(true) {}

};

template<typename Tp_, typename Ep_>
class Result {
    private:
        Expect<Tp_, Ep_> data;

        explicit constexpr Result
            ( Expect<Tp_, Ep_> exp )
        : data(std::move(exp)) {}
    public:
        static constexpr auto Ok(Tp_ ok) -> Result<Tp_, Ep_> {
            return Result{Expect<Tp_, Ep_>(ok, true)};
        }

        static constexpr auto Err(Ep_ err) -> Result<Tp_, Ep_> {
            return Result{Expect<Tp_, Ep_>(err)};
        }

        constexpr auto value() -> Tp_& {
            return this->data.value;
        }

        constexpr auto error() -> Ep_& {
            return this->data.error;
        }
};

static auto Calculate(int min, int max) -> Result<int, const char*> {
    if (max < 0) return Result<int, const char*>::Err("Faliure, 0!");

    return Result<int, const char*>::Ok(min + max);
}

auto main() -> int {
    auto name = Calculate(5, 0);

    if (name.)
}
