#include "uintspinner.hpp"
#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstring>
#include "util.hpp"

using namespace std;

namespace {


} // anonymous

namespace patxitron {

UintSpinner::UintSpinner(int x, int y, uint16_t minval, uint16_t maxval
                        ,uint16_t val)
        :Fl_Group(x, y, Spinner::WIDTH * static_cast<uint16_t>(log10(max_)) + 1, Spinner::HEIGHT)
        ,value_(val < minval ? minval : (val > maxval ? maxval : val))
        ,max_(maxval)
        ,min_(minval)
        ,order_(static_cast<uint16_t>(log10(max_)) + 1)
{
    strncpy(fmt_, "%00hu", 6);
    fmt_[2] = static_cast<char>(order_) + '0';
    char buffer[6];
    snprintf(buffer, 6, fmt_, val);
    for (ssize_t i = order_ - 1; i >= 0; i--) {
        spinners_.emplace_back(new Spinner(x + i * Spinner::WIDTH, y, buffer[i] - '0'));
        spinners_.back()->callback(&UintSpinner::spinner_cb, this);
    }
}



uint16_t UintSpinner::value(uint16_t val)
{
    cout << "UintSpinner::value(" << val << ")" << endl;
    if (val > max_) val = max_;
    if (val < min_) val = min_;
    value_ = val;
    char buffer[6];
    snprintf(buffer, 6, fmt_, value_);
    for (size_t i = 0; i < order_; i++) {
        spinners_[i]->value(buffer[i] - '0');
    }
    do_callback();
    return value_;
}



uint16_t UintSpinner::increment()
{
    if (value_ < max_) return value(value_ + 1);
    else return value_;
}



uint16_t UintSpinner::decrement()
{
    if (value_ > min_) return value(value_ - 1);
    else return value_;
}



void UintSpinner::spinnercb()
{
    uint16_t new_value = 0;
    uint16_t factor = 1;
    cout << "UintSpinner::spinnercb()" << endl;
    for (auto const& v: spinners_) {
        new_value += v->value() * factor;
        factor *= 10;
    }
    util::ignore_result(value(new_value));
    cout << "UintSpinner::spinnercb(): " << value_ << endl;
}



void UintSpinner::spinner_cb(Fl_Widget* cb, void* p)
{
    cout << "UintSpinner::spinner_cb()" << endl;
    reinterpret_cast<UintSpinner*>(p)->spinnercb();
}

} // patxitron
