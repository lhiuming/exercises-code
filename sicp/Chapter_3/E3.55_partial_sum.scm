(define (partial-sums stm)
  (define self
    (cons-stream (stream-car stm)
                 (add-streams (stream-cdr stm)
                              self)))
  self)
