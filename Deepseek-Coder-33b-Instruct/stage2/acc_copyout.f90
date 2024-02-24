#ifndef T1
!T1:acc copyout,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        INTEGER, PARAMETER :: N = 100
        INTEGER :: i
        INTEGER, DIMENSION(:), ALLOCATABLE :: a, a_host

        ALLOCATE(a(N), a_host(N))

        ! Initialize data on the host
        DO i = 1, N
          a_host(i) = i
        END DO

        ! Copy data to the device
        !$acc enter data copyin(a_host) create(a)

        ! Copy data from the device to the host
        !$acc update device(a_host)
        !$acc copyout(a)

        ! Check the results
        DO i = 1, N
          IF (a(i) /= a_host(i)) THEN
            errors = errors + 1
          END IF
        END DO

        !$acc exit data delete(a)

        DEALLOCATE(a, a_host)

        IF (errors .eq. 0) THEN
          test1 = .FALSE.
        ELSE
          test1 = .TRUE.
        END IF
      END
#endif

      PROGRAM main
        IMPLICIT NONE
        INTEGER :: failcode, testrun
        LOGICAL :: failed
        INCLUDE "acc_testsuite.Fh"
#ifndef T1
        LOGICAL :: test1
#endif
        failed = .FALSE.
        failcode = 0
#ifndef T1
        DO testrun = 1, NUM_TEST_CALLS
          failed = failed .or. test1()
        END DO
        IF (failed) THEN
          failcode = failcode + 2 ** 0
          failed = .FALSE.
        END IF
#endif
        CALL EXIT (failcode)
      END PROGRAM