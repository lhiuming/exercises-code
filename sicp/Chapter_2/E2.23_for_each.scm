(define (for-each proc l)
  (cond ((null? l)
           true)
        (else
           (proc (car l))
           (for-each proc (cdr l)))))
