(define (make-table)
  (let ((local-table (list '*table*)))
    (define (lookup list-of-keys)
      (define (iter keys table)
        (if (null? keys)
            (cdr table)
            (let ((subtable (assoc (car keys) (cdr table))))
              (if subtable
                  (iter (cdr keys) subtable)
                  false))))
      (if (null? list-of-keys)
          (error "Invalid keys -- empty list")
          (iter list-of-keys local-table)))
    (define (insert! list-of-keys value)
      (define (iter keys table)
        (if (null? keys)
            (set-cdr! table value)
            (let ((subtable (assoc (car keys) (cdr table))))
              (if subtable
                  (iter (cdr keys) subtable)
                  (let ((new-subtable (list (car keys))))
                    (set-cdr! table (cons new-subtable
                                          (cdr table)))
                    (iter (cdr keys) new-subtable))))))
      (if (null? list-of-keys)
          (error "Invalid keys -- empty list")
          (iter list-of-keys local-table))
      'ok)
    (define (dispatch m)
      (cond ((eq? m 'lookup-proc) lookup)
            ((eq? m 'insert-proc!) insert!)
            (else (error "Unknown operation -- TABLE" m))))
    dispatch))

;;; test code
(define personnel (make-table))
(define get (personnel 'lookup-proc))
(define put (personnel 'insert-proc!))

(put (list 'John 'salary 'Jan) 999)
(put (list 'John 'salary 'May) 1200)
(put (list 'Jane 'employed-date) (list 2012 2 14))

(get (list 'John 'salary 'Jan))
(get (list 'John 'salary 'May))
(get (list 'John 'salary 'Aprl))
(get (list 'John 'friends))
(get (list 'Jane 'employed-date))
(newline)