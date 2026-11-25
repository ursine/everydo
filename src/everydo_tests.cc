#include "everydo.hh"

#include <print>
#include <liburing.h>

template<typename T>
void zeroStruct(T *toZero)
{
    memset(toZero, 0, sizeof(T));
}

constexpr int QD = 64;

int main() {
    //everydo::Context context;
    //everydo::SqlDatabase database(":memory:");

    io_uring ring;

    io_uring_params params{
        .cq_entries = QD * 8,
        .flags = IORING_SETUP_SUBMIT_ALL | IORING_SETUP_CQSIZE |
               IORING_SETUP_SINGLE_ISSUER |
               IORING_SETUP_DEFER_TASKRUN
    };

    /* Initialize io_uring */
    io_uring_queue_init_params(QD, &ring, &params);

    int major = io_uring_major_version();
    int minor = io_uring_minor_version();
    std::println("Initialized liburing {}.{}", major, minor);

    std::println("Booting up");


    return 0;
}
