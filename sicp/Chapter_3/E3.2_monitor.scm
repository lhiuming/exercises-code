(define (make-monitored f)
  (let ((counter 0))
    (define (mf x)
      (cond ((eq? x 'how-many-calls?) counter)
            ((eq? x 'reset-count) (set! counter 0) counter)
            (else (set! counter (+ counter 1)) (f x))))
    mf))

