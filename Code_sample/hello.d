sudo bpftrace -e '
tracepoint:syscalls:sys_enter_futex
{
    @[comm] = count();
}
'
