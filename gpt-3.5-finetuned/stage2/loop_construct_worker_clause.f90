!T1:loop construct worker clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0

        INTEGER :: a(LOOPCOUNT)
        INTEGER :: b(LOOPCOUNT)
        INTEGER :: c(LOOPCOUNT)
        INTEGER :: d(LOOPCOUNT)
        
        ! Loop initializer
        SEEDDIM(1) = 1
        SEEDDIM(2) = 1
        CALL RANDOM_SEED(PUT=SEEDDIM)
        CALL RANDOM_NUMBER(a)
        CALL RANDOM_NUMBER(b)
        c = 0
        d = 0

        !$acc data copyin(a(1:LOOPCOUNT), b(1:LOOPCOUNT)) copy(c(1:LOOPCOUNT),d(1:LOOPCOUNT))
          !$acc parallel
            !$acc loop worker
            DO i = 1, LOOPCOUNT
              c(i) = a(i) + b(i)
            END DO
            !$acc loop worker
            DO i = 1, LOOPCOUNT
              d(i) = a(i) * b(i)
            END DO
          !$acc end parallel
        !$acc end data
        DO i = 1, LOOPCOUNT
          IF (c(i) .ne. a(i) + b(i)) THEN
            errors = errors + 1
          END IF
          IF (d(i) .ne. a(i) * b(i)) THEN
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