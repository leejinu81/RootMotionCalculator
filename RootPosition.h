#ifndef TESTCPP_ROOTPOSITION_H
#define TESTCPP_ROOTPOSITION_H

#include "Vector3Nx.h"

struct RootPosition final {
    RootPosition();

    RootPosition(int timeMs, const Vector3Nx &pos);

    static const RootPosition EmptyRootPosition;

    const int timeMs_{};
    const Vector3Nx pos_{};
};

#endif //TESTCPP_ROOTPOSITION_H
