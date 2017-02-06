(define (distance-points a b)
  (let ((delta-x (- (x-point a) (x-point b)))
        (delta-y (- (y-point a) (y-point b))))
  (sqrt (+ (* delta-x delta-x)
           (* delta-y delta-y)))))
(define (length-segment s)
  (distance-points (start-segment s) (end-segment s)))

(define (make-rectangle a b c d)
  (let ((s1 (make-segment a b))
        (s2 (make-segment b c)))
  (cons s1 s2)))
(define (height-rectangle r)
  (length-segment (car r)))
(define (width-rectangle r)
  (length-segment (cdr r)))

(define (perimeter-rectangle r)
  (* 2 (+ (height-rectangle r) (width-rectangle r))))
(define (area-rectangle r)
  (* (height-rectangle r) (width-rectangle r)))

;test codes
(define a (make-point 3 4))
(define b (make-point 1 2))
(define c (make-point 3 0))
(define r (make-rectangle a b c 0))
(perimeter-rectangle r)
(area-rectangle r)

;another implementation, a edge and the length of the counterclock side
(define (make-rectangle s l)
  (cons s l))
(define (height-rectangle r)
  (length-segment (car r)))
(define (width-rectangle r)
  (cdr r))

;test codes 2
(define s (make-segment b c))
(define l (sqrt 8))
(define r2 (make-rectangle s l))
(perimeter-rectangle r2)
(area-rectangle r2)
