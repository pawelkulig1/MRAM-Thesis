#pragma once
#include <deque>
#include <functional>
#include "MovingImage.h"
#include "Chain.h"

namespace GNEB
{
    class MovingImage;
    class Point;

    class AbstractChainRecalculator
    {
    protected:
        Chain chainCopy;
        Chain *originalChain;
    public:
        virtual Chain recalculateChain(Chain *originalChain) = 0;
    };
}

