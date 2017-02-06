(define (make-mobile left right)
  (list left right))
(define (make-branch length structure)
  (list length structure))

;a
(define (left-branch mobile)
  (car mobile))
(define (right-branch mobile)
  (car (cdr mobile)))
(define (branch-length branch)
  (car branch))
(define (branch-structure branch)
  (car (cdr branch)))

;b
(define (branch-weight branch)
  (let ((structure (branch-structure branch)))
  (if (pair? structure)
      (totle-weight structure)
      structure)))
(define (totle-weight mobile)
  (let ((lb (left-branch mobile))
        (rb (right-branch mobile)))
  (+ (branch-weight lb) (branch-weight rb))))

;c
(define (balanced? mobile)
  (let ((lb (left-branch mobile))
        (rb (right-branch mobile)))
  (define (branch-balanced? branch)
    (let ((structure (branch-structure branch)))
    (if (pair? structure)
        (balanced? structure)
        true)))
  (define (top-balanced?)
    (and (= (* (branch-weight lb) (branch-length lb))
            (* (branch-weight rb) (branch-length rb)))))
  (and (branch-balanced? lb)
       (branch-balanced? rb)
       (top-balanced?))))

;test code
(define b1 (make-branch 4 5))
(define b2.1 (make-branch 1 3))
(define b2.2 (make-branch 3 1))
(define m2 (make-mobile b2.1 b2.2))
(define b2 (make-branch 5 m2))
(define m (make-mobile b1 b2))

;d
;(define (make-mobile left right)
;  (cons left right))
;(define (make-branch length structure)
;  (cons length structure))

;(define (right-branch mobile)
;   (cdr mobile))
;(define (branch-structure branch)
;  (cdr branch))

