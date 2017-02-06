(define (deep-reverse tree)
  (define (reverse-iter tree result)
    (cond ((null? tree) result)
          ((pair? tree) (reverse-iter
                          (cdr tree)
                          (cons (deep-reverse (car tree)) result)))
          (else tree)))
  (reverse-iter tree ()))
