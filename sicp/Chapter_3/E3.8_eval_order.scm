(define f
  (let ((state 0))
    (define (reset x)
      (set! state x))
    (define (accumulate x)
      (if (eq? x 'reset)
          reset
          (begin (set! state (+ state x))
                 state)))
  accumulate))

;;; 
(+ (f 0) (f 1))
((f 'reset) 0)
(+ (f 1) (f 0))
