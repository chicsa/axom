!
! Test code generated by the tutorial test
!
program tester
  use iso_c_binding
  use tutorial_mod
  implicit none

  logical rv_logical
  integer rv_integer
  real(C_DOUBLE) rv_double
  character(30) rv_char

  character(4)  status

  call test_functions

  call test_class1

!  call test_allocable

contains

  subroutine test_functions
    call function1
    call assert_true(.true.)

    rv_double = function2(1.d0, 4)
    call assert_true(rv_double == 5.d0)

    rv_logical = function3(.false.)
    call assert_true(rv_logical)

    call assert_true( function4a("dog", "cat") == "dogcat")

    call function4b("dog", "cat", rv_char)
    call assert_true( rv_char == "dogcat")

    call assert_real(function5(), 8.13d0)
    call assert_real(function5(1.d0, 2), 3.d0)
    call assert_real(function5(arg2=6), 9.13d0)

    call function6("name")
    call assert_true(last_function_called() == "Function6(string)")
    call function6(1)
    call assert_true(last_function_called() == "Function6(int)")

    call function7(1)
    call assert_true(last_function_called() == "Function7<int>")
    call function7(10.d0)
    call assert_true(last_function_called() == "Function7<double>")

    ! return values set by calls to function7
    rv_integer = function8_int()
    call assert_true(rv_integer == 1)
    rv_double = function8_double()
    call assert_true(rv_double == 10.d0)

    call function9(1.0)
    call assert_true(.true.)
    call function9(1.d0)
    call assert_true(.true.)
  end subroutine test_functions

  subroutine test_class1
    type(class1) obj

    obj = class1_new()
    call assert_true(c_associated(obj%voidptr), "class1_new")

    call obj%method1()
    call assert_true(.true.)

    call obj%delete()
    call assert_true(.not. c_associated(obj%voidptr), "class1_delete")
  end subroutine test_class1

  subroutine assert_real(a, b)
    real(C_DOUBLE) a, b
    call assert_true((abs(a - b) < .00001))
  end subroutine assert_real

  subroutine assert_true(expr, msg)
    logical expr
    character(*), optional :: msg
    if (expr) then
       status = "pass"
    else
       status = "fail"
    endif

    if (present(msg)) then
       print *, msg, " -- ", status
    else
       print *, last_function_called(), " -- ", status
    endif
  end subroutine assert_true

!  subroutine test_allocable
!    integer, allocatable :: iarray(:)
!
!   allocate(iarray(10))
!    call all_test1(iarray)
!
!  end subroutine test_allocable


end program
