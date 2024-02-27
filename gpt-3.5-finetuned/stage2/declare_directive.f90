!T1:declare directive,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0

        REAL(8), DIMENSION(LOOPCOUNT):: a, b, c
        REAL(8) :: a_host, b_host
        INTEGER :: x

        !$acc enter data copyin(a(1:LOOPCOUNT))) 
        !$acc enter data copyin(b(1:LOOPCOUNT)))
        !$acc parallel present(c(1:LOOPCOUNT))
          !$acc loop
          DO x = 1, LOOPCOUNT
            c(x) = a(x) + b(x)
          END DO
        !$acc end parallel
        !$acc exit data copyout(a(1:LOOPCOUNT))
        !$acc exit data copyout(b(1:LOOPCOUNT))

        DO x = 1, LOOPCOUNT
          IF (abs(a(x) - (a_loop_init - 1) * PRESENT_LOOP_INDEX) .gt. PRECISION) THEN
            errors = errors + 1
          END IF
          IF (abs(b(x) - PRESENT_LOOP_INDEX) .gt. PRECISION) THEN
            errors = errors + 1
          END IF
        END DO

        IF (errors .eq. 0) THEN
          test1 = .FALSE.
        ELSE
          test1 = .TRUE.
        END IF
      END

      PROGRAM main
        IMPLICIT NONE
        INTEGER :: failcode, testrun
        LOGICAL :: failed
        INCLUDE "acc_testsuite.Fh"
        LOGICAL :: test1
        failed = .FALSE.
        failcode = 0
        DO testrun = 1, NUM_TEST_CALLS
          failed = failed .or. test1()
        END DO
        IF (failed) THEN
          failcode = failcode + 2 ** 0
          failed = .FALSE.
        END IF
        CALL EXIT (failcode)
      END PROGRAM