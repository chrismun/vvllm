!T1:data construct copyout clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        INTEGER :: errors = 0

        !Data allocation for testing
        REAL(8), DIMENSION(LOOPCOUNT):: a, b, c
        INTEGER :: x
        x =  GDIM1
        IF ( x .eq. 1 ) THEN
          a = 0
          b = 0
          c = 0
        ELSE
          a = 1
          b = 1
          c = 1
        END IF

        !$acc enter data copyin(a(1:LOOPCOUNT), b(1:LOOPCOUNT), c(1:LOOPCOUNT))
        !$acc parallel present(a(1:LOOPCOUNT), b(1:LOOPCOUNT)) num_gangs(1) vector_length(1)
           !$acc loop
           DO x = 1, LOOPCOUNT
             c(x) = a(x) * b(x)
           END DO
        !$acc end parallel
        !$acc exit data copyout(c(1:LOOPCOUNT)) delete(a(1:LOOPCOUNT), b(1:LOOPCOUNT))

        !Checkout that no indexes are bonkers
        DO x = 1, LOOPCOUNT
          IF (abs(c(x) - (a(x) * b(x))) .gt. 3 * PRECISION) THEN
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