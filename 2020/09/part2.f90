integer function has_sum(arg, arr)
    implicit none

    integer, parameter :: arr_len = 25

    integer (kind=8) :: arg
    integer (kind=8), dimension(25) :: arr
    integer :: i, j

    do i = 1, arr_len
        do j = 1, arr_len
            if (arr(i) + arr(j) == arg) then
                has_sum = 1
                return
            end if
        end do
    end do

    has_sum = 0
    return
end function has_sum

program day9
    implicit none

    integer, parameter :: input_len = 1000

    integer :: has_sum, i, j, tmp
    integer (kind=8), dimension(input_len) :: input
    integer (kind=8) :: search = -1, sum

    open(10, file='input', status='old')
    do i = 1, input_len
        read(10, *) input(i)
    end do
    close(10)

    do i = 26, input_len
        tmp = has_sum(input(i), input(i - 25))
        if (tmp == 0) then
            search = input(i)
            exit
        end if
    end do

    do i = 1, input_len
        sum = 0
        do j = i, input_len
            sum = sum + input(j)
            if (sum >= search) then
                exit
            end if
        end do
        if (sum == search) then
            print *, minval(input(i:j)) + maxval(input(i:j))
            stop
        end if
    end do

end program day9
