program day1
    implicit none

    integer, parameter :: input_len = 200
    integer, parameter :: search = 2020

    integer :: i, j
    integer, dimension(input_len) :: input

    open(10, file='input', status='old')
    do i = 1, input_len
        read(10, *) input(i)
    end do
    close(10)

    do i = 1, input_len
        do j = 1, input_len
            if (input(i) + input(j) == search) then
                print *, input(i) * input(j)
                stop
            end if
        end do
    end do

end program day1
