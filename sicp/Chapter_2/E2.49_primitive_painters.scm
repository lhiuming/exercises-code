(define (segments->painter segment-list)
  (lambda (frame)
    (for-each
     (lambda (segment)
       (draw-line
        ((frame-coord-map frame) (start-segment segment))
        ((frame-coord-map frame) (end-segment segment))))
     segment-list)))


(define outline
  (let ((p1 (make-vect 0 0))
        (p2 (make-vect 0 1))
        (p3 (make-vect 1 1))
        (p4 (make-vect 1 0)))
    (let ((s1 (make-segment p1 p2))
          (s2 (make-segment p2 p3))
          (s3 (make-segment p3 p4))
          (s4 (make-segment p4 p1)))
      (segments->painter (list s1 s2 s3 s4)))))

(define draw-X
  (let ((s1 (make-segment (make-vect 0 0) (make-vect 1 1)))
        (s2 (make-segment (make-vect 0 1) (make-vect 1 0))))
    (segments->painter (list s1 s2))))

(define diamond
  (let ((p1 (make-vect 0 0.5))
        (p2 (make-vect 0.5 1))
        (p3 (make-vect 1 0.5))
        (p4 (make-vect 0.5 0)))
    (let ((s1 (make-segment p1 p2))
          (s2 (make-segment p2 p3))
          (s3 (make-segment p3 p4))
          (s4 (make-segment p4 p1)))
      (segments->painter (list s1 s2 s3 s4)))))

;;; (define wave
;;;    (
;;; Oh, no
