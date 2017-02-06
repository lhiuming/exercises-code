(define (estimate-integral P x1 x2 y1 y2 trails)
  (define (experiment)
    (let ((x (random-in-range x1 x2))
          (y (random-in-range y1 y2)))
      (P x y)))
  (* (monte-carlo trails experiment)
     (* (- x2 x1) (- y2 y1))))

(define (monte-carlo-pi trails)
  (define (in-unit-circle? x y)
    (< (+ (* x x) (* y y))
       1))
  (estimate-integral in-unit-circle? -1.0 1.0 -1.0 1.0 trails))

;;; test
(monte-carlo-pi 500)
(monte-carlo-pi 80000)
