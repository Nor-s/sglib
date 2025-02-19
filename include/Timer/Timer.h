#ifndef SGLIB_TIMER
#define SGLIB_TIMER

template <typename Func>
void InvokeWithTimer(double limit, Func _function)
{
    _function();
}

#endif