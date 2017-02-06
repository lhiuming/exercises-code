(define (iterative-improve good-enough? improve)
  (define (lambda-iter guess)
    (if (good-enough? guess)
        guess
        (lambda-iter (improve guess))))
  lambda-iter)


(define (sqrt x)
  (let ((tolerance 0.00001))
  (define (good-enough? y)
    (< (abs (- x (* y y))) tolerance))
  (define (improve guess)
    (/ (+ guess (/ x guess)) 2.0))
  ((iterative-improve good-enough? improve) x)))

(define (fixed-point f first-guess)
  (let ((tolerance 0.00001))
  (define (good-enough? y)
    (< (abs (- (f y) y)) tolerance))
  (define (improve guess)
    (f guess))
  ((iterative-improve good-enough? improve) first-guess)))

