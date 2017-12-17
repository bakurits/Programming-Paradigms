(define (range l r)
    (if (> l r) '()
        (cons l (range (+ 1 l) r))
    )
)

(define (string-concat num)
    (if (= (length num) 0) '()
        (if (eval (cons or (map (lambda (x) (equal? x (car num)))
            (range 0 9)))
        ) (cons (car num) (string-concat (cdr num)))
            (string-concat (cdr num))
        )
    )
)

(define (generate len)
    (lambda (x) (* x len))
)

(define (multiply seq)
    (map (generate (length seq))
        seq)
)


(define (reverse seq)
    (if (null? seq) '()
        (if (= (length seq) 1) seq
            (append (reverse (cdr seq)) (list (car seq)))
        )
    )
)

(define (convert-wr n base)
    (if (< n base) (list n)
        (cons (remainder n base) (convert-wr (quotient n base) base))
    )
)

(define (convert n base)
    (reverse (convert-wr n base))
)

(define (generate base)
    (lambda (n) (convert n base))
)