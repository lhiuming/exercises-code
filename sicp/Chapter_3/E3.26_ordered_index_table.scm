(define (make-table)
  (let ((local-table (list '*table*)))
    (define (prior? key1 key2)
      true)
    (define (lookup
    (define (insert! key value)
      (define (iter branch)
        (if (null? branch)
            (cons (cons key value) (cons '() '()))
            (let ((node-record (car branch))
                  (node-key (caar branch)))
              (cond ((eq? key node-key)
                      (set-cdr! node-record value))
                    ((prior? key node-key)
                       (set-car! (cdr branch) (iter (cdar branch))))
                    (else (set-cdr! (cdr branch) (iter (cddr branch)))))))
        branch)