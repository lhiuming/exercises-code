(define (list-of-values exps env) ;left to right
  (if (no-operands? exps)
      '()
      (let ((first-value (eval (first-operand exps) env)))
        (let ((rest-values (list-of-values (rest-operands exps) env)))
          (cons first-value rest-values)))))

(define (list-of-value exps env) ;right to left
  (if (no-operands? exps)
      '()
      (let ((rest-values (list-of-values (rest-operands exps)) env))
        (let ((first-value (eval (first-operand exps) env)))
          (cons first-value rest-values)))))
