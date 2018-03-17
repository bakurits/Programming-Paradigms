(define (min-wrap lst)
    (if (= (length lst) 0) '(10000000000 ())
        ((lambda (a b)
            (if (> (car a) (car b)) b
                a
            )
        )(car lst) (min (cdr lst)))
    )
)

(define (min lst)
    (if (= (car (min-wrap lst)) 10000000000) '(0 ())
        (min-wrap lst)
    )
)

(define (isGood elem lst)
    (if (= (length lst) 0) #t
        (if (= (car lst) elem) #f
            (isGood elem (cdr lst))
        )
    )
)

(define (pls pr val)
    (cons (+ val (car pr)) (cdr pr))
)

(define (rec start edges cur)
    (min (map (lambda (curEdge)
                (if (= start (car curEdge)) (if (isGood (cadr curEdge) cur) (pls (rec (cadr curEdge) edges (cons (cadr curEdge) cur)) (caddr curEdge))
                                                '(10000000000 ())
                                            )
                    (if (= start (cadr curEdge)) (if (isGood (car curEdge) cur) (pls (rec (car curEdge) edges (cons (car curEdge) cur)) (caddr curEdge))
                                                    '(10000000000 ())
                                                )
                        '(10000000000 ())
                    )
                )
            )
            edges)
    )
)

(define (sailsman start edges)
    (cadr (rec start edges '()))
)

