(define (average-damp f)
  (lambda (x) (/ (+ x (f x)) 2)))

(define tolerance 0.000001)
(define (fixed-point f first-guess)
  (define (close-enough? v1 v2)
    (< (abs (- v1 v2)) tolerance))
  (define (try guess)
    (let ((next (f guess)))
      (if (close-enough? guess next)
          next
          (try next))))
  (try first-guess))

(define (exp x n)
  (if (= n 0)
      1
      (* x (exp x (- n 1)))))

(define (repeated f n)
  (define (repeated-rec i)
    (if (= i 1)
	f
        (lambda (x) (f ((repeated-rec (- i 1)) x)))))
  (repeated-rec n))

(define (test k n)
;test whether n-damp can make kth-root converge
  (let ((x (exp 5 k)))
  (define (f y)
    (/ x (exp y (- k 1))))
  (fixed-point ((repeated average-damp n) f) 2.0)))

(define (aver-damp-calc x)
;work out the neccessary average-damp time for xth root
  (define (adc-iter i)
    (if (< (/ x 2) (exp 2 i))
        i
        (adc-iter (+ i 1))))
  (adc-iter 1))
(define (root n x)
  (let ((aver-damp-time (aver-damp-calc n)))
  (define (f y)
    (/ x (exp y (- n 1))))
  (fixed-point ((repeated average-damp aver-damp-time) f) 2.0)))
